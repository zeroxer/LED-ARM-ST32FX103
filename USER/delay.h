#include "stm32f10x.h"
#ifndef _DELAY__H_
#define _DELAY__H_

void delay_init(u8 SYSCLK);
void delayus(u32 nus);
void delayms(u16 nms);
void delay_us(u32 n);
void delay_ms(u32 n);

#endif
