
# Sets the minimum version of CMake required to build the native library.
cmake_minimum_required(VERSION 3.10.2)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
#打印当前 cmakeLists 的路径
message("当前cmakel路径: ${CMAKE_SOURCE_DIR} \n cpu架构：${CMAKE_ANDROID_ARCH_ABI}")

# 查看gradle Console 调试信息 PROJECT_SOURCE_DIR => E:/Codes/android_code/TPlayer/ffmpeg
message(STATUS "========> distribution_DIR   is :${distribution_DIR}")
message(STATUS "========> ANDROID_ABI is : ${ANDROID_ABI}")
message(STATUS "========> the PROJECT_SOURCE_DIR is : ${PROJECT_SOURCE_DIR}")
message(STATUS "========> the PROJECT_BINARY_DIR is : ${PROJECT_BINARY_DIR}")
message(STATUS "========> the cmakeList.txt PATH is : ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "========> distribution_DIR is : ${distribution_DIR}")

set(jnilibs ${CMAKE_SOURCE_DIR}/../jniLibs)
project("JniStudy")

#找到包含所有的cpp文件
file(GLOB my_source *.cpp *.c)


#为了让 CMake 能够在编译时找到头文件，您需要使用 include_directories() 命令并包含相应头文件的路径：

##添加头文件搜索目录  发现一个android studio的bug 如果没有使用头文件 那么引入头文件的时候会一直报错. 我再这里被坑了很久.
include_directories(
        include
        util
)
#
#link_directories(
#        ${jnilibs}/${ANDROID_ABI}
#)

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
        log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.
link_directories(
        ${jnilibs}/${ANDROID_ABI})

target_link_libraries( # Specifies the target library.
        native-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib} )