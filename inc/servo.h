#ifndef SERVO_H_
#define SERVO_H_

/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/* Configuration function ----------------------------------------------------*/
void Servo_Configuration(void);

void Set_Servo_PWM(uint8_t Servo_Number, uint16_t PWM);

#endif
