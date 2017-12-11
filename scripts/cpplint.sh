#!/usr/bin/env bash

this="$(readlink -f $0)"
scripts="${this%/*}"
root="${scripts}/../"

find "${root}"/{src,include} -name "*.cc" -or -name "*.h" \
    -exec "${scripts}/cpplint.py" --filter=-build/header_guard {} \;
