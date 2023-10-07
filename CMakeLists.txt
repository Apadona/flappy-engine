cmake_minimum_required( VERSION 3.16 )

project( payan_name )

set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_STANDARD 17 )

# if ON, target will be build for 64-bit systems, OFF and target will be build for 32-bit systems.
option( architecture_64 "select build architecture (32 or 64) bit." ON )

###########          for more readability and less repeating.           ###########
# project directories.
set( dependencies_directory "${CMAKE_SOURCE_DIR}/dependencies" )
set( engine_source_directory "${CMAKE_SOURCE_DIR}/src" )
set( sanbox_directory "${CMAKE_SOURCE_DIR}/sandbox" )
set( include_api_directory "${CMAKE_SOURCE_DIR}/include")
set( build_directory "${CMAKE_SOURCE_DIR}/build" )

# compile flags used for compiling the engine and it's sanbox (not the dependencies).
set( release_compile_flags "-O2 -Wall -Wextra -s" )
set( debug_compile_flags "-g3 -Wall -Wextra" )

if( WIN32 ) 
    set( os_title "windows" )
    set( opengl_library "opengl32" )

elseif( UNIX )
    if( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
        set( os_title "linux" )
        set( opengl_library "GL" )

    else()
        message( FATAL_ERROR "UNIX platform other than Linux detected!\n" )
    endif() 

else()
    message( FATAL_ERROR "only windows and linux are currently supported!\n" )
endif()

if( architecture_64 )
    set( target_architecture "64" )
else()
    set( target_architecture "32" )
endif()

# directories for the executables/libraries that we are building.
set( executable_directory "${build_directory}/bin/${os_title}/${target_architecture}" )
set( library_directory "${build_directory}/lib/${os_title}/${target_architecture}" )

###########          compiling glfw as a static library          ###########
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
set( GLFW_INSTALL OFF CACHE BOOL "" FORCE )

add_subdirectory("${dependencies_directory}/glfw")

set_target_properties( glfw PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${library_directory}"
                     )

###########          compiling imgui as a static library          ###########

set( IMGUI_SOURCE_PATH "${dependencies_directory}/imgui" )
file( GLOB_RECURSE imgui_source_files
    "${IMGUI_SOURCE_PATH}/imgui.cpp"
    "${IMGUI_SOURCE_PATH}/imgui_draw.cpp"
    "${IMGUI_SOURCE_PATH}/imgui_tables.cpp"
    "${IMGUI_SOURCE_PATH}/imgui_widgets.cpp"
    "${IMGUI_SOURCE_PATH}/backends/imgui_impl_glfw.cpp"
    "${IMGUI_SOURCE_PATH}/backends/imgui_impl_opengl3.cpp" )

add_library( imgui STATIC ${imgui_source_files} )

target_include_directories( imgui PRIVATE
                            "${dependencies_directory}/imgui"
                          )

set_target_properties( imgui PROPERTIES
                          COMPILE_FLAGS "-m${target_architecture} -O3"
                     )

set_target_properties( imgui PROPERTIES
                          ARCHIVE_OUTPUT_DIRECTORY "${library_directory}"
                   )

###########          compiling freetype as a static library          ###########
add_subdirectory("${dependencies_directory}/freetype")

set_target_properties( freetype PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${library_directory}"
                     )

###########          compiling glad as a a static library          ###########
add_library( glad STATIC "${dependencies_directory}/glad/glad/glad.c" )

target_include_directories( glad PRIVATE
                            "${dependencies_directory}/glad"
                          )

set_target_properties( glad PROPERTIES
                            COMPILE_FLAGS "-m${target_architecture} -O3"
                     )

set_target_properties( glad PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${library_directory}"
                     )

###########          compiling stb_image as a static library          ###########
add_library( stb_image STATIC "${dependencies_directory}/stb_image/stb_image.cpp" )

set_target_properties( stb_image PROPERTIES
                            COMPILE_FLAGS "-m${target_architecture} -O3"
                     )

set_target_properties( stb_image PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${library_directory}"
                     )

###########          compiling engine as a static library          ###########
file( GLOB_RECURSE engine_source_files
                  "${engine_source_directory}/*.cpp"
                  #"${engine_source_directory}/core/*.cpp"
                  #"${engine_source_directory}/graphics/*.cpp"
                  #"${engine_source_directory}/maths/*.cpp"
                  #"${engine_source_directory}/utils/*.cpp"
    )

add_library( engine STATIC ${engine_source_files} )

target_include_directories( engine PUBLIC
                            "${dependencies_directory}"
                            "${dependencies_directory}/glad"
                            "${dependencies_directory}/glfw/include"
                            "${dependencies_directory}/freetype/include"
                            "${dependencies_directory}/imgui"
                            "${dependencies_directory}/imgui/backend"

                            "${engine_source_directory}"
                            "${engine_source_directory}/core"
                          )

target_precompile_headers( engine PRIVATE
                           "${engine_source_directory}/engine_pch.hpp" 
                         )                          

target_link_libraries( engine PRIVATE
                          "${opengl_library}"

                          glad
                          glfw
                          stb_image
                          freetype
                          imgui
                     )

set_target_properties( engine PROPERTIES
                            ARCHIVE_OUTPUT_DIRECTORY "${library_directory}"
                     )

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set_target_properties( engine PROPERTIES
                            COMPILE_FLAGS "-m${target_architecture} ${debug_compile_flags}"
                         )

else()
    set_target_properties( engine PROPERTIES
                            COMPILE_FLAGS "-m${target_architecture} ${release_compile_flags}"
                         )

endif()

###########          compiling sandbox          ###########
add_executable( sandbox "sandbox/sandbox.cpp" )

target_include_directories( sandbox PRIVATE
                            "${include_api_directory}"
                          )

target_link_libraries( sandbox PRIVATE
                        engine
                     )

set_target_properties( sandbox PROPERTIES
                            RUNTIME_OUTPUT_DIRECTORY "${executable_directory}"
                     )                     

if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set_target_properties( sandbox PROPERTIES
                            COMPILE_FLAGS "-m${target_architecture} ${debug_compile_flags}"
                        )
else()
    set_target_properties( sandbox PROPERTIES
                            COMPILE_FLAGS "-m${target_architecture} ${release_compile_flags}"
                         )

endif()
