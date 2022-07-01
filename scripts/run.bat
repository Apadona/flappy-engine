@echo off

cd ..

setlocal 
    path=dependencies\lib\glfw\32;%path%
    "build/bin/engine.exe"
endlocal
