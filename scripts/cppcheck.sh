#!/usr/bin/env bash

this="$(readlink -f $0)"
scripts="${this%/*}"
root="${scripts}/../"

cppcheck "${root}"/{src,include} --enable=all
