cmake_minimum_required(VERSION 3.10)
project(NginxManagerCli
    VERSION 1.5.0
    DESCRIPTION "CLI tool for Nginx config creator by Sesdear"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(nginx-manager-cli ${SOURCES})

message(STATUS "Building ${PROJECT_NAME} version ${PROJECT_VERSION}")
