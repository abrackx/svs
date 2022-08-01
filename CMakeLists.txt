cmake_minimum_required(VERSION 3.23)
project(svs)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBAV REQUIRED IMPORTED_TARGET
        libavdevice
        libavfilter
        libavformat
        libavcodec
        libswresample
        libswscale
        libavutil
        )

pkg_check_modules(LIB_VLC REQUIRED IMPORTED_TARGET
        libvlc
        )

set(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})

add_executable(svs main.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::LIBAV)
target_link_libraries(${PROJECT_NAME} PUBLIC PkgConfig::LIB_VLC)
