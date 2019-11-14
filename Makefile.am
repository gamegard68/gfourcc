# Tell aclocal where to find `.m4' files.
ACLOCAL_AMFLAGS = -I m4

SUBDIRS=src icons

@INTLTOOL_DESKTOP_RULE@
DESKTOP_IN_IN_FILES = gfourcc.desktop.in.in
DESKTOP_IN_FILES = gfourcc.desktop.in
DESKTOP_FILES =$(DESKTOP_IN_FILES:.desktop.in=.desktop)
desktopdir = $(datadir)/applications
desktop_DATA = $(DESKTOP_FILES)

bin_PROGRAMS=gfourcc
CLEANFILES = $(bin_PROGRAMS) $(DESKTOP_IN_FILES)

gfourcc.desktop.in:  gfourcc.desktop.in.in Makefile
	$(do_subst) < $(srcdir)/gfourcc.desktop.in.in > gfourcc.desktop.in

EXTRA_DIST =			\
	$(DESKTOP_IN_IN_FILES)	\
	$(DESKTOP_FILES)	\
	intltool-extract.in  	\
	intltool-merge.in	\
	intltool-update.in	\
	gfourcc.in

DISTCLEANFILES =		\
	$(desktop_DATA)		\
	intltool-extract	\
	intltool-merge		\
	intltool-update
