@echo off

cd ..

if NOT exist build mkdir build
cd build

cmake .. -G"MinGW Makefiles"

cmake --build .

pause