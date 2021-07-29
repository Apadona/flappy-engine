@echo off

setlocal 
    path=dependencies\lib\glfw\32;%path%
    gdb "bin/flappy_bird.exe"
endlocal
