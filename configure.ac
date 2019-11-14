AC_INIT([gfourcc], [0.1.2])
AC_PREREQ([2.50])

AC_CONFIG_SRCDIR([src/main.cc])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([1.9 subdir-objects])
AM_MAINTAINER_MODE

# Checks for programs.
AC_PROG_CXX
AC_PROG_LN_S
AC_TYPE_SIGNAL
AC_HEADER_STDC
AX_CXX_COMPILE_STDCXX_11

# Check for pkg-config early to avoid splitting message when first used.
PKG_CHECK_EXISTS

# i18n stuff

GETTEXT_PACKAGE=gfourcc
AC_SUBST([GETTEXT_PACKAGE])
AC_DEFINE_UNQUOTED([GETTEXT_PACKAGE], "$GETTEXT_PACKAGE", [description])

AM_GLIB_GNU_GETTEXT
IT_PROG_INTLTOOL([0.36.0])

# GTKMM
PKG_CHECK_MODULES([GTKMM], [gtkmm-3.0 >= 3.0])
AC_SUBST([GTKMM_LIBS])
AC_SUBST([GTKMM_CFLAGS])

# Check for glibmm minimum required version.
PKG_CHECK_MODULES([GLIBMM], [glibmm-2.4 >= 2.0])

AC_CONFIG_FILES([
Makefile
src/Makefile
icons/Makefile
icons/hicolor/Makefile
icons/hicolor/48x48/Makefile
icons/hicolor/48x48/apps/Makefile])

AC_OUTPUT

