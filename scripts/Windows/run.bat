@echo off

cd ../..

if /I %PROCESSOR_ARCHITECTURE% == "x86"     set system_architecture=32
if /I %PROCESSOR_ARCHITECTURE% == "AMD64"   set system_architecture=64

setlocal
    "build/bin/windows/%system_architecture%/engine.exe" %*
endlocal
