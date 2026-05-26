cmake_minimum_required(VERSION 3.16)
project(SkyBridge VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_SOURCES
        main.cpp
        include/ITelemetryDisplay.h
        include/TerminalDisplay.h
        source/TerminalDisplay.cpp
        # Drop the library files in your project root
)

add_executable(SkyBridge ${PROJECT_SOURCES})

target_include_directories(SkyBridge PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)