#ifndef __TIMER_H
#define __TIMER_H
#include "stm32f10x.h"

void TIM3_IRQHandler(void);   //TIM3ÖÐ¶Ï  
void TIM3_Init(u16 arr,u16 psc); 
 
#endif
