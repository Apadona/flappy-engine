#!/bin/bash

cd ../..

if [ -d cmakefiles ]; then
    cd cmakefiles

else
    mkdir cmakefiles
    cd cmakefiles
fi

if [ `uname -m` -eq "x86_64" ]; then 
    cmake .. -G"Unix Makefiles" -D"architecture_64"
else
    cmake .. -G"Unix Makefiles"
fi

cmake --build . -j$(nproc)

error_code=$? # to figure out if the build process was successfull or not.

if [ ${error_code} -ne 0 ]; then echo -e "build failed.\n"; else echo -e "build was successfull\n"; fi;

exit ${error_code}