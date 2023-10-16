# Minimum CMake version and project name
cmake_minimum_required(VERSION 3.16)
project(ArrowExperiments LANGUAGES CXX)

# C++ Standard Settings
set(CMAKE_CXX_STANDARD 20)

# Find required packages
set(REQUIRED_PACKAGES Arrow Spdlog ZLIB libcoro RapidJSON)
foreach(PACKAGE ${REQUIRED_PACKAGES})
    find_package(${PACKAGE} REQUIRED)
endforeach()

# Define the executable
add_executable(ArrowExperiments main.cpp)

# Gather all module files in a directory
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp")
file(GLOB HEADER_ONLY_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.hpp")

# Add sources to the executable
target_sources(ArrowExperiments PRIVATE ${SOURCE_FILES} ${HEADER_ONLY_FILES})
target_include_directories(ArrowExperiments PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link the executable to the required libraries
target_link_libraries(ArrowExperiments arrow::arrow spdlog::spdlog ZLIB::ZLIB libcoro::libcoro rapidjson)
