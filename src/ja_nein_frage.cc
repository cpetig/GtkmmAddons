// generated 2011/6/30 11:53:48 CEST by christof@christof-hp.(none)
// using glademm V2.13.0
//
// newer (non customized) versions of this file go to ja_nein_frage.cc_new

#include <gdk/gdk.h>

#include "ja_nein_frage.hh"

bool ja_nein_frage::on_key_release_event(GdkEventKey *ev)
{
    if(ev->type != GDK_KEY_RELEASE)
        return true;

    if(ev->keyval == m_yes_key)
        response(Gtk::RESPONSE_YES);
    else if(ev->keyval == m_no_key)
        response(Gtk::RESPONSE_NO);

    return true;
}

ja_nein_frage::ja_nein_frage() : m_yes_key(0), m_no_key(0)
{
}

ja_nein_frage::ja_nein_frage(const guint yes_key_event, const guint no_key_event) 
    : m_yes_key(0), m_no_key(0)

{
    if(yes_key_event)
        m_yes_key = yes_key_event;
    if(no_key_event)
        m_no_key = no_key_event;
        
    if(m_yes_key || m_no_key)
        {
            signal_key_release_event().connect(sigc::mem_fun(*this, &ja_nein_frage::on_key_release_event), false);
        }
}

