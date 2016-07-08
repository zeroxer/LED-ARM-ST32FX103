#ifndef _USER__H_
#define _USER__H_
#include "stm32f10x.h"

#define BK0_HIGH GPIO_SetBits(GPIOC,GPIO_Pin_10)
#define BK0_LOW GPIO_ResetBits(GPIOC,GPIO_Pin_10)

#define BK1_HIGH GPIO_SetBits(GPIOC,GPIO_Pin_11)
#define BK1_LOW GPIO_ResetBits(GPIOC,GPIO_Pin_11)

#define BK2_HIGH GPIO_SetBits(GPIOC,GPIO_Pin_12)
#define BK2_LOW GPIO_ResetBits(GPIOC,GPIO_Pin_12)

extern u8 data[20];
extern u8 hello[20];
extern u8 start[20];
extern u8 emoje[20];

void Led_RollShow(u8 data[]);
void Led_StaticShow(u8 data[]);
void Led_StaticShow1(u8 data[]);
void Led_StaticShowHello(u8 data[]);
void Led_RollShowStart(u8 start[]);

#endif
