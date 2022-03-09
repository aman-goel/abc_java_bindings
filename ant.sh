#!/bin/bash

#uses the build.sh to mimic what 'ant install' does without 'ant'
REPO_ROOT=${PWD}

AP=${REPO_ROOT}/../abc
AC=${REPO_ROOT}/build/classes
AI=${REPO_ROOT}/dist/lib


rm -rf ${AC} ${AI}
cd ./src/main/java/com/berkeley/abc/
make clean

cd ${REPO_ROOT}
ABC_PATH=${AP} ABC_CLASSPATH=${AC} ABC_JNI=${AI} ./build.sh

cd ${AC}
jar -cvfm ${AI}/abc.jar ${REPO_ROOT}/MANIFEST.txt com/berkeley/abc/*.class

cd ${AI}
java -Djava.library.path=. -jar abc.jar

cd ${REPO_ROOT}

cp dist/lib/libabc2java.* ~/Library/Java/Extensions/
cp dist/lib/abc.jar ~/work/ws/eclipse/P/Src/PRuntimes/PSymbolicRuntime/lib/
