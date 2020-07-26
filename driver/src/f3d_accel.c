/* f3d_accel.c --- 
 * 
 * Filename: f3d_accel.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Oct 31 09:14:43 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

#include <f3d_i2c.h>
#include <f3d_lcd_sd.h>
#include <f3d_accel.h>
#include <f3d_delay.h>
#include <stdio.h>
#include <math.h>

#define WORD_Y 145
#define PITCH_X 7
#define ROLL_X 73
void f3d_accel_init() {
  uint8_t value;

  /* f3d_accel.c*/
  value = 0x40|0x07; // Normal Power Mode, All Axis Enable (X,Y,Z)
  f3d_i2c1_write(0x32, 0x20, &value); // Accel (0x32), Ctrl Reg1 (0x20)

  value = 0x08; // Continuous Update, Little Endian, 2G Sensitivity, High Resolution Mode
  f3d_i2c1_write(0x32, 0x23, &value); // Accel (0x32, Ctrl Reg4 (0x23)

  value = 0x10 | 0x80; // HPF Cutoff 16, High Pass Filter Normal Mode, AO1/AO1 Disable
  f3d_i2c1_write(0x32, 0x21, &value); // Accel (0x32, Ctrl Reg2 (0x21)
}

void f3d_accel_read(float *accel_data) {
  int16_t raw_data[3];
  uint8_t buffer[6];
  int i;

  /*f3d_accel.c*/
  f3d_i2c1_read(0x32, 0x28, buffer, 6);
  for (i=0; i<3; i++) {
    raw_data[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i])/(uint8_t)16;
    accel_data[i]=(float)raw_data[i]/1000.0;
  }
}

void f3d_accel_draw(int drawFrame) {
  float slaveVals[3];
  float pitch;
  float roll;

  printf("accel mode\n"); // debug

  // draw frame if drawFrame set
  if (drawFrame) {f3d_accel_drawFrame();}

  // draw vals/bars
  f3d_accel_read(slaveVals);
  pitch = atan2f(slaveVals[0], sqrt(powf(slaveVals[1],2) + powf(slaveVals[2],2)));
  roll = atan2f(slaveVals[1], sqrt(powf(slaveVals[0],2) + powf(slaveVals[2],2)));
  f3d_accel_drawVals(pitch, roll, 60);
}
/* f3d_accel.c ends here */

void f3d_accel_drawVals(float pitch, float roll, int scale) {
  char str[30];
  // draw pitch data
  sprintf(str, "%f", pitch);
  f3d_lcd_drawString(PITCH_X, WORD_Y, str, WORD_COL, BACKGROUND);
  delay(15);
  f3d_lcd_drawDynamicHBar(pitch*scale, PITCH_X, WORD_Y-15, 40, 50, BLUE);

  // draw roll data
  delay(15);
  sprintf(str, "%f", roll);
  f3d_lcd_drawString(ROLL_X, WORD_Y, str, WORD_COL, BACKGROUND);
  f3d_lcd_drawDynamicHBar(roll*scale, ROLL_X, WORD_Y-15, 40, 50, BLUE);
}

void f3d_accel_drawFrame() {
  f3d_lcd_drawString(7, 10, "mode: accel", WORD_COL, BACKGROUND);
  f3d_lcd_drawString(PITCH_X, WORD_Y-10, "pitch:", WORD_COL, BACKGROUND);
  f3d_lcd_drawString(ROLL_X, WORD_Y-10, "roll:", WORD_COL, BACKGROUND);
}
