#!/bin/bash

rm -rf source/lib/*
qmake -r "CONFIG+=release"
make clean
make
rm -rf build/*
cp -a source/config/ build/
cp -a source/db/ build/
cp -a source/lib/ build/
cp source/controllers/ext_libs/arm/* build/lib/
cp -a source/plugin/ build/
cp -a source/public/ build/
cp -a source/sql/ build/
