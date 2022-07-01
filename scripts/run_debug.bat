@echo off

cd ..

setlocal 
    path=dependencies\lib\glfw\32;%path%
    gdb "build/bin/engine.exe"
endlocal
