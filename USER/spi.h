#ifndef _SPI__H_
#define _SPI__H_
#include "stm32f10x.h"


void SPI1_Init(void);
void SPI1_SetSpeed(u8 SpeedSet);
void SPI1_WriteByte(u8 TxData);

#endif

