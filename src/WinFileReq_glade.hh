// generated 2008/6/28 12:10:48 CEST by christof@vesta.(none)
// using glademm V2.13.0
//
// DO NOT EDIT THIS FILE ! It was created using
// glade-- WinFileReq.glade
// for gtk 2.13.3 and gtkmm 2.12.7
//
// Please modify the corresponding derived classes in ./src/WinFileReq.hh and./src/WinFileReq.cc

#ifndef _WINFILEREQ_GLADE_HH
#  define _WINFILEREQ_GLADE_HH

// Since all your widgets were private I made them all public.
// To differentiate between accessable (e.g. entries, output labels)
// and unaccessible widgets (e.g. static labels, containers)
// you should use the 'visibility' property (only visible in C++ mode)


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

#include <gtkmm/fileselection.h>
#include <gtkmm/button.h>

class WinFileReq_glade : public Gtk::FileSelection
{  
        
        GlademmData *gmm_data;
public:
        class Gtk::FileSelection * WinFileReq;
protected:
        
        WinFileReq_glade();
        
        ~WinFileReq_glade();
private:
        virtual void on_ok_button1_clicked() = 0;
        virtual void on_cancel() = 0;
};
#endif
