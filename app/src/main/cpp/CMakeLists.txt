cmake_minimum_required(VERSION 3.4.1)

add_library(
        native-lib
        SHARED
        native-lib.cpp)

find_library(
        log-lib
        log)

# 引入头文件
include_directories(${CMAKE_SOURCE_DIR}/ffmpeg/include/)
set(lib_path ${CMAKE_SOURCE_DIR}/ffmpeg/lib/${ANDROID_ABI})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${lib_path}")

target_link_libraries(
        native-lib
        avfilter avformat avcodec avutil swresample swscale
        z
        android
        OpenSLES
        ${log-lib})

add_subdirectory ("BasicPlayer")
add_subdirectory ("BasicAV")
add_subdirectory ("BasicThread")