#! /usr/bin/env bash
set -e

VERSION=${1}

wget https://github.com/linux-test-project/lcov/releases/download/v${VERSION}/lcov-${VERSION}.tar.gz
mkdir lcov
tar -xf lcov-${VERSION}.tar.gz
cd lcov-${VERSION}/
make install PREFIX=${PWD}/../lcov
cd ..
export PATH=${PWD}/lcov/bin:${PATH}
