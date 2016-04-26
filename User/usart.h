#ifndef USART_H
#define USART_H

#include "stm32f10x.h"
#include <stdio.h>

void USART_Config(void);
void Usart_NVIC_Init(void);
void OnRecieve(int32_t data);
#endif
