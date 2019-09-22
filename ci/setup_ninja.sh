#! /usr/bin/env bash
set -e

VERSION=${1}
OS=${2}

wget https://github.com/ninja-build/ninja/releases/download/v${VERSION}/ninja-${OS}.zip
mkdir ninja
unzip ninja-${OS}.zip -d ninja
export PATH=${PWD}/ninja:${PATH}
