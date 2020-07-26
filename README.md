# jumper

## game installation
* clone this repository
* cd into 'game' directory
* ensure board is plugged into computer via USB ST-LINK
* run 'make download'

## linux software set-up

### stlink

:$ sudo apt install cmake  
:$ sudo apt install build-essential  
:$ sudo apt install libusb-1.0  

:$ git clone git@github.com:texane/stlink.git  
:$ cd stlink  
:$ make  

:$ cd build/Release  
:$ sudo make install /usr/bin/  
:$ sudo apt install gcc-arm-none-eabi  

### download the stm32 libraries
https://www.st.com/en/embedded-software/stsw-stm32118.html

### file edit
change makefile_root.md to match your tool and library paths, e.g.:
TOOLROOT=/usr/bin/
LIBROOT=../libraries/STM32F3-Discovery_FW_V1.1.0

## hardware
* STM32F301 board with:
  * LCD display
  * Wii nunchuk
  * I2C
  * Accelerometer
  * User button

