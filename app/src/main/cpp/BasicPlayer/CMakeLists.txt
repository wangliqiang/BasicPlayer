cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR})

# 将源代码添加到此项目的可执行文件。
add_library(
        BasicPlayer
        SHARED
        "BasicPlayer.cpp"
        "BasicPlayer.h"
        "BasicPlayerReaderThread.cpp"
        "BasicPlayerDecoderThread.cpp"
        "BasicPlayerController.cpp")

target_link_libraries(BasicPlayer BasicThread)
target_link_libraries(BasicPlayer BasicAV)