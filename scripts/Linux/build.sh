#!/bin/sh

cd ../..

if [ -d cmakefiles ]; then
    cd cmakefiles

else
    mkdir cmakefiles
    cd cmakefiles
fi

cmake .. -G"Unix Makefiles"

cmake --build . -j2

read -p "Press Enter to continue" var