# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_sounddir      Where system sounds should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

APPSDIR = $(kde_appsdir)/Utilities
INCLUDES= $(all_includes)

SUBDIRS = html pics data

bin_PROGRAMS = kdewizard
bin_SCRIPTS = kprintwrapper krunonce

kdewizard_SOURCES = main.cpp toplevel.cpp themepage.cpp theme.cpp \
			intropage.cpp linkpage.cpp drivepage.cpp \
			printerpage.cpp

kdewizard_METASOURCES = USE_AUTOMOC
kdewizard_LDFLAGS = $(all_libraries) $(KDE_RPATH)

kdewizard_LDADD   = -lkfm -lkdeui -lkdecore -lqt -lXext -lX11 $(LIBSOCKET) \
			-lkhtmlw -lkimgio -ljpeg -ltiff -lpng -lm -ljscript -lz
DISTCLEANFILES = $()

THEMESDIR = $(kde_datadir)/kdewizard/Themes

install-data-local: install-themes

install-themes:
	$(mkinstalldirs) $(THEMESDIR)
	$(INSTALL_DATA) themes/Template.themerc $(THEMESDIR)
	cd themes; \
	for f in *; do \
	  if [ -d $$f -a $$f != "CVS" ]; then \
	    tar --exclude CVS -c -f - $$f | gzip -c > $(THEMESDIR)/$$f.tar.gz; \
	  fi; \
	done
	$(mkinstalldirs) $(kde_datadir)/kdewizard
	$(INSTALL_DATA) theme.mappings $(kde_datadir)/kdewizard

install-data-local: 
	$(mkinstalldirs) $(APPSDIR)
	$(INSTALL_DATA) kdewizard.kdelnk $(APPSDIR)
	$(mkinstalldirs) $(kde_icondir)
	$(INSTALL_DATA) wizard.xpm $(kde_icondir)

uninstall-local:
	-rm -f $(APPSDIR)/kdewizard.kdelnk

