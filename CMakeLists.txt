cmake_minimum_required( VERSION 3.16 )

project( payan_name )

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 17 )

#for more readability and less repeating.
set( build_deps "${CMAKE_SOURCE_DIR}/dependencies" )
set( library_directory "${CMAKE_SOURCE_DIR}/build/lib" )

###########          compiling glfw as a library          ###########
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
set( GLFW_INSTALL OFF CACHE BOOL "" FORCE )

add_subdirectory("${build_deps}/glfw")

###########          compiling glad as a library          ###########
add_library( glad STATIC "${build_deps}/glad/glad/glad.c" )

target_include_directories( glad PRIVATE
                            "${build_deps}/glad"
                          )

set_target_properties( glad PROPERTIES
                            COMPILE_FLAGS "-O3"
                     )

set_target_properties( glad PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${library_directory}"
                     )

###########          compiling stb_image as a library          ###########
add_library( stb_image STATIC "${build_deps}/stb_image/stb_image.cpp" )

set_target_properties( stb_image PROPERTIES
                            COMPILE_FLAGS "-O3"
                     )

set_target_properties( stb_image PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${library_directory}"
                     )

###########          compiling engine          ###########
file( GLOB_RECURSE engine_source
                  "${CMAKE_SOURCE_DIR}/src/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/utils/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/graphics/*.cpp"
                  #"${CMAKE_SOURCE_DIR}/src/maths/*.cpp"
    )                     

add_executable( engine ${engine_source} )

target_include_directories( engine PRIVATE
                            "${build_deps}"
                            "${build_deps}/glad"
                            "${build_deps}/glfw/include"
                            "${CMAKE_SOURCE_DIR}/src/core"
                            "${CMAKE_SOURCE_DIR}/src"
                          )

target_precompile_headers( engine PRIVATE
                           "${CMAKE_SOURCE_DIR}/src/engine_pch.hpp" 
                         )                          

#target_link_directories( engine PRIVATE
#                          "${build_deps}/lib/glfw/32"
#                       )

target_link_libraries( engine PRIVATE
                          "GL"

                          glfw
                          glad
                          stb_image
                     )

set_target_properties( engine PROPERTIES
                             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build/bin"
                     )

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set_target_properties( engine PROPERTIES
                            COMPILE_FLAGS "-g3 -Wall -Wextra"
                            
                         )

else()
    set_target_properties( engine PROPERTIES
                            COMPILE_FLAGS "-O2 -Wall -Wextra -s"
                            
                         )

endif()