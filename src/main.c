/* Includes ------------------------------------------------------------------*/
#include "configuration.h"
#include "Kalman.h"
#include <math.h>




/* Global variables ----------------------------------------------------------*/
int16_t joy1axeX = 0, trigger = 0;

float angle_Acc_LP;
float angle_Acc;
float angle;

int16_t Buffer_Gyro[3] = {0}, Buffer_Acc[3] = {0};		//Buffer of angle rate (70 mDPS/digit) and acceleration (1 mg/digit)

int main(void)
{
	/* Registers configuration -----------------------------------------------*/
	RCC_Configuration();

	GPIOs_Configuration();

	Timer4_Configuration();

	USART_Configuration();

	Gyro_Configuration();

	Accelero_Magneto_Configuration();

	/* Initialization of Kalman filter ---------------------------------------*/
	AcceleroReadAcc(Buffer_Acc);
	angle = -atan2f((float)(Buffer_Acc[2]), (float)(Buffer_Acc[0])) * RadianToDegree;
	setAngle(angle);

	/* Start of control loop -------------------------------------------------*/
	Timer2_Configuration();

	uint8_t button;
	uint8_t TX_counter = 0;
	int i;

	while(1)
	{
		button = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

		if(button != 0)
			GPIO_SetBits(GPIOE, GPIO_Pin_8);
		else
			GPIO_ResetBits(GPIOE, GPIO_Pin_8);

		switch(TX_counter)
		{
		case 0:
			/* Start of transmission */
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
			USART_SendData(USART1, (uint8_t)(12));
			TX_counter++;
			GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;

		case 1:
			/* Start of transmission */
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
			USART_SendData(USART1, (uint8_t)(13));
			TX_counter++;
			GPIO_SetBits(GPIOE, GPIO_Pin_10);
			break;

		//case 2:
		//	/* Send the angular position calculate with the Accelerometer */
		//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
		//	USART_SendData(USART1, (uint8_t)((float)((angle)+128)));
		//	TX_counter++;
		//	GPIO_SetBits(GPIOE, GPIO_Pin_11);
		//	break;

		//case 3:
		//	/* Send the angular rate calculate with the Gyrometer */
		//	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
		//	USART_SendData(USART1, (uint8_t)((consigne_angle)+128));
		//	TX_counter = 0;
		//	GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);
		//	break;

		default :
			TX_counter = 0;
			break;
		}

		for(i = 0; i < 30000; i++);
	}
}

/**
  *===========================================================================
  *
  *  STM32F30x Peripherals Interrupt Handlers
  *
  *===========================================================================
  */

/**
 * @brief  This function handles USART1 global interrupt request : interruption each time we receive a byte in UART1.
 * @param  None
 * @retval None
 */
void USART1_IRQHandler(void)
{
	static uint8_t RX_counter = 0;
	uint16_t RX_buffer = 0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		RX_buffer = USART_ReceiveData(USART1);

		switch(RX_counter)
		{
		case 0:
			/* Start of reception */
			if(RX_buffer == 12)
			{
				RX_counter++;
			}

			else
			{
				RX_counter = 0;
			}
			break;

		case 1:
			/* Start of reception */
			if(RX_buffer == 13)
			{
				RX_counter++;
			}

			else
			{
				RX_counter = 0;
			}
			break;

		case 2:
			/* Joystick 1 axe X */
			joy1axeX = (int16_t)(RX_buffer) - 128;
			RX_counter++;
			break;

		case 3:
			/* Trigger */
			trigger = (int16_t)(RX_buffer) - 128;
			RX_counter=0;
			break;
//
//		case 4:
//			/* kp */
//			//kp = (float)(RX_buffer) / 1.0;
//			kp = (float)(RX_buffer);
//			RX_counter++;
//			break;
//
//		case 5:
//			/* ki */
//			ki = (float)(RX_buffer) * 10.0;
//			RX_counter++;
//			break;
//
//		case 6:
//			/* kd */
//			kd = (float)(RX_buffer) / 10.0;
//			RX_counter++;
//			break;
//
//		case 7:
//			/* kpv */
//			kpv = (float)(RX_buffer) / 1000.0;
//			RX_counter++;
//			break;
//
//		case 8:
//			/* kiv */
//			kiv = (float)(RX_buffer) / 1000.0;
//			RX_counter++;
//			break;
//
//		case 9:
//			/* kdv */
//			kdv = (float)(RX_buffer) / 10000.0;
//			RX_counter = 0;
//			break;

		default :
			RX_counter = 0;
			break;
		}
	}
}


/**
 * @brief  This function handles TIM2 global interrupt request : interruption at 100Hz (every 10ms).
 * @param  None
 * @retval None
 */
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);


		/* Acquisition ---------------------------------------------------------------*/

		GyroReadAngRate(Buffer_Gyro);
		AcceleroReadAcc(Buffer_Acc);

		/* Angular Position computation with complementary filters -------------------*/

		/*angle_Acc = -atan2f((float)(Buffer_Acc[2]), (float)(Buffer_Acc[0])) * RadianToDegree;
		angle_Gyro = -(float)(Buffer_Gyro[0]) * 0.0007;		//Convert in DPS then in degrees between the last 10ms (70 mDPS/digit, 100Hz)

		angle_Acc_LP = prev_Acc_LP + ((angle_Acc - prev_Acc_LP) / 16.0);
		prev_Acc_LP = angle_Acc_LP;

		angle = angle_Acc_LP + angle_Gyro;*/


		/* Angular Position computation with Kalman filter ---------------------------*/
		angle_Acc = -atan2f((float)(Buffer_Acc[2]), (float)(Buffer_Acc[0])) * RadianToDegree;

		angle = getAngle(angle_Acc, (float)(Buffer_Gyro[0]) * -0.07f);
	}
}
