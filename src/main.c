/* Includes --------------------------------------------------------------------------------------*/
#include "configuration.h"
#include "servo.h"
#include <math.h>

/* Global variables ------------------------------------------------------------------------------*/
uint8_t Servo_Raw_Buffer[24] = {0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05,
                                0xDC, 0x05};
uint8_t New_CRC = 0;
uint8_t New_Data = 0;


int main(void)
{
	// Registers configuration
	RCC_Configuration();

	GPIOs_Configuration();

	USART_Configuration();

	Servo_Configuration();

	// Start of control loop
	//Timer2_Configuration();

	uint8_t button;
	uint8_t TX_counter = 0;
	int i;

	while(1) {
		button = GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0);

		if(button != 0) {
			GPIO_SetBits(GPIOE, GPIO_Pin_8);
		} else {
			GPIO_ResetBits(GPIOE, GPIO_Pin_8);
		}

		switch(TX_counter) {
		case 0:
			// Start of transmission
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
			USART_SendData(USART1, (uint8_t)(10));
			TX_counter++;
			GPIO_SetBits(GPIOE, GPIO_Pin_9);
			break;

		case 1:
			// Start of transmission
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
			USART_SendData(USART1, (uint8_t)(69));
			TX_counter++;
			GPIO_SetBits(GPIOE, GPIO_Pin_10);
			break;

		case 2:
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
			USART_SendData(USART1, (uint8_t)(14));
			TX_counter++;
			GPIO_SetBits(GPIOE, GPIO_Pin_11);
			break;

		case 3:
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) != SET);
			USART_SendData(USART1, (uint8_t)(15));
			TX_counter = 0;
			GPIO_ResetBits(GPIOE, GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11);
			break;

		default :
			TX_counter = 0;
			break;
		}

		if(New_Data == 1) {
			New_Data = 0;

			uint8_t Computed_CRC = 0;
			for(i = 0; i < 24; i++) {
				Computed_CRC = Computed_CRC ^ Servo_Raw_Buffer[i];
			}

			if(Computed_CRC == New_CRC) {
				for(i = 0; i < 12; i++) {
					uint16_t PWM = (uint16_t)(Servo_Raw_Buffer[i * 2]) + ((uint16_t)(Servo_Raw_Buffer[(i * 2) + 1]) << 8);
					Set_Servo_PWM(i + 1, PWM);
				}
			}
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
	static uint8_t RX_Counter = 0;
	uint16_t RX_Buffer = 0;

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) {
		RX_Buffer = USART_ReceiveData(USART1);

		switch(RX_Counter) {
		case 0:
			// Start of reception
			if(RX_Buffer == 10) {
				RX_Counter++;
			} else {
				RX_Counter = 0;
			}
			break;

		case 1:
			// Start of reception
			if(RX_Buffer == 69) {
				RX_Counter++;
			} else {
				RX_Counter = 0;
			}
			break;

		case 26:
			New_CRC = RX_Buffer;
			New_Data = 1;
			RX_Counter = 0;
			break;

		default:
			if(RX_Counter > 1 && RX_Counter < 26) {
				Servo_Raw_Buffer[RX_Counter - 2] = RX_Buffer;
				RX_Counter++;
			} else {
				RX_Counter = 0;
			}
			break;
		}
	}
}


/**
 * @brief  This function handles TIM2 global interrupt request : interruption at 100Hz (every 10ms).
 * @param  None
 * @retval None
 */
//void TIM2_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
//	{
//		TIM_ClearITPendingBit(TIM2, TIM_IT_CC1);
//
//
//		/* Acquisition -----------------------------------------------------------------------------------*/
//
//		GyroReadAngRate(Buffer_Gyro);
//		AcceleroReadAcc(Buffer_Acc);
//
//		/* Angular Position computation with complementary filters ---------------------------------------*/
//
//		/*angle_Acc = -atan2f((float)(Buffer_Acc[2]), (float)(Buffer_Acc[0])) * RadianToDegree;
//		angle_Gyro = -(float)(Buffer_Gyro[0]) * 0.0007;		//Convert in DPS then in degrees between the last 10ms (70 mDPS/digit, 100Hz)
//
//		angle_Acc_LP = prev_Acc_LP + ((angle_Acc - prev_Acc_LP) / 16.0);
//		prev_Acc_LP = angle_Acc_LP;
//
//		angle = angle_Acc_LP + angle_Gyro;*/
//
//
//		/* Angular Position computation with Kalman filter -----------------------------------------------*/
//		angle_Acc = -atan2f((float)(Buffer_Acc[2]), (float)(Buffer_Acc[0])) * RadianToDegree;
//
//		angle = getAngle(angle_Acc, (float)(Buffer_Gyro[0]) * -0.07f);
//	}
//}
