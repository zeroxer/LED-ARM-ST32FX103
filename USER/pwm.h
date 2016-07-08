#ifndef _PWM__H_
#define _PWM__H_
#include "stm32f10x.h"


void PWM_Init(u16 arr,u16 psc);


void pwm_set_high(TIM_TypeDef* TIMx, uint16_t TIM_Channel);
void pwm_set_low(TIM_TypeDef* TIMx, uint16_t TIM_Channel);
void pwm_set_on(TIM_TypeDef* TIMx, uint16_t TIM_Channel);//ปฅฒน
void pwm_set_off(TIM_TypeDef* TIMx, uint16_t TIM_Channel);

#endif
