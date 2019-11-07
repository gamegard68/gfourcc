#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([gfourcc], [0.1.2])
AC_CONFIG_AUX_DIR([.])
AM_INIT_AUTOMAKE(1.9 check-news foreign subdir-objects)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES])
AC_CONFIG_SRCDIR([src/])

# Extract host information.
AC_CANONICAL_HOST

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AM_PROG_CC_C_O
AC_CACHE_SAVE

# Recent versions of glib/gtkmm need c++11 support
AX_CXX_COMPILE_STDCXX_11

required_libs="gtkmm-3.0 >= 3.6.0"

###################################
# Check for libraries.
###################################

PKG_CHECK_MODULES([gfourcc], [$required_libs])
AC_CACHE_SAVE

###################################
# Output
###################################

AC_OUTPUT([
  Makefile
    m4/Makefile

    icons/Makefile
      icons/hicolor/Makefile
        icons/hicolor/48x48/Makefile
          icons/hicolor/48x48/apps/Makefile
      
])


