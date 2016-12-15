#!/bin/bash

git clone https://github.com/rochus/qt5-node-editor.git
git clone https://github.com/mbasaglia/Qt-Color-Widgets.git

cd kf5
bash ./build.sh
cd ..

mkdir mbuild -p
cd mbuild
bash ../apk.sh

make -j8
make create-apk-foo ARGS="--install"
