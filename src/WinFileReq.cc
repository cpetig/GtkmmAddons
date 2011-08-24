// generated 2002/11/13 0:12:01 CET by christof@puck.petig-baender.de
// using glademm V1.1.2a_cvs
//
// newer (non customized) versions of this file go to WinFileReq.cc_new

// This file is for your program, I won't touch it again!

#include "config.h"
#include "WinFileReq.hh"
#include <iostream>

#ifdef __MINGW32__
//#include <DllObject.h> // cant use ManuProC_Base
# include <windows.h>
# include <commdlg.h>
# include <objidl.h> // IMalloc
# include <shlobj.h>
#include <gdk/gdkwin32.h>
#include <assert.h>
//#include <Misc/i18n.h> // dependency not easily added, prefer glib_gettext?
#define _(X) (X)

//class TagStream { public: static void utf82iso(std::string &s); };
//extern std::string utf82iso(const std::string &s);
#endif

#ifndef __MINGW32__
void WinFileReq::on_ok_button1_clicked()
{  slot(get_filename());
   if (!dont_delete) delete this;
}

void WinFileReq::on_cancel()
{  if (call_on_cancel) slot(std::string());
   if (!dont_delete) delete this;
}

#if 0 && GTKMM_MAJOR_VERSION==2 && GTKMM_MINOR_VERSION>2
#  include <sigc++/bind.h>
// don't ask me why this does not work:
// #  include <sigc++/compatibility.h>
// /usr/include/sigc++-2.0/sigc++/object_slot.h: In function `
//    SigC::Slot0<T_return> SigC::slot(T_obj1&, T_return (T_obj2::*)()) [with
//    T_return = void, T_obj1 = WinFileReq_glade, T_obj2 = WinFileReq_glade]':
// WinFileReq_glade.cc:35:   instantiated from here
// /usr/include/sigc++-2.0/sigc++/object_slot.h:32: error: cannot convert from
//    base `sigc::trackable' to derived type `WinFileReq_glade' via virtual base `
//    sigc::trackable'

namespace SigC
{  template <class T>
    Slot0<void> slot(T &t, void (T::*p)()) { return sigc::mem_fun(t,p); }
}
#endif

#include "WinFileReq_glade.cc"
#endif

#ifdef WIN32
std::wstring WinFileReq::make_wstring(std::string const& x)
{
#if 0
  return ManuProC::make_wstring(x);
#else
  if (x.empty()) return std::wstring();
  wchar_t wstring[10240];
  int res= MultiByteToWideChar(CP_UTF8, 0, x.data(), x.size(), wstring, sizeof(wstring)/sizeof(wchar_t));
  assert(res!=0);
//  size_t r= mbstowcs(wstring,x.c_str(),sizeof(wstring)/sizeof(wchar_t));
//  if (r==(size_t)(-1)) return std::wstring();
  return std::wstring(wstring,wstring+res);
#endif
}

std::string WinFileReq::un_wstring(std::wstring const& x)
{
#if 0
  return ManuProC::un_wstring(x);
#else
  if (x.empty()) return std::string();
  char nstring[10240];
  int res= WideCharToMultiByte(CP_UTF8, 0, x.data(), x.size(), nstring, sizeof(nstring), NULL, NULL);
  assert(res!=0);
//  size_t r= wcstombs(nstring,x.c_str(),sizeof(nstring)/sizeof(char));
//  if (r==(size_t)(-1)) return std::string();
  return std::string(nstring,nstring+res);
#endif
}
#endif

WinFileReq::WinFileReq(const sigc::slot<void,const std::string &> &sl,
                std::string file, std::string filter,
                std::string extension, std::string title, bool load,
		Gtk::Window *parent, bool pass_cancel)
#ifndef __MINGW32__
	: slot(sl), call_on_cancel(pass_cancel), dont_delete()
