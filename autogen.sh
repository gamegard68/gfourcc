#!/bin/sh -e
# autogen.sh - Run this to generate all the initial makefiles, etc.
#
#  Copying and distribution of this file, with or without modification,
#  are permitted in any medium without royalty provided the copyright
#  notice and this notice are preserved.  This file is offered as-is,
#  without any warranty.

glib-gettextize --copy --force
intltoolize --copy --force --automake

autoreconf -f -i && automake -a -f
