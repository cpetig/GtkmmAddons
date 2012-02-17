/* $Id: ComboBoxMapping.h,v 1.7 2004/04/29 14:24:40 christof Exp $ */

/*
 * Copyright (C) 2010 Christof Petig
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <map>
#include <gtkmm/comboboxentrytext.h>

// wrapper functions to associate a ComboBoxText with a set of named choices (of arbitrary data type)

// see ../test/ComboBoxMapping for a very simple example

namespace ComboBoxMapping
{

template <class T>
 void init(Gtk::ComboBoxEntryText &widget, std::map<T,Glib::ustring> const& entries)
{
  widget.clear_items();
  for (typename std::map<T,Glib::ustring>::const_iterator i=entries.begin(); i!=entries.end(); ++i)
  {
    widget.append_text(i->second);
  }
}

template <class T>
 void set(Gtk::ComboBoxEntryText &widget, std::map<T,Glib::ustring> const& entries, T const& what)
{
  typename std::map<T,Glib::ustring>::const_iterator j=entries.begin();
  for (unsigned i=0; j!=entries.end(); ++i, ++j)
    if (j->first==what)
    { widget.set_active(i);
      return;
    }
  widget.set_active(-1);
}

template <class T>
 T get(Gtk::ComboBoxEntryText const&widget, std::map<T,Glib::ustring> const& entries)
{
  if (widget.get_active_row_number()<0) return T();
  int index=widget.get_active_row_number();
  for (typename std::map<T,Glib::ustring>::const_iterator i=entries.begin(); i!=entries.end(); ++i,--index)
  {
    if (!index) return i->first;
  }
  return T();
}

} // namespace
