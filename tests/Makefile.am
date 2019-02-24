# $Id: Makefile.am,v 1.11 2004/08/30 07:35:07 christof Exp $

SUBDIRS=close_window
GADDON_LIBS=$(top_srcdir)/src/libManuProC_GtkmmAddons.a

AM_CXXFLAGS=-I$(top_srcdir)/searchcombo/src -I$(top_srcdir)/src

EXTRA_PROGRAMS = nsc_test sccont_test optionmenu db_test back_test \
	callbackbuf wfr_test treeview treeview_tree ComboBoxMapping \
	ec_test sccont3_test gsc_test

back_test_SOURCES = back_test.cc db_embed.cc
back_test_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

sccont_test_SOURCES = sccont_test.cc
sccont_test_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

sccont3_test_SOURCES = sccont3_test.cc
sccont3_test_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

nsc_test_SOURCES = nsc_test.cc
nsc_test_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

wfr_test_SOURCES = wfr_test.cc
wfr_test_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

db_test_SOURCES = db_test.cc db_embed.cc
db_test_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

optionmenu_SOURCES = optionmenu.cc
optionmenu_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

treeview_SOURCES = treeview.cc
treeview_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

treeview_tree_SOURCES = treeview_tree.cc
treeview_tree_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

callbackbuf_SOURCES = callbackbuf.cc
callbackbuf_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

ComboBoxMapping_SOURCES = ComboBoxMapping.cc
ComboBoxMapping_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

INCLUDES = -I$(top_srcdir)/searchcombo/src -I$(top_srcdir)/src @GTKMM_CFLAGS@ 
#AM_LDFLAGS = @GTKMM2_LDFLAGS@

ec_test_SOURCES = ec_test.cc
ec_test_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@

gsc_test_SOURCES = ../searchcombo/tests/gsc_test.c
gsc_test_LDADD = $(GADDON_LIBS) @GTKMM_LIBS@
