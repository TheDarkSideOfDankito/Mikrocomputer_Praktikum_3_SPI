cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME 03_SPI)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SRCS 03_SPI.cpp SPI.h SPI.cpp)

set(${PROJECT_NAME}_BOARD uno)
set(${PROJECT_NAME}_PORT /dev/ttyACM0)

generate_arduino_firmware(${CMAKE_PROJECT_NAME})
