#### Flappy engine

simple 2D engine C++/glfw/OpenGL.

For compiling the project, you need to have:

### gcc ( that supports C++17 )
### cmake( atleast 3.16 ) installed.

For compiling the project simply just run the **scripts/Linux/build.sh** file and it will build automatically. for compiling in debug mode, run **scripts/Linux/build_debug.bat**.

For running the program, you will need **OpenGL 3.3 and above**. all other nessacery dynamic link files are supplied in the repository.

For running the project, simply just execute **run.sh** for normal build, and **run_debug.sh** for debugging ( debug build ).

For Windows just run the windows equilivant aformationed files which are in scripts/Windows instead of scripts/Linux. although it has not been test on Windows for a while.

**run.sh** will supply run the executable with project root directory as it's working directory, if you wish to copy the executable somewhere else or ship it, you need to also copy data directory into the executable directory itself, or if you want to use the .sh file, you need to copy them with respect to the relative path they have with the run.sh file or modify the script file.

---
