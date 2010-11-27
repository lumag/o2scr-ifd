readerconfdir = $(sysconfdir)/reader.conf.d/
readerconf_DATA = o2scr
noinst_DATA = o2scr-ni

EXTRA_DIST = o2scr.in

CLEANFILES = $(readerconf_DATA) $(noinst_DATA)

o2scr: $(srcdir)/o2scr.in Makefile
	rm -f $@ $@.tmp
	$(SED) -e 's|@libdir[@]|$(libdir)|g' $< > $@.tmp
	mv $@.tmp $@

o2scr-ni: $(srcdir)/o2scr.in Makefile
	rm -f $@ $@.tmp
	$(SED) -e 's|@libdir[@]|$(abs_top_builddir)/src/.libs|g' $< > $@.tmp
	mv $@.tmp $@
