
# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.4.1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#打印当前 cmakeLists 的路径
#message("当前cmakel路径: ${CMAKE_SOURCE_DIR} \n cpu架构：${CMAKE_ANDROID_ARCH_ABI}")
#
## 查看gradle Console 调试信息 PROJECT_SOURCE_DIR => E:/Codes/android_code/TPlayer/ffmpeg
#message(STATUS "========> distribution_DIR   is :${distribution_DIR}")
#message(STATUS "========> ANDROID_ABI is : ${ANDROID_ABI}")
#message(STATUS "========> the PROJECT_SOURCE_DIR is : ${PROJECT_SOURCE_DIR}")
#message(STATUS "========> the PROJECT_BINARY_DIR is : ${PROJECT_BINARY_DIR}")
#message(STATUS "========> the cmakeList.txt PATH is : ${CMAKE_CURRENT_SOURCE_DIR}")
#message(STATUS "========> distribution_DIR is : ${distribution_DIR}")

set(jnilibs ${CMAKE_SOURCE_DIR}/../jniLibs)

set(libname native-lib)
#project("JniStudy")


include_directories(
        include
        ${CMAKE_SOURCE_DIR}/util
)

#找到包含所有的cpp文件
#file(GLOB my_source *.cpp *.c)
file(GLOB my_source
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/util/*.cpp
        ${CMAKE_SOURCE_DIR}/player/*.cpp
        ${CMAKE_SOURCE_DIR}/player/decoder/*.cpp
        ${CMAKE_SOURCE_DIR}/player/render/video/*.cpp
        ${CMAKE_SOURCE_DIR}/player/render/audio/*.cpp)


# 这里的link_directories 必须放在这里要不然编译就找不到库了
link_directories(
        ${jnilibs}/${ANDROID_ABI})

#为了让 CMake 能够在编译时找到头文件，您需要使用 include_directories() 命令并包含相应头文件的路径：

##添加头文件搜索目录  发现一个android studio的bug 如果没有使用头文件 那么引入头文件的时候会一直报错. 我再这里被坑了很久.



add_library( # Sets the name of the library.
        native-lib
        SHARED
        ${my_source}
        )

#找到系统的已经存在的动态库

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)



set(third-party-libs
        avformat
        avcodec
        avfilter
        swresample
        swscale
        avutil
        )

set(native-libs
        android
        EGL
        OpenSLES
        log
        m
        z
        )
#set(third-party-libs
#        avformat
#        avcodec
#        avfilter
#        swresample
#        swscale
#        avutil
#        )
target_link_libraries( # Specifies the target library.
        ${libname}
        ${third-party-libs}
        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${native-libs})