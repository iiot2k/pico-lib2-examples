cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include(pico_sdk_import.cmake)

# We also need LIB2
include(pico_lib2_import.cmake)

project(lib2_examples C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the Pico SDK
pico_sdk_init()

add_subdirectory(ads1115)
add_subdirectory(mcp4728)
add_subdirectory(ds3231)
add_subdirectory(i2cdetect)
