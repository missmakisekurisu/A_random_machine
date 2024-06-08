#ifndef _ENCODER_H
#define _ENCODER_H
#include "gpio.h"


//编码器中间按钮用中断
#define KEY1_INT_GPIO_PORT         GPIOB

#define KEY1_INT_GPIO_PIN          GPIO_PIN_1


//编码器AB相用轮询
#define ENCODER_PORT                 GPIOB     
#define ENCODER_PIN_A                GPIO_PIN_10 
#define ENCODER_PIN_B                GPIO_PIN_11 

#define ENCODER_READ_A  HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_PIN_A)
#define ENCODER_READ_B  HAL_GPIO_ReadPin(ENCODER_PORT, ENCODER_PIN_B)

#define ENCODER_RESOLUTION  (20)

typedef struct{
		uint8_t x;
		uint8_t y;
		uint8_t buttons;

		int8_t wheel;
}T_MOUSEE_HID; 

extern int currentRad;
extern T_MOUSEE_HID mouseHID;

uint8_t encoder_read_position(void);
void key1_interupt_routine(void);
void encoder_Task(void);

#endif
