#! /usr/bin/env bash

VERSION=${1}
INSTALL_PREFIX=${2}

MAJOR=`echo ${VERSION} | cut -d. -f1`
MINOR=`echo ${VERSION} | cut -d. -f2`
REVISION=`echo ${VERSION} | cut -d. -f3`

case ${VERSION} in
  7.1.0|8.0.1)
    URL=https://github.com/llvm/llvm-project/releases/download/llvmorg-
    ;;
  *)
    URL=http://releases.llvm.org/
    ;;
esac

wget ${URL}${VERSION}/llvm-${VERSION}.src.tar.xz
wget ${URL}${VERSION}/libcxxabi-${VERSION}.src.tar.xz
wget ${URL}${VERSION}/libcxx-${VERSION}.src.tar.xz
mkdir -p llvm/projects/libcxxabi llvm/projects/libcxx
tar --strip-components=1 -xf llvm-${VERSION}.src.tar.xz -C llvm
tar --strip-components=1 -xf libcxxabi-${VERSION}.src.tar.xz -C llvm/projects/libcxxabi
tar --strip-components=1 -xf libcxx-${VERSION}.src.tar.xz -C llvm/projects/libcxx
mkdir llvm-build
cd llvm-build
cmake ../llvm \
    -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_C_COMPILER=${C_COMPILER} \
    -DCMAKE_CXX_COMPILER=${CXX_COMPILER} \
    -DCMAKE_INSTALL_PREFIX=${INSTALL_PREFIX} \
    -DLIBCXX_INSTALL_EXPERIMENTAL_LIBRARY=TRUE \
    -DLIBCXX_ENABLE_FILESYSTEM=TRUE
make cxx cxx_experimental
sudo make install-libcxxabi install-libcxx
cd ..
