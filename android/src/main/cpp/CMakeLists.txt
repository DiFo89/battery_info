cmake_minimum_required(VERSION 3.4.1)

add_library(
    battery_info_ffi
    SHARED
    battery_info_android.cpp
)
include_directories($ENV{ANDROID_NDK}/toolchains/llvm/prebuilt/windows-x86_64/sysroot/usr/include)

find_library(
    log-lib
    log
)

target_link_libraries(
    battery_info_ffi
    ${log-lib}
    android
)
