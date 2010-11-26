/*  Gtk--addons: a collection of gtk-- addons
 *  Copyright (C) 2010 Christof Petig
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free
 *  Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */


#ifndef SEARCHCOMBOCONTENT3
#define SEARCHCOMBOCONTENT3

#include"SearchCombo3.h"

template<class T>
class SearchComboContent3 : public Gtk::SearchCombo3
{
public:
  struct cols_t : public Gtk::SearchCombo3::mycols
  {
    Gtk::TreeModelColumn<T> content;

    cols_t()
    { add (content);  }
  };

struct ContentError : public std::exception
{  virtual const char* what() const throw() { return "SearchComboContent3::ContentError";}
   ContentError() {}
};

 SearchComboContent3() : SearchCombo3(false,false,&cols) { }
 void add_item(const std::string &text, const T &item);
 void reset();
 void clear() {reset();}
 const T &Content() const;
 const T &get_value()const {return Content();}
 void setContent(const std::string &text, const T &c);
 void set_value(const std::string &text, const T &c){ setContent(text,c); }
 bool SetMatch(const T &c);

private:
 T current_content;
 static cols_t cols;

 void set_text(const std::string &text);
 virtual bool match_selected(const Gtk::TreeModel::iterator&);
};

template<class T>
typename SearchComboContent3<T>::cols_t SearchComboContent3<T>::cols;

template<class T>
bool SearchComboContent3<T>::match_selected(const Gtk::TreeModel::iterator& it)
{
  current_content=(*it)[cols.content];
  return Gtk::SearchCombo3::match_selected(it);
}

template<class T>
bool SearchComboContent3<T>::SetMatch(T const& v)
{
  for (const_iterator i=begin();i!=end();++i)
    if ((*i)[cols.content]==v)
      return Gtk::SearchCombo3::match_selected(it);
  return false;
}

template<class T>
void SearchComboContent3<T>::setContent(const std::string &text, const T &item)
{
// reset();  // why this?
 Gtk::SearchCombo3::set_text(text);
// Gtk::TreeIter it= Gtk::SearchCombo3::add_item(text);
// (*it)[cols.content]=item;
 current_content=item;
}


template<class T>
void SearchComboContent3<T>::add_item(const std::string &text, const T &item)
{
 if(size()==0) current_content=T();
 Gtk::TreeIter it= Gtk::SearchCombo3::add_item(text);
 (*it)[cols.content]=item;
}


template<class T>
const T &SearchComboContent3<T>::Content() const
{
  return current_content;
}

template<class T>
void SearchComboContent3<T>::reset()
{ current_content=T();
  Gtk::SearchCombo3::reset();
}

#endif
