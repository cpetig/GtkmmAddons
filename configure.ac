## $Id: configure.in,v 1.14 2005/09/14 08:17:11 christof Exp $
#
# process this file with GNU autoconf to produce a configure script.
#
# parts taken from glade--, guppi2

AC_PREREQ(2.50)
AC_INIT(GtkmmAddons,1.3.0,[manuproc-developer-de@berlios.de])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS(config.h)

AC_PREFIX_DEFAULT(/usr/local)

AC_PROG_CC
AC_PROG_CXX
AM_PROG_LIBTOOL
AC_LANG_CPLUSPLUS


if echo __MINGW32__ | $CPP - - | fgrep -q __MINGW32__
then mingw=false
else mingw=true 
fi
AM_CONDITIONAL(WINDOWS, test x$mingw = xtrue)

AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(CXXFLAGS)

AC_HEADER_STDC

MPC_CHECK_BASE

PKG_CHECK_MODULES(GTKMM,[gtkmm-2.4 >= 2.4.0],
	[PKG_CHECK_MODULES(SIGC,[sigc++-2.0 >= 2.0.1])],
	[PKG_CHECK_MODULES(GTKMM,[gtkmm-2.0 >= 1.3.20])])

MPC_GTKMMADDONS_INCLUDES="$MPC_BASE_INCLUDES -I\$(top_srcdir)/src"   
MPC_GTKMMADDONS_LDFLAGS="$MPC_BASE_LDFLAGS"
MPC_GTKMMADDONS_LIBS="$MPC_BASE_LIBS"
AC_SUBST(MPC_GTKMMADDONS_INCLUDES)
AC_SUBST(MPC_GTKMMADDONS_LDFLAGS)
AC_SUBST(MPC_GTKMMADDONS_LIBS)

#dnl LATEX stuff
#m4_include(latex.m4)

#AC_PROG_LATEX
#AC_LATEX_PACKAGE(helvetic,article,has_helvetic)
#if test "$has_helvetic" = "yes"
#then
#  AC_DEFINE(HAS_HELVETIC,[],[whether the latex installation has helvetic.sty])
#fi

#AC_MSG_CHECKING([for utf8x encoding in latex])
#_AC_LATEX_TEST([
#\documentclass{article}
#\usepackage[utf8x]{inputenc}
#\begin{document}
#\end{document}
#],has_utf8x)
#AC_MSG_RESULT_UNQUOTED([$has_utf8x])
#if test "$has_utf8x" = "yes"
#then AC_DEFINE(HAS_UTF8X, [], [whether the latex installation has encoding utf8x])
#fi

AC_OUTPUT(Makefile src/Makefile tests/Makefile tests/close_window/Makefile)
