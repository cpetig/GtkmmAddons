# $Id: Makefile.am,v 1.14 2004/04/29 16:44:50 christof Exp $

CLEANFILES = *~

GTKMMTOOLS=$(HOME)/sourceforge/gtkmm-2.2/tools

AM_CPPFLAGS = -Wall -I. -I$(top_srcdir)/searchcombo/src @GTKMM_CFLAGS@ @MPC_BASE_INCLUDES@


if WINDOWS
WIN_LDFLAGS=@MPC_BASE_LDFLAGS@
DLL_LDADD=@MPC_BASE_LIBS@
else
WIN_LDFLAGS=
DLL_LDADD=
endif


lib_LIBRARIES = libManuProC_GtkmmAddons.a
libManuProC_GtkmmAddons_la_LIBADD=$(DLL_LDADD)

include_HEADERS = Gtk_OStream.h Message.h SearchCombo.h \
		SearchComboContent.h gtksearchcombo.h \
		TeX.h SelectMatching.h SigC2SlotEmu.h ja_nein_frage.hh \
		ja_nein_frage_glade.hh

libManuProC_GtkmmAddons_a_SOURCES = Gtk_OStream_label.cc \
		 Gtk_OStream_optionmenu.cc Gtk_OStream_stream.cc \
		 SearchCombo.cc TeX.cc Gtk_OStream.cc \
		 gtksearchcombo.c Gtk_OStream_TreeView.cc \
		 DoubleButton.cc gtkdoublebutton.c WinFileReq.cc \
		 ChoiceButton.cc gtkhacks.cc Gtk2TeX.cc \
		 expander_hook.c SearchCombo3.cc ja_nein_frage_glade.cc ja_nein_frage.cc
#SearchCombo2.cc

BUILT_SOURCES=SearchCombo.cc SearchCombo.h gtksearchcombo.c gtksearchcombo.h \
	gtkmm DoubleButton.h DoubleButton.cc gtkdoublebutton.c gtkdoublebutton.h \
	WinFileReq_glade.hh WinFileReq.hh ComboBoxMapping.hh

EXTRA_DIST=SearchCombo.hg SearchCombo.ccg private/SearchCombo_p.h \
	WinFileReq_glade.cc 

gtkmm:
	ln -sf . gtkmm


AM_LDFLAGS=@LDFLAGS@ $(WIN_LDFLAGS)

SearchCombo.cc SearchCombo.h: gtkmm SearchCombo.hg SearchCombo.ccg
	if [ ! -d private ] ; then mkdir private ; fi
#	echo perl -I$(GTKMMTOOLS)/pm $(GTKMMTOOLS)/gtkmmproc -I $(GTKMMTOOLS)/m4 --defs . SearchCombo . .
	echo /usr/lib/glibmm-2.4/proc/gmmproc --defs . SearchCombo . .

DoubleButton.cc DoubleButton.h: gtkmm DoubleButton.hg DoubleButton.ccg
	if [ ! -d private ] ; then mkdir private ; fi
#	echo perl -I$(GTKMMTOOLS)/pm $(GTKMMTOOLS)/gtkmmproc -I $(GTKMMTOOLS)/m4 --defs . DoubleButton . .
	echo /usr/lib/glibmm-2.4/proc/gmmproc --defs . DoubleButton . .

gtksearchcombo.h gtksearchcombo.c gtkdoublebutton.c gtkdoublebutton.h \
		: $(top_srcdir)/searchcombo/src/$@
	ln -sf $(top_srcdir)/searchcombo/src/$@ .

ComboBoxMapping.hh: ComboBoxMapping.h
	ln -sf $^ $@
