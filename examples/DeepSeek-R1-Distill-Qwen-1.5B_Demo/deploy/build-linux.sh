#!/bin/bash
# Debug / Release / RelWithDebInfo
set -e
if [[ -z ${BUILD_TYPE} ]];then
    BUILD_TYPE=Release
fi

C_COMPILER=/usr/bin/gcc
CXX_COMPILER=/usr/bin/g++
STRIP_COMPILER=/usr/bin/strip

TARGET_ARCH=aarch64
TARGET_PLATFORM=linux
if [[ -n ${TARGET_ARCH} ]];then
TARGET_PLATFORM=${TARGET_PLATFORM}_${TARGET_ARCH}
fi

ROOT_PWD=$( cd "$( dirname $0 )" && cd -P "$( dirname "$SOURCE" )" && pwd )
BUILD_DIR=${ROOT_PWD}/build/build_${TARGET_PLATFORM}_${BUILD_TYPE}

if [[ ! -d "${BUILD_DIR}" ]]; then
  mkdir -p ${BUILD_DIR}
fi

cd ${BUILD_DIR}
cmake ../.. \
    -DCMAKE_SYSTEM_PROCESSOR=${TARGET_ARCH} \
    -DCMAKE_SYSTEM_NAME=Linux \
    -DCMAKE_C_COMPILER=${C_COMPILER} \
    -DCMAKE_CXX_COMPILER=${CXX_COMPILER} \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    -DCMAKE_POSITION_INDEPENDENT_CODE=ON

make -j4
# make install
