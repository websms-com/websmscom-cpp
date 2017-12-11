
include project.mk

PACKAGE=CPP_SMS_Toolkit-$(MAJOR).$(MINOR).$(REVISION)

default:
	make -C src

debug:
	make -C src debug

clean:
	rm -rf Debug tmp
	rm -f *.zip
	make -C src clean
	make -C examples clean
	make -C test clean

install:
	make -C src install

uninstall:
	make -C src uninstall

doc:
	rm -rf doc/sdk
	mkdir -p doc
	doxygen

dist: clean doc
	rm -rf $(PACKAGE)
	mkdir $(PACKAGE)
	cp COPYING INSTALL README $(PACKAGE)
	cp Doxyfile Makefile project.mk $(PACKAGE)
	cp .project .cproject $(PACKAGE)
	cp -r doc examples include src win32 $(PACKAGE)
	zip -9 -r $(PACKAGE).zip $(PACKAGE)
	rm -rf $(PACKAGE)

.PHONY: clean debug default dist doc install uninstall zip
