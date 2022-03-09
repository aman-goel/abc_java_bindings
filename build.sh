#!/bin/bash

set -e

function error() {
    echo "**********************************************************************"
    echo "*********************  ERROR OCCURED !!!! ****************************"
    echo "**********************************************************************"
    echo "$1"
    echo "**********************************************************************"
    exit -1;
}

if [ $EUID -eq 0 ]; then echo "Should not run this script as root"; exit -1; fi

# Abc PATH
if [[ -z "$ABC_PATH" ]]; then
    echo "Please set environment variable ABC_PATH where the abc is already built."
    exit -1
fi

# Abc JNI
if [[ -z "$ABC_JNI" ]]; then
    echo "Please set environment variable ABC_JNI where the libabc2java dynamic library will live."
    exit -1
fi

# Abc CLASSPATH
if [[ -z "$ABC_CLASSPATH" ]]; then
    echo "Please set environment variable ABC_CLASSPATH where the abc java classes will live."
    exit -1
fi

echo
echo "Building the Abc2Java wrapper..."

if [[ ( ! -z "$ABC_JNI")  &&  ( ! -d "$ABC_JNI" ) ]] ; then
    echo "Creating directory ${ABC_JNI}"
    (mkdir -p $ABC_JNI || (echo "Failed to create directory ${ABC_JNI}" ; exit -1 ))
fi

if [[ ( ! -z "$ABC_CLASSPATH")  &&  ( ! -d "$ABC_CLASSPATH" ) ]] ; then
    echo "Creating directory ${ABC_CLASSPATH}"
    (mkdir -p $ABC_CLASSPATH || (echo "Failed to create directory ${ABC_CLASSPATH}" ; exit -1 ))
fi

cd ./src/main/java/com/berkeley/abc/

if CLASSPATH=${ABC_CLASSPATH} make && make install ; then
    echo "Installed the Abc2Java wrapper in ${ABC_JNI}"
else
    echo "Could not install the Abc2Java wrapper"
    exit -1
fi
echo "DONE"


