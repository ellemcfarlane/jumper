/* f3d_nunchuk.c --- 
 * 
 * Filename: f3d_nunchuk.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Oct 31 09:40:37 2013
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
#include <f3d_delay.h>
#include <f3d_i2c.h>
#include <f3d_nunchuk.h>
#include <f3d_lcd_sd.h>
#include <stdio.h>
#include <math.h>

#define NUNCHUK_ADDRESS 0xA4

#define WORD_Y 145
#define PITCH_X 7
#define ROLL_X 73
#define HTOFF 18 // limit height of dynamic bars

// keeps track if 
void f3d_nunchuk_init(void) {
  uint8_t realb = 0x00;
  uint8_t buf = 0x55;
  uint8_t buf2 = 0x00;


  // Use for factory Wii Nunchuk controllers
  f3d_i2c1_write(NUNCHUK_ADDRESS,0x40,&realb);
  // Use for 3 party nunchuks like we have in the lab
  //f3d_i2c1_write(NUNCHUK_ADDRESS,0xf0,&buf); 
  //f3d_i2c1_write(NUNCHUK_ADDRESS,0xfb,&buf2);
}

void f3d_nunchuk_read(nunchuk_t *n) {
  uint8_t data[6] = {0,0,0,0,0,0};
  int i;
  unsigned short tmp;

  f3d_i2c1_read_nunchuk(0xA5, data, 6);
  n->jx = data[0];
  n->jy = data[1];

  tmp = data[2];
  tmp = tmp << 2;
  n->ax = tmp | ((data[5] & 0x0C) >> 2);

  tmp = data[3];
  tmp = tmp << 2;
  n->ay = tmp | ((data[5] & 0x30) >> 4);

  tmp = data[4];
  tmp = tmp << 2;
  n->az = tmp | ((data[5] & 0xC0) >> 6);

  switch (data[5] & 0x03) {
  case 2:
    n->z = 1;
    n->c = 0;
    break;
  case 1:
    n->z = 0;
    n->c = 1;
    break;
  case 0:
    n->z = 1;
    n->c = 1;
    break;
  case 3:
    n->z = 0;
    n->c = 0;
    break;
  }
}

// draws screen for nunchuk mode
// if drawFrame is set to 1, will draw frame, otherwise will not
void f3d_nunchuk_draw(nunchuk_t dat, int drawFrame) {
  float pitch, roll;

  pitch = atan2f(dat.ax, sqrtf(powf(dat.ay,2)+powf(dat.az,2)));
  roll = atan2f(dat.ay, sqrtf(powf(dat.ax,2)+powf(dat.az,2)));

  //draw labels
  if (drawFrame) {f3d_nunchuk_drawFrame();}

  // draw pitch/roll values and bars
  f3d_nunchuk_drawVals(pitch, roll, 20);
}

/* f3d_nunchuk.c ends here */

// draws pitch/roll values to screen with bars of corresponding heights, scaled per given scale
void f3d_nunchuk_drawVals(float pitch, float roll, int scale) {
  char str[30]; // use to format values to strings

  // draw pitch data
  sprintf(str, "%f", pitch);
  f3d_lcd_drawString(PITCH_X, WORD_Y, "         ", WORD_COL, BACKGROUND); // clear prev pitch val
  f3d_lcd_drawString(PITCH_X, WORD_Y, str, WORD_COL, BACKGROUND);
  delay(15);
  f3d_lcd_drawDynamicHBar(pitch*scale, PITCH_X, WORD_Y-15, 40, HTOFF, BLUE);

  // draw roll data
  sprintf(str, "%f", roll);
  f3d_lcd_drawString(ROLL_X, WORD_Y, "             ", WORD_COL, BACKGROUND); // clear prev roll val
  f3d_lcd_drawString(ROLL_X, WORD_Y, str, WORD_COL, BACKGROUND);
  delay(15);
  f3d_lcd_drawDynamicHBar(roll*scale, ROLL_X, WORD_Y-15, 40, HTOFF, BLUE);
}

// draws frame for nunchuk screen
void f3d_nunchuk_drawFrame() {
  f3d_lcd_drawString(7, 10, "mode: nunchuk", WORD_COL, BACKGROUND);
  f3d_lcd_drawString(PITCH_X, WORD_Y-10, "pitch:", WORD_COL, BACKGROUND);
  f3d_lcd_drawString(ROLL_X, WORD_Y-10, "roll:", WORD_COL, BACKGROUND);
}
