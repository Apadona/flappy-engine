## flappy-bird

flappy bird clone using C++/glfw/OpenGL.
for compiling the project, you need to have gcc (that supports C++17) and cmake(atleast 3.10) installed. (On windows their instalation path must be set in the PATH enviroment variable).
for compiling the project simply just run the build.bat file and it will build automatically.for compiling in debug mode, run build_debug.bat.
for running the program, you will need OpenGL 3+. all other nessacery dynamic link files are supplied in the repository.
for running the project, simply just execute run.bat for normal build, and run_debug.bat for debugging ( debug build ).
run.bat will supply the nessacery dynamic link files for the executable, if you wish to copy the executable somewhere else or ship it, you need to also copy the dynamic link files into the executable directory itself, or if you want to use the .bat file, you need to copy them with respect to the relative path they have with the run.bat file.
