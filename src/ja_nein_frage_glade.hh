// generated 2011/6/30 11:53:48 CEST by christof@christof-hp.(none)
// using glademm V2.13.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- /home/christof/GtkmmAddons/glade/WinFileReq.glade
// for gtk 2.24.4 and gtkmm 2.24.0
//
// Please modify the corresponding derived classes in ./src/ja_nein_frage.hh and./src/ja_nein_frage.cc

#ifndef _JA_NEIN_FRAGE_GLADE_HH
#  define _JA_NEIN_FRAGE_GLADE_HH


#if !defined(GLADEMM_DATA)
#define GLADEMM_DATA 
#include <gtkmm/accelgroup.h>

class GlademmData
{  
        
        Glib::RefPtr<Gtk::AccelGroup> accgrp;
public:
        
        GlademmData(Glib::RefPtr<Gtk::AccelGroup> ag) : accgrp(ag)
        {  
        }
        
        Glib::RefPtr<Gtk::AccelGroup>  getAccelGroup()
        {  return accgrp;
        }
};
#endif //GLADEMM_DATA

#include <gtkmm/dialog.h>
#include <gtkmm/button.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/label.h>
#include <gtkmm/box.h>

class ja_nein_frage_glade : public Gtk::Dialog
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::Dialog * ja_nein_frage;
        class Gtk::Button * button28;
        class Gtk::Button * button30;
        class Gtk::Label * label_text;
protected:
        
        ja_nein_frage_glade();
        
        ~ja_nein_frage_glade();
};
#endif
