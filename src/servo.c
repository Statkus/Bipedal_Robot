/* Includes ------------------------------------------------------------------*/
#include "servo.h"

/* Local functions -----------------------------------------------------------*/
void Servo_GPIOs_Configuration (void);
void Timer1_Configuration(void);
void Timer2_Configuration(void);
void Timer3_Configuration(void);
void Timer4_Configuration(void);

void Servo_Configuration(void)
{
	Servo_GPIOs_Configuration();

	Timer1_Configuration();
	//Timer2_Configuration();
	Timer3_Configuration();
	Timer4_Configuration();
}

void Set_Servo_PWM(uint8_t Servo_Number, uint16_t PWM)
{
	if (Servo_Number >= 1 && Servo_Number <= 16) {
		if (PWM > 2000) {
			PWM = 2000;
		} else if (PWM < 1000) {
			PWM = 1000;
		}

		switch(Servo_Number) {
			case 1: TIM3->CCR3 = PWM; break;
			case 2: TIM3->CCR4 = PWM; break;
			case 3: TIM4->CCR2 = PWM; break;
			case 4: TIM4->CCR1 = PWM; break;
			case 5: TIM4->CCR3 = PWM; break;
			case 6: TIM4->CCR4 = PWM; break;
			case 7: TIM3->CCR2 = PWM; break;
			case 8: TIM3->CCR1 = PWM; break;
			case 9: TIM1->CCR2 = PWM; break;
			case 10: TIM1->CCR4 = PWM; break;
			case 11: TIM1->CCR3 = PWM; break;
			case 12: TIM1->CCR1 = PWM; break;
			//case 13: TIM2->CCR3 = PWM; break;
			//case 14: TIM2->CCR4 = PWM; break;
			//case 15: TIM2->CCR1 = PWM; break;
			//case 16: TIM2->CCR2 = PWM; break;
		}
	}
}

void Servo_GPIOs_Configuration (void)
{
	// Enable peripheral clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA |
	                      RCC_AHBPeriph_GPIOB |
						  RCC_AHBPeriph_GPIOD, ENABLE);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);

	// Timer1 servos:             S12          S9           S11           S10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_6);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_6);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_6);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_11);

	// Timer2 servos:             S13           S14
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//GPIO_Init(GPIOB, &GPIO_InitStructure);

	//GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
	//GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);

	//// Timer2 servos:             S15          S16
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//GPIO_Init(GPIOD, &GPIO_InitStructure);

	//GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF_2);
	//GPIO_PinAFConfig(GPIOD, GPIO_PinSource4, GPIO_AF_2);

	// Timer3 servos:             S1           S2           S8           S7
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_2);

	// Timer4 servos:             S4            S3            S5            S6
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_2);
}

// Configure Timer1: 4 PWMs at 50Hz
void Timer1_Configuration(void)
{
	// Enable peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	// Configure frequency of Timer1: 50Hz
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_TimeBaseStructInit(&TIM_InitStructure);

	TIM_InitStructure.TIM_Prescaler = 40-1;
	TIM_InitStructure.TIM_Period = 20000;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1, &TIM_InitStructure);

	// Configure PWM in channel 1, 2, 3 and 4
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);

	TIM_Cmd(TIM1, ENABLE);
}

// Configure Timer2: 4 PWMs at 50Hz
void Timer2_Configuration(void)
{
	// Enable peripheral clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// Configure frequency of Timer2: 50Hz
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_TimeBaseStructInit(&TIM_InitStructure);

	TIM_InitStructure.TIM_Prescaler = 40-1;
	TIM_InitStructure.TIM_Period = 20000;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);

	// Configure PWM in channel 1, 2, 3 and 4
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);

	TIM_Cmd(TIM2, ENABLE);
}

// Configure Timer3: 4 PWMs at 50Hz
void Timer3_Configuration(void)
{
	// Enable peripheral clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// Configure frequency of Timer3: 50Hz
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_TimeBaseStructInit(&TIM_InitStructure);

	TIM_InitStructure.TIM_Prescaler = 40-1;
	TIM_InitStructure.TIM_Period = 20000;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_InitStructure);

	// Configure PWM in channel 1, 2, 3 and 4
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);

	TIM_Cmd(TIM3, ENABLE);
}

// Configure Timer4: 4 PWMs at 50Hz
void Timer4_Configuration(void)
{
	// Enable peripheral clock
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	// Configure frequency of Timer4: 50Hz
	TIM_TimeBaseInitTypeDef TIM_InitStructure;
	TIM_TimeBaseStructInit(&TIM_InitStructure);

	TIM_InitStructure.TIM_Prescaler = 40-1;
	TIM_InitStructure.TIM_Period = 20000;
	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &TIM_InitStructure);

	// Configure PWM in channel 1, 2, 3 and 4
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 1500;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);

	TIM_Cmd(TIM4, ENABLE);
}
