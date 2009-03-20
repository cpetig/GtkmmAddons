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

template <class T>
struct ComboBoxMappingEntry
{
  T value;
  Glib::ustring name;
};

template <class T>
 typedef ComboBoxMappingEntry<T> ComboBoxMapping[];

#if 0
template <class T>
 class ComboBoxMapping : ComboBoxMappingArray
{
  
};
#endif

//namespace Gtk
//{
//  class ComboBoxText;
//};

// to pass both as arguments
#define ARRAY_WITH_SIZE(A) (A), (sizeof(A)/sizeof(A[0]))

#if 1
template <class T>
 void init(Gtk::ComboBoxText &widget, ComboBoxMapping<T> const& entries);

template <class T>
 void set(Gtk::ComboBoxText &widget, ComboBoxMapping<T> const& entries, T const& what);

template <class T>
 T get(Gtk::ComboBoxText const&widget, ComboBoxMapping<T> const& entries);

template <class T>
 void init(Gtk::ComboBoxText &widget, ComboBoxMapping<T> const& entries)
{
  for (unsigned i=0; i< sizeof(entries)/sizeof(entries[0]); ++i)
  {
    widget->append_text(entries[i].name);
  }
}
#endif
