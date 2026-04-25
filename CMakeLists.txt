cmake_minimum_required(VERSION 3.15)
project(raybird VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Find raylib
# Try pkg-config first (works on Linux/Mac)
find_package(PkgConfig QUIET)
if(PKG_CONFIG_FOUND)
    pkg_check_modules(RAYLIB raylib)
endif()

# If pkg-config didn't find raylib, try other methods
if(NOT RAYLIB_FOUND)
    # Try to find raylib using standard CMake find
    find_package(raylib QUIET)
    if(raylib_FOUND)
        set(RAYLIB_FOUND TRUE)
        set(RAYLIB_INCLUDE_DIRS ${raylib_INCLUDE_DIRS})
        set(RAYLIB_LIBRARIES ${raylib_LIBRARIES})
    endif()
endif()

# If still not found, try to find it in common locations
if(NOT RAYLIB_FOUND)
    # Check for raylib in standard system paths
    find_path(RAYLIB_INCLUDE_DIR raylib.h
        PATHS
            /usr/local/include
            /usr/include
            /opt/homebrew/include
            $ENV{RAYLIB_PATH}/include
    )
    
    find_library(RAYLIB_LIBRARY
        NAMES raylib libraylib
        PATHS
            /usr/local/lib
            /usr/lib
            /opt/homebrew/lib
            $ENV{RAYLIB_PATH}/lib
    )
    
    if(RAYLIB_INCLUDE_DIR AND RAYLIB_LIBRARY)
        set(RAYLIB_FOUND TRUE)
        set(RAYLIB_INCLUDE_DIRS ${RAYLIB_INCLUDE_DIR})
        set(RAYLIB_LIBRARIES ${RAYLIB_LIBRARY})
    endif()
endif()

# Fallback: assume raylib is available via compiler/linker flags
if(NOT RAYLIB_FOUND)
    message(WARNING "raylib not found via pkg-config or CMake. Assuming it's available via system paths.")
    set(RAYLIB_INCLUDE_DIRS "")
    set(RAYLIB_LIBRARIES "raylib")
endif()

# Collect source files
file(GLOB SOURCES "src/*.c")

# Create executable
add_executable(raybird ${SOURCES})

# Link raylib and math library
target_link_libraries(raybird PRIVATE ${RAYLIB_LIBRARIES} m)
target_include_directories(raybird PRIVATE ${RAYLIB_INCLUDE_DIRS})

# macOS-specific frameworks
if(APPLE)
    target_link_libraries(raybird PRIVATE "-framework Cocoa" "-framework IOKit" "-framework OpenGL" "-framework CoreVideo" "-framework CoreAudio")
endif()

# Compiler warnings
target_compile_options(raybird PRIVATE
    $<$<COMPILE_LANGUAGE:C>:-Wall -Wextra -Wpedantic -Werror>
)

# Debug configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(raybird PRIVATE DEBUG)
endif()

# Installation rules
install(TARGETS raybird DESTINATION bin)
