#!/bin/sh -e
# autogen.sh - Run this to generate all the initial makefiles, etc.
#

srcdir=`dirname $0`
test -z "$srcdir" && srcdir=.

which gnome-autogen.sh || {
    echo "You need to install gnome-common"
    exit 1
}

# Ensure that m4 directory exists
if ! test -d $srcdir/m4; then
	mkdir $srcdir/m4
fi

REQUIRED_AUTOMAKE_VERSION=1.9 . gnome-autogen.sh

