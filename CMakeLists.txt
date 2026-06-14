cmake_minimum_required(VERSION 3.14)
project(nginxcc
    VERSION 2.0.1
    DESCRIPTION "CLI tool for Nginx config creator by Seadear"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(nginxcc ${SOURCES})

target_link_libraries(nginxcc argparse)

message(STATUS "Building ${PROJECT_NAME} version ${PROJECT_VERSION}")
