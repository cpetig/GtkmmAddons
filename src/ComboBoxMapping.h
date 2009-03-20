/* $Id: ComboBoxMapping.h,v 1.7 2004/04/29 14:24:40 christof Exp $ */

/*
 * Copyright (C) 2009 Christof Petig
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

#include <gtkmm/comboboxtext.h>

// wrapper functions to associate a ComboBoxText with a set of named choices (of arbitrary data type)

// see ../test/ComboBoxMapping for a very simple example

namespace ComboBoxMapping
{

template <class T>
struct Entry
{
  T value;
  Glib::ustring name;
};

template <class T>
 void init(Gtk::ComboBoxText &widget, T const& entries);

template <class T>
 void init(Gtk::ComboBoxText &widget, T const& entries)
{
  widget.clear_items();
  for (unsigned i=0; i< sizeof(entries)/sizeof(entries[0]); ++i)
  {
    widget.append_text(entries[i].name);
  }
}

template <class T>
 void set(Gtk::ComboBoxText &widget, Entry<T> const* entries, T const& what)
{
  unsigned size=widget.get_model()->children().size();
  for (unsigned i=0; i<size; ++i)
    if (entries[i].value==what)
    { widget.set_active(i);
      return;
    }
  widget.set_active(-1);
}

template <class T>
 T get(Gtk::ComboBoxText const&widget, Entry<T> const* entries)
{
  if (widget.get_active_row_number()<0) return T();
  return entries[widget.get_active_row_number()].value;
}

} // namespace
