
#ifndef _INIT__H_
#define _INIT__H_

#include "stm32f10x.h"
#include "I2C_MPU6050.h"
#include "usart1.h"
#include "delay.h"
#include "user.h"
#include "timer.h"
#include "pwm.h"
#include "spi.h"
#include "sensor.h"
#include "showwave.h"


#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)//读取按键1

void MYRCC_DeInit(void);
void Stm32_Clock_Init(u8 PLL);
void GPIO_Configuration(void);



#endif
