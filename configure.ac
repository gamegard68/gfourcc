#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.62)
AC_INIT([gfourcc], [0.1.2])
AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign 1.11 -Wall dist-xz tar-ustar])
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_CXX
# AC_PROG_CC
AC_PROG_LN_S
AC_TYPE_SIGNAL
AC_HEADER_STDC
AX_CXX_COMPILE_STDCXX_11

PKG_CHECK_MODULES(GUILIBS, [ gtkmm-3.0 >= 3.0 sigc++-2.0 ])
AC_SUBST(GUILIBS_CFLAGS)
AC_SUBST(GUILIBS_LIBS)

AC_CONFIG_FILES([
Makefile
src/Makefile
icons/Makefile
icons/hicolor/Makefile
icons/hicolor/48x48/Makefile
icons/hicolor/48x48/apps/Makefile])

AC_OUTPUT

