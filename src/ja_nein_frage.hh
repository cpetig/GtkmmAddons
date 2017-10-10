// generated 2011/6/30 11:53:48 CEST by christof@christof-hp.(none)
// using glademm V2.13.0
//
// newer (non customized) versions of this file go to ja_nein_frage.hh_new

// you might replace
//    class foo : public foo_glade { ... };
// by
//    typedef foo_glade foo;
// if you didn't make any modifications to the widget

#ifndef _JA_NEIN_FRAGE_HH
#  include "ja_nein_frage_glade.hh"
#  define _JA_NEIN_FRAGE_HH

#include <gdk/gdk.h>

class ja_nein_frage : public ja_nein_frage_glade
{
    guint m_yes_key;
    guint m_no_key;

    bool on_key_release_event(GdkEventKey *ev);

public:
    ja_nein_frage();
    ja_nein_frage(const guint yes_key_event, const guint no_key_event);
};

#endif // _JA_NEIN_FRAGE_HH
