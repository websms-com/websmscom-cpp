#!/usr/bin/env bash

GMOCK_VERSION="1.6.0"

this="$(readlink -f $0)"
scripts="${this%/*}"
root="${scripts}/../"
test="${root}/test/"

cd "${test}"
wget -N "https://googlemock.googlecode.com/files/gmock-$GMOCK_VERSION.zip"
unzip "gmock-$GMOCK_VERSION.zip"
mv "gmock-$GMOCK_VERSION" gmock
cd gmock/make
make gmock.a
