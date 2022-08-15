@echo off

cd ../..

for /f %%i in ('wmic cpu get NumberOfLogicalProcessors') do set number_of_cores=%%i

if NOT exist cmakefiles mkdir cmakefiles
cd cmakefiles

cmake .. -G"MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug

cmake --build . -j%number_of_cores%

pause