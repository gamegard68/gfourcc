dnl Process this file with autoconf to produce a configure script.

AC_INIT([gfourcc],[0.1.4-git])
AC_PREREQ([2.13])


AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_HEADERS(config.h)
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_FILES([Makefile])

dnl -----------------------------------------------
dnl Package name and version number (user defined)
dnl -----------------------------------------------

PACKAGE=gfourcc
VERSION=0.1.4

dnl -----------------------------------------------
dnl Package name and version number (DO NOT MODIFY)
dnl -----------------------------------------------

AM_INIT_AUTOMAKE(1.9)

ACLOCAL_AMFLAGS='${ACLOCAL_FLAGS}'
AC_SUBST(ACLOCAL_AMFLAGS)

dnl Checks for programs.
AC_PROG_CXX
AC_PROG_CC

dnl Checks for libraries.
PKG_CHECK_MODULES(GTKMM, gtkmm-3.0 >= 3.24)
AC_SUBST(GTKMM_CFLAGS)
AC_SUBST(GTKMM_LIBS)

dnl Enable C++11 compilation.
AX_CXX_COMPILE_STDCXX_11()

dnl Create makefiles
AC_OUTPUT
