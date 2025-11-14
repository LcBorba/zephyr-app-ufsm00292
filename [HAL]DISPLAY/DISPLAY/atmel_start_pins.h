/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */
#ifndef ATMEL_START_PINS_H_INCLUDED
#define ATMEL_START_PINS_H_INCLUDED

#include <hal_gpio.h>

// SAMD21 has 8 pin functions

#define GPIO_PIN_FUNCTION_A 0
#define GPIO_PIN_FUNCTION_B 1
#define GPIO_PIN_FUNCTION_C 2
#define GPIO_PIN_FUNCTION_D 3
#define GPIO_PIN_FUNCTION_E 4
#define GPIO_PIN_FUNCTION_F 5
#define GPIO_PIN_FUNCTION_G 6
#define GPIO_PIN_FUNCTION_H 7

#define RES_PIN GPIO(GPIO_PORTB, 27)
#define PB16 GPIO(GPIO_PORTB, 16)
#define CS_PIN GPIO(GPIO_PORTB, 17)
#define PB22 GPIO(GPIO_PORTB, 22)
#define PB23 GPIO(GPIO_PORTB, 23)
#define DC_PIN GPIO(GPIO_PORTB, 30)

#define PA12 GPIO(GPIO_PORTA, 12)
#define PA13 GPIO(GPIO_PORTA, 13)
#define PA15 GPIO(GPIO_PORTA, 15)

#define DISPLAY_BUTTON_1 GPIO(GPIO_PORTA, 28)
#define DISPLAY_BUTTON_2 GPIO(GPIO_PORTA, 2)
#define DISPLAY_BUTTON_3 GPIO(GPIO_PORTA, 3)


#endif // ATMEL_START_PINS_H_INCLUDED
