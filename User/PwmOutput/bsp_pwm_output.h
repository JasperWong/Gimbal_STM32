#ifndef __PWM_OUTPUT_H
#define	__PWM_OUTPUT_H

#include "stm32f10x.h"

#define COUNTERCLOCKWISE 1
#define CLOCKWISE 2
#define STOP 3

void TIM3_PWM_Init(void);	
void Roll(u16 angle);
void Yaw(u16 turn);
void Reset(void);
void YawAngle(int16_t angle);
void YawToAngle(uint16_t angle);

#endif /* __PWM_OUTPUT_H */
