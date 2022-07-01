cmake_minimum_required( VERSION 3.16 )

project( Game_Engine )

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 17 )

#for more readability and less repeating.
set( build_deps "${CMAKE_SOURCE_DIR}/dependencies" )
set( glfw_build_lib "${build_deps}/lib/glfw/32" )

file( GLOB_RECURSE engine_source
                  "${CMAKE_SOURCE_DIR}/dependencies/include/stb_image/stb_image.cpp"

                  "${CMAKE_SOURCE_DIR}/src/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/utils/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/graphics/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/maths/*.cpp"
    )

add_library( glad STATIC "${build_deps}/include/glad/glad.c" )

set_target_properties( glad PROPERTIES
                            COMPILE_FLAGS "-m32 -O3"
                     )

set_target_properties( glad PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/lib"
                     )

add_executable( engine ${engine_source} )

target_include_directories( engine PRIVATE
                            "${build_deps}/include"
                            "${CMAKE_SOURCE_DIR}/src"
                            "${CMAKE_SOURCE_DIR}/src/core"
                          )

target_precompile_headers( engine PRIVATE
                           "${CMAKE_SOURCE_DIR}/src/engine_pch.hpp" 
                         )                          

target_link_directories( engine PRIVATE
                          "${glfw_build_lib}"
                       )

target_link_libraries( engine PRIVATE
                          "opengl32"
                          "glfw3dll"

                          glad
                     )

set_target_properties( engine PROPERTIES
                             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin"
                     )

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set_target_properties( engine PROPERTIES
                            COMPILE_FLAGS "-m32 -g3 -Wall -Wextra"
                            LINK_FLAGS "-m32"
                         )

else()
    set_target_properties( engine PROPERTIES
                            COMPILE_FLAGS "-m32 -O2 -Wall -Wextra -s"
                            LINK_FLAGS "-m32"
                         )

endif()