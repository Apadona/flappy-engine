cmake_minimum_required( VERSION 3.15 )

project( flappy )

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_)

file( GLOB_RECURSE source
      "${CMAKE_SOURCE_DIR}/src/*.cpp"
      #"${CMAKE_SOURCE_DIR}/src/maths/*.cpp"
      #"${CMAKE_SOURCE_DIR}/src/utils/*.cpp"
      "${CMAKE_SOURCE_DIR}/dependencies/include/glad/glad.c" )

add_executable( flappy_bird ${source} )

#for more readability and less repeating.
set( build_deps "${CMAKE_SOURCE_DIR}/dependencies" )
set( glfw_build_lib "${build_deps}/lib/glfw/32" )

target_include_directories( flappy_bird PRIVATE
                            "${build_deps}/include"
                            "${CMAKE_SOURCE_DIR}/src" )

target_link_directories( flappy_bird PRIVATE
                         "${glfw_build_lib}" )

target_link_libraries( flappy_bird PRIVATE
                       "opengl32"
                       "glfw3dll" )

set_target_properties( flappy_bird PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                       "${CMAKE_SOURCE_DIR}/bin" )

set_target_properties( flappy_bird PROPERTIES COMPILE_FLAGS "-m32"
                        LINK_FLAGS "-m32" )