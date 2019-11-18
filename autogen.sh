#!/bin/sh -e
# autogen.sh - Run this to generate all the initial makefiles, etc.
#

autoreconf -f -i && automake -a -f
