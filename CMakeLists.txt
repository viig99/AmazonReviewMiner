# Minimum CMake version and project name
cmake_minimum_required(VERSION 3.26 FATAL_ERROR)
project(ArrowExperiments LANGUAGES CXX)

# C++ Standard Settings
set(CMAKE_CXX_STANDARD 20)
# Doesn't work without this, needed for including import statement.
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Custom Experimental API Key, used for modules!
if(CMAKE_VERSION VERSION_LESS "3.27.0")
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "2182bf5c-ef0d-489a-91da-49dbc3090d2a")
else()
    set(CMAKE_EXPERIMENTAL_CXX_MODULE_CMAKE_API "aa1f7df0-828a-4fcd-9afc-2dc80491aca7")
endif()

# Find required packages
set(REQUIRED_PACKAGES Arrow Spdlog)
foreach(PACKAGE ${REQUIRED_PACKAGES})
    find_package(${PACKAGE} REQUIRED)
endforeach()

# Define the executable
add_executable(ArrowExperiments main.cpp)

# Gather all module files in a directory
file(GLOB MODULE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/modules/*.cppm")

# Add sources to the executable
target_sources(ArrowExperiments
        PRIVATE FILE_SET CXX_MODULES FILES ${MODULE_FILES})

# Link the executable to the required libraries
target_link_libraries(ArrowExperiments arrow::arrow spdlog::spdlog)
