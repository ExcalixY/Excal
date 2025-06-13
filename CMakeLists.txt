cmake_minimum_required(VERSION 3.14)
project(MyVM LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# Output binary to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Include headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/src/*.c
)

# Main executable
add_executable(Excal ${SOURCES})

target_link_libraries(Excal PRIVATE fstream)
target_link_directories(Excal PRIVATE ${CMAKE_SOURCE_DIR}/lib/filestream)

# Enable warnings
target_compile_options(Excal PRIVATE -Wall -Wextra -Wpedantic)

# Optional: link libraries from lib/ later
# target_link_libraries(Excal PRIVATE some_library)
