cmake_minimum_required(VERSION 3.13.1)

set(OPENOCD_NRF5_SUBFAMILY "nrf52")

set (BOARD_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
include($ENV{ZEPHYR_BASE}/cmake/app/boilerplate.cmake NO_POLICY_SCOPE)

message("Board " ${BOARD} " build type " ${CMAKE_BINARY_DIR})
set(BOARD mBeacon)

project(nrf52-mbeacon)

FILE(GLOB app_sources ../src/*.c*)
target_sources(app PRIVATE ${app_sources})

