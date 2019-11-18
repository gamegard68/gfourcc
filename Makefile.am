ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src

# Icon
icondir			= $(datadir)/icons/hicolor/48x48/apps/
icon_DATA		= gfourcc.png

desktopdir = $(datadir)/applications
desktop_DATA = gfourcc.desktop

# Substitute variables in a Desktop Entry file.
gfourcc.desktop: gfourcc.desktop.in
	$(AM_V_GEN) sed -e 's|@bindir[@]|$(bindir)|g' $< > $@

EXTRA_DIST =				\
	autogen.sh				\
	gfourcc.png				\
	gfourcc.desktop.in

CLEANFILES = $(bin_PROGRAMS) gfourcc.desktop

