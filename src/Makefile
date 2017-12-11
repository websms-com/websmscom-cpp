
include ../project.mk

LIBNAME := lib$(NAME)
LIBRARY := $(LIBNAME).so.$(MAJOR).$(MINOR)
VERSION := $(LIBNAME) $(MAJOR).$(MINOR)
SOURCES := $(wildcard *.cc)
OBJS := $(patsubst %.cc, %.o, $(SOURCES))
INCLUDE := -I../include
LIBS := -lcurl -ljansson
PREFIX := /usr/local
CXX := g++
CXXFLAGS := -Werror -Wall -Wextra -pedantic -Weffc++ \
	-Wno-variadic-macros \
	-DVERSION="\"$(VERSION)\""

$(LIBRARY): $(OBJS)
	$(CXX) -shared -Wl,-soname,$(LIBNAME).so.$(MAJOR) \
	-o $(LIBRARY) $(OBJS) $(LIBS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) -fPIC -c $< -o $@

debug: CXXFLAGS += -g -DDEBUG
debug: $(LIBRARY)

main: main.cc
	$(CXX) $(CXXFLAGS) $(INCLUDE) main.cc -o main $(LIBRARY)

version:
	@echo $(VERSION)

install:
	install -m 755 -d $(PREFIX)/include/$(NAME)/
	install -m 644 ../include/$(NAME)/*.h $(PREFIX)/include/$(NAME)
	install -m 755 -d $(PREFIX)/lib/
	install -m 644 -s $(LIBRARY) $(PREFIX)/lib/
	ln -s $(LIBRARY) $(PREFIX)/lib/$(LIBNAME).so.$(MAJOR)
	ln -s $(LIBRARY) $(PREFIX)/lib/$(LIBNAME).so
	ldconfig

uninstall:
	rm -rf $(PREFIX)/include/$(NAME)/
	rm -rf $(PREFIX)/lib/$(LIBNAME).*

clean:
	rm -f *.o *.so $(LIBRARY) main

check-syntax:
	$(CXX) -o /dev/null -S ${CHK_SOURCES}

.PHONY: clean debug install uninstall version
