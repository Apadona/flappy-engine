@echo off

cd ..

if NOT exist cmakefiles mkdir cmakefiles
cd cmakefiles

cmake .. -G"MinGW Makefiles"

cmake --build .

pause