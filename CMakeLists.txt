cmake_minimum_required(VERSION 3.16)
project(SkyBridge VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("/opt/homebrew/Cellar/qpid-proton/0.40.0/include"
                    "/opt/apr-1.7.5/include"
                    "/opt/libraries"
                    "/opt/homebrew/Cellar/simdjson/4.6.4/include"
                    "/opt/libraries/stduuid/include"
                    "/opt/libraries/stduuid/")

set(EXTERNAL_LIBRARIES
        "/opt/homebrew/Cellar/e2fsprogs/1.47.2/lib/libuuid.a"
        "/opt/homebrew/Cellar/openssl@3/3.6.2/lib/libssl.a"
        "/opt/homebrew/lib/libcrypto.a"
        "/usr/local/apr/lib/libapr-1.a"
        "/usr/local/lib/libqpid-proton-cpp-static.a"
        "/usr/local/lib/libqpid-proton-static.a"
        "/usr/local/lib/libqpid-proton-core-static.a"
        "/usr/local/lib/libqpid-proton-proactor-static.a"
        "/opt/homebrew/Cellar/libuv/1.52.1/lib/libuv.a"
        "/opt/homebrew/Cellar/cyrus-sasl/2.1.28_2/lib/libsasl2.dylib"
        "/opt/homebrew/Cellar/simdjson/4.6.4/lib/libsimdjson_static.a")

set(PROJECT_SOURCES
        main.cpp
        include/interfaces/ITelemetryDisplay.h
        include/TerminalDisplay.h
        source/TerminalDisplay.cpp
        include/ThreadSafeQueue.h
        source/ThreadSafeQueue.cpp
        include/AmqClient.h
        source/AmqClient.cpp
        include/VehicleTelemetryPayload.h
        source/VehicleTelemetryPayload.cpp
        include/MessagePacket.h
        source/MessagePacket.cpp
        include/interfaces/IMessagePayload.h
        # Drop the library files in your project root
)

add_executable(SkyBridge ${PROJECT_SOURCES})
target_link_libraries(SkyBridge ${EXTERNAL_LIBRARIES})

target_include_directories(SkyBridge PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
)

