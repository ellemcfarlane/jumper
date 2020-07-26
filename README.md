# jumper

## video demo
Click [here](https://drive.google.com/file/d/1Gx4is2f0_Znnba_4_Oi3fZEkFp1OcODH/view?usp=sharing) to watch a video of the game being played.
Note: video has no audio.

## game instructions
* c or z button on nunchuk to fire bullets
* tilt board to move player

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

