/**
 * Author: Elle McFarlane
 * Partner: Kevin Cao
 */

/************************
 *f3d_led.c - contains intializations/functions for the leds
 ************************/

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <f3d_led.h>


//intializes the port and pins for the leds on the board
void f3d_led_init(void) {
 GPIO_InitTypeDef GPIO_InitStructure;
 GPIO_StructInit(&GPIO_InitStructure);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
 GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
 GPIO_Init(GPIOE, &GPIO_InitStructure);
}

/*Turns on the appropriate led as specified by the parameter.*/
void f3d_led_on(int led) {
  int curr_pin = GPIO_Pin_8 << led;
  GPIOE->BSRR = curr_pin;
}

/*Turns off the approiate led as specified by the parameter*/ 
void f3d_led_off(int led) {
  int curr_pin = GPIO_Pin_8 << led;
  GPIOE->BRR = curr_pin;
} 

/*Turns on all LEDs*/
void f3d_led_all_on(void) {
  // turn on LEDs within range
  int curr_pin;
  for (curr_pin = 0; curr_pin < 8; curr_pin++) {
    f3d_led_on(curr_pin);
  }
} 

/*Turns off all LEDs*/
void f3d_led_all_off(void) {
  int curr_pin;
  for (curr_pin = 0; curr_pin < 8; curr_pin++) {
    f3d_led_off(curr_pin);
  }
} 

/* led.c ends here */