#endif
{
   if (filter.size()>2 && filter.substr(filter.size()-3,3)!=std::string(3,char(0)))
     std::cerr << "Filter for " << title << " does not contain 3 trailing \\0\n";
#ifndef __MINGW32__
   set_filename(file);
   set_title(title);
   if (parent) set_transient_for(*parent);
#else
   std::string patsep(1,char(0));
   if (filter.empty() && !extension.empty() && !title.empty())
   {  filter=title+" (*."+extension+")"+patsep+"*."+extension+patsep+
           _("All Files (*.*)")+patsep+"*.*"+patsep+patsep+patsep;
   }
   if (filter.empty()) filter = _("All Files (*.*)")+patsep+"*.*"+patsep+patsep+patsep;
   // file is assumed to have UTF-8 encoding
   std::wstring wfile=make_wstring(file);
   std::wstring wtitle=make_wstring(title);

   std::wstring wfilter=make_wstring(filter);
   std::wstring wextension=make_wstring(extension);

   wchar_t buf[MAX_PATH];
   wcsncpy(buf,wfile.c_str(),sizeof(buf)/sizeof(wchar_t));

   if (wfilter.empty() && wextension.empty())
   // browse for a directory
   { BROWSEINFOW bi;
     ZeroMemory(&bi, sizeof(BROWSEINFOW));
     bi.hwndOwner = (HWND)GDK_WINDOW_HWND(parent->get_window()->gobj());
     bi.pszDisplayName = buf;
     bi.lpszTitle = wtitle.c_str();
     bi.ulFlags = BIF_EDITBOX | BIF_RETURNONLYFSDIRS;

     LPITEMIDLIST pidl=SHBrowseForFolderW(&bi);
     if (pidl)
     { // get the name of the folder
       if ( SHGetPathFromIDListW ( pidl, buf ) )
       { std::wstring wresult=buf;
         //TagStream::utf82iso(result);
         const_cast<sigc::slot<void,const std::string &>&>(sl)(un_wstring(wresult));
       }
        // free memory used
        IMalloc * imalloc = 0;
        if ( SUCCEEDED( SHGetMalloc ( &imalloc )) )
        {
            imalloc->Free ( pidl );
            imalloc->Release ( );
        }
     }
     else if (pass_cancel)
        const_cast<sigc::slot<void,const std::string &>&>(sl)(std::string());
     return;
   }

   OPENFILENAMEW ofn;

   ZeroMemory(&ofn, sizeof (OPENFILENAMEW));
   ofn.lStructSize = sizeof (OPENFILENAMEW);
   if (parent) ofn.hwndOwner = (HWND)GDK_WINDOW_HWND(parent->get_window()->gobj());
   ofn.lpstrFile = buf;
   ofn.nMaxFile = sizeof buf/sizeof(wchar_t);
   ofn.lpstrFilter=wfilter.c_str();
   ofn.nFilterIndex = 1;
   ofn.lpstrDefExt= wextension.c_str();
   ofn.lpstrTitle = wtitle.c_str();
   ofn.Flags = OFN_PATHMUSTEXIST
               | (load ? OFN_FILEMUSTEXIST : 0);
   if (!wfile.empty() && wfile[wfile.size()-1]=='\\')
   {  *buf=0;
      ofn.lpstrInitialDir = wfile.c_str();
   }

   bool res=false;
   char currentwd[MAX_PATH];
   getcwd(currentwd,sizeof(currentwd));
   if (load) res=GetOpenFileNameW(&ofn);
   else res=GetSaveFileNameW(&ofn);
   chdir(currentwd); // work around the fact that GetOpenFileName changes working dir

   if (res)
   { //std::string result=buf;
     //TagStream::utf82iso(result);
     const_cast<sigc::slot<void,const std::string &>&>(sl)(un_wstring(buf));
   }
   else if (pass_cancel)
      const_cast<sigc::slot<void,const std::string &>&>(sl)(std::string());
#endif
}

void WinFileReq::create(const sigc::slot<void,const std::string &> &sl,const std::string &file,
		std::string filter, std::string extension, std::string title, bool load,
		Gtk::Window *parent, bool pass_cancel)
{  (void)
#ifndef __MINGW32__
     new
#endif
       WinFileReq(sl,file,filter,extension,title,load,parent,pass_cancel);
}

static void sassign(std::string const& b, std::string * s)
{
  *s=b;
}

std::string WinFileReq::run(const std::string &file,
	std::string filter, std::string extension,
	std::string title, bool load,
	Gtk::Window *parent)
{
  std::string res;
  {
    WinFileReq rq(sigc::bind(sigc::ptr_fun(&sassign),&res),file,filter,extension,title,load,parent,false);
#ifndef WIN32
    rq.dont_delete=true;
    static_cast<Gtk::Dialog&>(rq).run();
    rq.hide();
#endif
  }
  return res;
}
