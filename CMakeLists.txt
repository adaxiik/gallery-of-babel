cmake_minimum_required(VERSION 3.0.0)
project(gallery LANGUAGES C VERSION 1.0)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS} -g -pedantic -Wall -Wextra -Werror -fsanitize=address")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -O2 -march=native -mtune=generic")

file(GLOB SOURCES "src/*.c")
add_executable(gallery ${SOURCES})
target_link_libraries(gallery m png)


