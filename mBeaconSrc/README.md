# mBeacon

## Project setup

- Do not have Spaces in the path of the project
- Based on platformio: `https://platformio.org/install/ide?install=vscode`, use VSCode and import the project
- Zephyr version can be found in `C:\.platformio\packages\framework-zephyr\VERSION`.
- Look for `https://docs.platformio.org/en/latest/frameworks/zephyr.html?utm_source=docs.zephyrproject.org#configuration`
  To get more details on how to configure the workspace.
- `make menuconfig`, if arrows do not work, use "j" and "k".

## Run the program

Logs can be extracted using J-Link RTT viewer
It won't start until it is connected. Configuration is nRF52832_xxAA

## Files

zephyr: contains all the necessary information for the OS:

- DTS overlay for adding the support of the sensors
- conf: For adding or removing some parts of the OS
- Contains the main top level CMake file

src: Source of the project, all the .c files (from platform IO)

include: Includes of the project, all the .h files (from platform IO)
