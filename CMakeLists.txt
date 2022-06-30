cmake_minimum_required( VERSION 3.16 )

project( Game_Engine )

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 17 )

#for more readability and less repeating.
set( build_deps "${CMAKE_SOURCE_DIR}/dependencies" )
set( glfw_build_lib "${build_deps}/lib/glfw/32" )

file( GLOB_RECURSE source
                  "${CMAKE_SOURCE_DIR}/dependencies/include/stb_image/stb_image.cpp"

                  "${CMAKE_SOURCE_DIR}/src/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/utils/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/graphics/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/maths/*.cpp"
    )

#set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${build_deps}/lib/glad" )
add_library( glad STATIC "${build_deps}/include/glad/glad.c" )
set_target_properties( glad PROPERTIES
                            COMPILE_FLAGS "-m32 -O3"
                     )

set_target_properties( glad PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${build_deps}/lib/glad"
                     )

add_executable( flappy_bird ${source} )

target_include_directories( flappy_bird PRIVATE
                            "${build_deps}/include"
                            "${CMAKE_SOURCE_DIR}/src"
                            "${CMAKE_SOURCE_DIR}/src/core"
                          )

target_precompile_headers(
                           flappy_bird PRIVATE
                           "${CMAKE_SOURCE_DIR}/src/engine_pch.hpp" 
                         )                          

target_link_directories( flappy_bird PRIVATE
                          "${glfw_build_lib}"
                       )

target_link_libraries( flappy_bird PRIVATE
                          "opengl32"
                          "glfw3dll"
                       glad
                     )

set_target_properties( flappy_bird PROPERTIES
                             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
                     )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties( flappy_bird PROPERTIES
                            COMPILE_FLAGS "-m32 -g3 -Wall -Wextra"
                            LINK_FLAGS "-m32"
                         )
else()
    set_target_properties( flappy_bird PROPERTIES
                            COMPILE_FLAGS "-m32 -O2 -Wall -Wextra -s"
                            LINK_FLAGS "-m32"
                         )
endif()