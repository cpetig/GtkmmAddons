/* $Id: nsc_test.cc,v 1.5 2004/04/29 15:41:48 christof Exp $ */
/*  Gtk--addons: a collection of gtk-- addons
    Copyright (C) 1998  Adolf Petig GmbH. & Co. KG
    Developed by Christof Petig <christof.petig@wtal.de>
 
    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.
 
    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.
 
    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <ComboBoxMapping.h>
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include <iostream>

ComboBoxMapping::Entry<int> intmap[]= { { 20, "twenty" }, { 30, "thirty" } };

class testwindow : public Gtk::Window
{
        Gtk::ComboBoxText combo;

    public:

        testwindow() 
        {
            add(combo);
            combo.show();
            init(combo, intmap);
            ComboBoxMapping::set(combo, intmap, int());
            std::cout << ComboBoxMapping::get(combo, intmap) << '\n';
            ComboBoxMapping::set(combo, intmap, 20);
            std::cout << ComboBoxMapping::get(combo, intmap) << '\n';
        }
        ~testwindow()
        {
            std::cout << ComboBoxMapping::get(combo, intmap) << '\n';
        }
};


int main( int argc, char **argv )
{   Gtk::Main m(argc, argv );
    testwindow w;

    w.show();

    m.run(w);
    return 0;
}
