#!/bin/bash

cd ../..

if [ -d cmakefiles ]; then
    cd cmakefiles

else
    mkdir cmakefiles
    cd cmakefiles
fi

cmake .. -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug

cmake --build . -j$(nproc)

error_code=$? # to figure out if the build process was successfull or not.

if [ ${error_code} -ne 0 ]; then echo -e "build failed.\n"; else echo -e "build was successfull\n"; fi;

exit ${error_code}