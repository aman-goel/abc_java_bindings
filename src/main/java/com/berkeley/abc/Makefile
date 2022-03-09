#
# Makefile to build libabc2java.dylib or libabc2java.so
#
# Call with
#    make OS=darmin
# or make OS=linux
#
# We assume gmake
# We also assume that jni.h is installed in ${JAVA_HOME}/include,
# jni_md.h is in ${JAVA_HOME}/include/${OS}, and that ${ABC_JNI} exists
#

SHELL=/bin/bash

ifneq ($(MAKECMDGOALS),clean)

ifeq ($(OS),)
 guess=$(shell uname)
 ifeq ($(guess),Darwin)
  OS := darwin
 else
 ifeq ($(guess),Linux)
  OS := linux
 endif
 endif
endif

ifeq ($(OS),linux)
 EXTENSION=so
else
ifeq ($(OS),darwin)
 EXTENSION=dylib
else
ifeq ($(OS),)
 $(error "Please set $$OS")
else
 $(error "Unkown OS: $(OS)")
endif
endif
endif

ifneq ($(MAKECMDGOALS),install)
ifeq ($(JAVA_HOME),)
 $(error "Please set $$JAVA_HOME")
endif
endif

endif

# name of the library
libabc2java := libabc2java.$(EXTENSION)

# install name for darwin
libabc2java_install_name := $(ABC_JNI)/libabc2java.dylib

# we ignore versions and soname for now

# default include directories for jni.h and jni_md.h
CPPFLAGS := -I $(JAVA_HOME)/include -I $(JAVA_HOME)/include/$(OS)
CXXFLAGS := -g -fPIC

CXX ?= g++


# JAVAC to compile the java
JAVAC ?= javac

# these defaults are for the ant build, and
# should/will be overidden when using the build.sh
ABC_CLASSPATH?=../../../../../../build/classes
ABC_JNI?=../../../../../../dist/lib
ABC_PATH?=../../../../../../../abc

libabc := $(ABC_PATH)/libabc.a
LIBS := $(libabc) -lm -ldl -lreadline -lpthread


all: $(libabc2java)

$(ABC_CLASSPATH)/com/berkeley/abc/%.class: %.java
	$(JAVAC) -d $(ABC_CLASSPATH) *.java

com_berkeley_abc_Abc.h: $(ABC_CLASSPATH)/com/berkeley/abc/Abc.class
	$(JAVAC) -h . *.java

abcJNI.o: abcJNI.cpp com_berkeley_abc_Abc.h
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -Wall -c -DABC_USE_STDINT_H -I $(ABC_PATH)/src abcJNI.cpp

libabc2java.dylib: abcJNI.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -dynamiclib -o $@ abcJNI.o $(LIBS)

libabc2java.so: abcJNI.o
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -shared -o $@ abcJNI.o $(LIBS)

LIBDIR := $(ABC_JNI)

install: install-$(OS)

install-linux:
	cp $(libabc2java) $(LIBDIR)
	ldconfig -n $(LIBDIR)

install-darwin:
	cp $(libabc2java) $(LIBDIR)

clean:
	rm -f *.o *.so *.dylib com_berkeley_abc_Abc.h *.class

.PHONY: all clean install install-linux install-darwin 
