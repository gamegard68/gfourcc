SUBDIRS = m4 . icons

# Tell aclocal where to find `.m4' files.
ACLOCAL_AMFLAGS = -I m4

dist_man_MANS = gfourcc-0.1.2

bin_PROGRAMS = gfourcc-0.1

noinst_HEADERS =
gfourcc_0_1_SOURCES =
BUILT_SOURCES =

EXTRA_DIST =
CLEANFILES =
DISTCLEANFILES =
MAINTAINERCLEANFILES =

include src/Makefile.am

gfourcc_0_1_LDADD = \
	$(gfourcc_LIBS) \
	$(LIBS)


# PRIVATE_ICONS_DIR is required by application.cpp to get access to the
# private icons that are installed into prefix/share/gobby-0.5/icons instead
# of prefix/share/icons. We also set PUBLIC_ICONS_DIR explicitely so that
# we find the application icon if it is installed in a non-standard prefix.
AM_CPPFLAGS = $(gfourcc) -I$(top_srcdir)/src \
              -DPRIVATE_ICONS_DIR=\""$(datadir)/gfourcc-0.1/icons"\" \
              -DPUBLIC_ICONS_DIR=\""$(datadir)/icons"\"

# .desktop file
desktopdir = $(datadir)/applications
desktop_in_files = gfourcc-0.1.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

appdatadir = $(datadir)/appdata
appdata_DATA = gfourcc-0.1.appdata.xml

gsettings_SCHEMAS = be.gamegard68.gfourcc.gschema.xml

EXTRA_DIST += de.gamegard68.gfourcc.gschema.xml.in
CLEANFILES += de.gamegard68.gfourcc.gschema.xml
DISTCLEANFILES += de.gamegard68.gfourcc.gschema.xml
MAINTAINERCLEANFILES += $(gsettings_SCHEMAS:.xml=.valid)

@GSETTINGS_RULES@

clean-local:
	-rm -rf gfourcc-0.1.desktop

@INTLTOOL_DESKTOP_RULE@

EXTRA_DIST += README.md

# Debian seems to need an XPM of the program icon, so we provide one here.
# It's currently not used for anything else, though.
EXTRA_DIST += gfourcc-0.1.xpm

# For the manual
EXTRA_DIST += gfourcc-0.1.desktop.in gfourcc-0.1.appdata.xml
DISTCLEANFILES += gnome-doc-utils.make
DISTCHECK_CONFIGURE_FLAGS = --disable-scrollkeeper

MAINTAINERCLEANFILES += \
	ChangeLog

distclean-local:
	if test "$(srcdir)" = "."; then :; else \
		rm -f ChangeLog; \
	fi

ChangeLog:
	$(AM_V_GEN) if test -d "$(srcdir)/.git"; then \
	  (GIT_DIR=$(top_srcdir)/.git ./missing --run git log \
		6570cc49a6c2c29fe9cf4c85e3b74f133ae4c1f8..HEAD --stat=78) \
		| fmt --split-only --width=78 > $@.tmp \
	  && cat $@.tmp ChangeLog.manual ChangeLog.pre-0.1 > $@ && $(RM) $@.tmp \
	  || ($(RM) $@.tmp; \
	      echo Failed to generate ChangeLog, your ChangeLog may be outdated >&2; \
	      (test -f $@ || echo git-log is required to generate this file >> $@)); \
	else \
	  test -f $@ || \
	  (echo A git checkout and git-log is required to generate ChangeLog >&2 && \
	  echo A git checkout and git-log is required to generate this file >> $@); \
	fi

.PHONY: ChangeLog

