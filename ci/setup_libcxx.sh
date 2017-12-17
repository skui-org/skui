#! /usr/bin/env bash

VERSION=${1}

MAJOR=`echo ${VERSION} | cut -d. -f1`
MINOR=`echo ${VERSION} | cut -d. -f2`
REVISION=`echo ${VERSION} | cut -d. -f3`

wget http://llvm.org/releases/${VERSION}/llvm-${VERSION}.src.tar.xz
wget http://llvm.org/releases/${VERSION}/libcxxabi-${VERSION}.src.tar.xz
wget http://llvm.org/releases/${VERSION}/libcxx-${VERSION}.src.tar.xz
mkdir -p llvm/projects/libcxxabi llvm/projects/libcxx
tar --strip-components=1 -xf llvm-${VERSION}.src.tar.xz -C llvm
tar --strip-components=1 -xf libcxxabi-${VERSION}.src.tar.xz -C llvm/projects/libcxxabi
tar --strip-components=1 -xf libcxx-${VERSION}.src.tar.xz -C llvm/projects/libcxx
mkdir llvm-build
cd llvm-build
cmake ../llvm \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=clang-${MAJOR}.${MINOR} \
    -DCMAKE_CXX_COMPILER=clang++-${MAJOR}.${MINOR} \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DLIBCXX_INSTALL_EXPERIMENTAL_LIBRARY=TRUE \
    -DLIBCXX_ENABLE_FILESYSTEM=TRUE
make cxx cxx_experimental
sudo make install-libcxxabi install-libcxx
cd ..
