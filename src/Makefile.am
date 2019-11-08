desktopdir = $(datadir)/applications

bin_PROGRAMS=gfourcc
desktop_in_files=gfourcc.desktop.in
desktop_DATA=$(desktop_in_files:.desktop.in=.desktop)

gfourcc_SOURCES= \
  gfourcc_application.h gfourcc_application.cc \
  gfourcc_window.h gfourcc_window.cc \
  main.cc

gfourcc_LDADD=$(AM_LDADD) $(GUILIBS_LIBS)
gfourcc_CXXFLAGS=$(AM_CXXFLAGS) $(GUILIBS_CFLAGS)

EXTRA_DIST = $(desktop_in_files)

CLEANFILES = $(desktop_DATA)

@INTLTOOL_DESKTOP_RULE@

