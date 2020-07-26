/* f3d_mag.c --- 
 * 
 * Filename: f3d_mag.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Oct 31 09:27:11 2013
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
#include <f3d_mag.h>
#include <f3d_lcd_sd.h>
#include <math.h>
#include <stdio.h>

#define WORD_Y 145
#define PITCH_X 7
#define ROLL_X 73
#define RANGE(val, min, max) (val >= min) && (val <= max) ? 1 : 0
void f3d_mag_init() {
  uint8_t value;
  
  /* f3d_mag.c */
  value = 0x14; //Temp sensor disable,30Hz Output Rate
  f3d_i2c1_write(0x3C, 0x00, &value); // Mag (0x3C), CRA (0x00)

  value = 0xE0; // +/- 8.1 Gauss Full Scale
  f3d_i2c1_write(0x3C, 0x01, &value); // Mag (0x3C), CRB (0x01)

  value = 0x00;// Continuous Conversion
  f3d_i2c1_write(0x3C, 0x02, &value); // Mag (0x3C), MR (0x23)
}

void f3d_mag_read(float *mag_data) {
  uint8_t buffer[6];
  int i;

  f3d_i2c1_read(0x3C, 0x03, buffer,2); // Read X Axis
  f3d_i2c1_read(0x3C, 0x07, buffer+2,2); // Read Y Axis
  f3d_i2c1_read(0x3C, 0x05, buffer+4,2); // Read Z Axis (notice that Z is out of order in the chip).

  for (i=0; i<2; i++) {
    mag_data[i]=(float)((int16_t)(((uint16_t)buffer[2*i] << 8) + buffer[2*i+1]))/230;
  }
  mag_data[2]=(float)((int16_t)(((uint16_t)buffer[4] << 8) + buffer[5]))/205;
}
// lights led per heading val and draws to screen
// only draws frame if set to 1
void f3d_mag_draw(int drawFrame) {
  float slaveVals[3];
  float heading, Xh, Yh;
  float pitch, roll;
  printf("mag mode\n"); //debug

  // read data from mag, convert to header angle
  f3d_mag_read(slaveVals);
  Xh = slaveVals[0]*cosf(pitch) + slaveVals[2]*sinf(pitch);
  Yh = slaveVals[0]*sinf(roll)*sinf(pitch) + slaveVals[1]*cosf(roll) - slaveVals[2]*sinf(roll)*cosf(pitch);
  heading = atan2f(Yh,Xh);

  // draw labels if drawFrame set
  if(drawFrame) {f3d_mag_drawFrame();}

  // draw values
  f3d_mag_drawVals(heading);

  f3d_led_all_off(); // clear previous light(s)
  // light led per heading value
  if (RANGE(heading, 2.25, 3.3)) f3d_led_on(1);
  if (RANGE(heading, 1.5, 2.24)) f3d_led_on(0);
  if (RANGE(heading, .75, 1.49)) f3d_led_on(7);
  if (RANGE(heading, 0, .74)) f3d_led_on(6);
  if (RANGE(heading, -3.3, -2.25)) f3d_led_on(2);
  if (RANGE(heading, -2.25, -1.5)) f3d_led_on(3);
  if (RANGE(heading, -1.49, -.75)) f3d_led_on(4);
  if (RANGE(heading, -.74, -.01)) f3d_led_on(5);
}

// draws value to screen
void f3d_mag_drawVals(float heading) {
  char str[30]; // use to format value to string
  sprintf(str, "%f", heading);
  f3d_lcd_drawString(7, WORD_Y, str, WORD_COL, BACKGROUND);
}

// draws frame for screen
void f3d_mag_drawFrame() {
  f3d_lcd_drawString(7, 10, "mode: mag", WORD_COL, BACKGROUND);
  f3d_lcd_drawString(7, WORD_Y-10, "heading:", WORD_COL, BACKGROUND);
}

/* f3d_mag.c ends here */
