#!/bin/sh

cd ../..

if [ -d cmakefiles ]; then
    cd cmakefiles

else
    mkdir cmakefiles
    cd cmakefiles
fi

cmake .. -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug

cmake --build . -j$(nproc)

read -p "Press Enter to continue" var