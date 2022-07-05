@echo off

cd ../..

if NOT exist cmakefiles mkdir cmakefiles
cd cmakefiles

cmake .. -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug

cmake --build . -j2

pause