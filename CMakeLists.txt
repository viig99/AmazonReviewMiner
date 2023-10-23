# Minimum CMake version and project name
cmake_minimum_required(VERSION 3.16)
project(Miner LANGUAGES CXX)

# C++ Standard Settings
set(CMAKE_CXX_STANDARD 20)

# Find required packages
set(REQUIRED_PACKAGES Spdlog ZLIB libcoro RapidJSON tsl-hopscotch-map Catch2)
foreach(PACKAGE ${REQUIRED_PACKAGES})
    find_package(${PACKAGE} REQUIRED)
endforeach()

# Define the executable
add_executable(Miner main.cpp)

# Gather all module files in a directory
file(GLOB SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp")
file(GLOB HEADER_ONLY_FILES "${CMAKE_CURRENT_SOURCE_DIR}/lib/*.hpp")

# Add sources to the executable
target_sources(Miner PRIVATE ${SOURCE_FILES} ${HEADER_ONLY_FILES})
target_include_directories(Miner PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Link the executable to the required libraries
target_link_libraries(Miner spdlog::spdlog ZLIB::ZLIB libcoro::libcoro rapidjson tsl::hopscotch_map)

# Add tests for easier development of functions.
add_executable(MinerTests tests/Tests.cpp)
target_sources(MinerTests PRIVATE ${SOURCE_FILES} ${HEADER_ONLY_FILES})
target_include_directories(MinerTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(MinerTests spdlog::spdlog ZLIB::ZLIB libcoro::libcoro rapidjson tsl::hopscotch_map Catch2::Catch2WithMain)