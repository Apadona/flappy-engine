@echo off

if NOT exist build mkdir build
cd build

cmake .. -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug

cmake --build .

pause