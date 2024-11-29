# kk21 - goldex bot project

## Branch: develop

This repository contains goldex bot project for KK17.

with simple rotating hand, no dispencer control, no hran

## Build and flash

We use CMake to build project. To build and flash the bot, perform the following steps:

### Install dependencies

For win10, please install the following software from installers_win10:

- cmake
- stlink (for flashing)
- gcc-arm-none-eabi (for compiling)
- mingw32 (for mingw32-make)

### Configure and build

1. Run CMake to configure the project. You need to specify the following options:
    - `CMAKE_TOOLCHAIN_FILE`: `kk17/arm_none_eabi_gcc.cmake`
    - `CMAKE_BUILD_TYPE`: `Debug`
    - `CMAKE_GENERATOR`: `MinGW Makefiles` (for win)
2. Run `cmake --build . -- -j 4` to build the project.

### Flash the bot

1. Connect your bot to the computer using ST-Link.
2. Go `stlink - file - kk17.hex - program` to flash the bot.
