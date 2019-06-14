# Makefile for the guest operating system cuda libraries.
#
# Source: http://www.gnu.org/software/make/manual/make.html
#
# Real name: 	lib<name>.so.<so_version>.<so_minor>.<so_release>
# Soname:		lib<name>.so.<so_version>		
# Soname links to real name, latest real-name version
#
# Targets have both CFLAGS and CXXFLAGS defined. This is because
# I have been switching between compiling with C and C++ code.

# Installation variables
# ++++++++++++++++++++++
prefix=/usr/local
exec_prefix=$(prefix)
bindir=$(exec_prefix)/bin
includedir=$(prefix)/include
libdir=$(exec_prefix)/lib
# ++++++++++++++++++++++

SHELL = /bin/sh
SO_VERSION 	?= 	0
SO_MINOR	?=	0
SO_RELEASE	?=	1
VERSION = $(SO_VERSION).$(SO_MINOR).$(SO_RELEASE)
LIBNAME = fakecuda
LIB_FACU_VIRSER_OBJS = virtCudaLib.o transfer-virtio-serial.o
HEADERS = transfer.h faCuda.h

CC=g++

# Dependencies
-include $(wildcard .*.d)

# We want to generate dependency information
#
# Override the default rule to compile c sources with 
# another, that also creates dependencies
%.o:%.c
	$(CC) -nostartfiles $(CFLAGS) $< -pthread -o $@
	$(CC) -nostartfiles $(CFLAGS) -M $< > .$*.d

%.o:%.cpp
	$(CC) $(CXXFLAGS) $< -o $@
	$(CC) $(CXXFLAGS) -M $< > .$*.d

# Must run user and lib make target separately
all: lib

# Attempted to separate into two stages; compiling user.o first then linking it.
# But get error that it cannot find the entry point symbol..
user: CFLAGS = -g -I /usr/local/cuda/include -lfakecuda -o user
user: CXXFLAGS = -g -I /usr/local/cuda/include -lfakecuda -o user

# Variables and their associated values are passed down prerequisites
#
# They override any other target-specific variable values for that same
# variable name
lib: CFLAGS = -g -w -pg -fPIC -c -I/usr/local/cuda/include
lib: CXXFLAGS = -g -w -pg -fPIC -c -I/usr/local/cuda/include
lib: libfacuvirser.so.$(VERSION)

libfacuvirser.so.$(VERSION): $(LIB_FACU_VIRSER_OBJS)
	$(CC) -shared -Wl,-soname,libfacuvirser.so.$(SO_VERSION) -o libfacuvirser.so.$(VERSION) $(LIB_FACU_VIRSER_OBJS)

install: lib
	cp libfacuvirser.so.$(VERSION) $(libdir)
	ldconfig
	link $(libdir)/libfacuvirser.so.$(SO_VERSION) $(libdir)/libfacuvirser.so

uninstall:
	rm -f $(libdir)/libfacuvirser.so.$(VERSION)
	ldconfig
	rm -f $(libdir)/libfacuvirser.so

reinstall: uninstall install

clean:
	@rm -f *.o
	@rm -f lib$(LIBNAME).so*
	@rm -f user
	@rm -f $(wildcard .*.d)

help:
	@echo "Makefile for the fake Cuda library." \
		"\n-> Override *_VERSION variables or edit Makefile to adjust current development version." \
		"\n-> Override INSTALL_DIR or edit Makefile to change installation folder." \
		"\nValid targets:" \
		"\n\tlib\tCompiles the library object file according to versioning information. "\
		"\n\tinstall\tInstalls the library and runs ldconfig."\
		"\n\tuser\tCompiles the user.c files for testing."
	
.PHONY: all lib help clean install uninstall reinstall
