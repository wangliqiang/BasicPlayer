cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR})

add_library(
        BasicAV
        SHARED
        "BasicAVReader.cpp"
        "BasicAVPacket.cpp"
        "BasicAVDecoder.cpp"
        "BasicAVStream.cpp"
        "BasicAVFrame.cpp"
        "BasicAVTime.cpp")


