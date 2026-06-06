cmake_minimum_required(VERSION 4.2.2)
project(watchface)

file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS
        "src/c/*.c"
        "src/c/*.h")

add_executable(project_target ${PROJECT_SOURCES})
target_include_directories(project_target PRIVATE "~/.local/share/pebble-sdk/SDKs/4.9.169/sdk-core/pebble/gabbro/include")