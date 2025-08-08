cmake_minimum_required(VERSION 3.4.1)

add_library(
    battery_info_ffi
    SHARED
    battery_info_android.cpp
)

find_library(
    log-lib
    log
)

target_link_libraries(
    battery_info_ffi
    ${log-lib}
    android
)
