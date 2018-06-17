/* Includes ------------------------------------------------------------------*/
#include "configuration.h"

// Configure clock : HSI at 8 MHz, PLL at 40 MHz
void RCC_Configuration(void)
{
	// Configure clock : 8MHz with HSI
	RCC_HSEConfig(RCC_HSE_OFF);
	RCC_HSICmd(ENABLE);

	while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) != SET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);

	uint8_t calibration = 13;

	RCC_AdjustHSICalibrationValue(calibration);

	// Configure clock : 40MHz with PLL
	RCC_PLLCmd(DISABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != RESET);

	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_10);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
}

void GPIOs_Configuration (void)
{
	// Enable peripheral clock
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA |
						  RCC_AHBPeriph_GPIOC |
						  RCC_AHBPeriph_GPIOE, ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_StructInit(&GPIO_InitStructure);			//Initialize structure

	// LEDs
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 |
	                             GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	// Button
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// Configure the GPIO USART1 pins
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_7);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_7);
}


/**
  * @brief Configure Timer2 : interrupt at 100Hz (every 10ms).
  * @param  None
  * @retval None
  */
//void Timer2_Configuration(void)
//{
//	/* Configure frequency of timer 2 */
//
//	TIM_TimeBaseInitTypeDef TIM_InitStructure;
//	TIM_TimeBaseStructInit(&TIM_InitStructure);		//Initialize structure
//
//	TIM_InitStructure.TIM_Prescaler = 400-1;
//	TIM_InitStructure.TIM_Period = 1000;
//	TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
//	TIM_TimeBaseInit(TIM2, &TIM_InitStructure);
//
//	TIM_OCInitTypeDef TIM_OCInitStructure;
//	TIM_OCStructInit(&TIM_OCInitStructure);			//Initialize structure
//
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
//	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
//	TIM_OCInitStructure.TIM_Pulse = 1000;
//	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
//
//	TIM_ITConfig(TIM2, TIM_IT_CC1, ENABLE);
//
//	/* ENABLE TIM2 Interrupt */
//
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
//
//	NVIC_InitTypeDef NVIC_InitStructure;
//
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//
//	TIM_Cmd(TIM2, ENABLE);
//}

void USART_Configuration(void)
{
	// Enable peripheral clock
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_InitTypeDef USART_InitStrucutre;
	USART_StructInit(&USART_InitStrucutre);

	USART_InitStrucutre.USART_BaudRate = 115200;
	USART_InitStrucutre.USART_WordLength = USART_WordLength_8b;
	USART_InitStrucutre.USART_StopBits = USART_StopBits_1;
	USART_InitStrucutre.USART_Parity = USART_Parity_No;
	USART_InitStrucutre.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStrucutre.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStrucutre);

	USART_Cmd(USART1, ENABLE);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	//Enable receive Interrupt
	//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	//Enable transmit Interrupt

	/* ENABLE USART1 Interrupt */
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Gyro_Configuration(void)
{
	L3GD20_InitTypeDef L3GD20_InitStructure;
	L3GD20_FilterConfigTypeDef L3GD20_FilterStructure;

	/* Configure the Gyro */
	L3GD20_InitStructure.Power_Mode = L3GD20_MODE_ACTIVE;
	L3GD20_InitStructure.Output_DataRate = L3GD20_OUTPUT_DATARATE_4;
	L3GD20_InitStructure.Axes_Enable = L3GD20_AXES_ENABLE;
	L3GD20_InitStructure.Band_Width = L3GD20_BANDWIDTH_1;
	L3GD20_InitStructure.BlockData_Update = L3GD20_BlockDataUpdate_Continous;
	L3GD20_InitStructure.Endianness = L3GD20_BLE_LSB;
	L3GD20_InitStructure.Full_Scale = L3GD20_FULLSCALE_2000;
	L3GD20_Init(&L3GD20_InitStructure);

	/* Configure the Gyro HPF */
	L3GD20_FilterStructure.HighPassFilter_Mode_Selection = L3GD20_HPM_NORMAL_MODE_RES;
	L3GD20_FilterStructure.HighPassFilter_CutOff_Frequency = L3GD20_HPFCF_1;
	L3GD20_FilterConfig(&L3GD20_FilterStructure);

	L3GD20_FilterCmd(L3GD20_HIGHPASSFILTER_DISABLE);
}

void Accelero_Magneto_Configuration(void)
{
	LSM303DLHCMag_InitTypeDef LSM303DLHCMag_InitStructure;
	LSM303DLHCAcc_InitTypeDef LSM303DLHCAcc_InitStructure;
	//LSM303DLHCAcc_FilterConfigTypeDef LSM303DLHCAccFilter_InitStructure;

	/* Configure the Magnetometer */
	LSM303DLHCMag_InitStructure.Temperature_Sensor = LSM303DLHC_TEMPSENSOR_DISABLE;
	LSM303DLHCMag_InitStructure.MagOutput_DataRate = LSM303DLHC_ODR_220_HZ;
	LSM303DLHCMag_InitStructure.MagFull_Scale = LSM303DLHC_FS_1_3_GA;
	LSM303DLHCMag_InitStructure.Working_Mode = LSM303DLHC_CONTINUOS_CONVERSION;
	LSM303DLHC_MagInit(&LSM303DLHCMag_InitStructure);

	/* Configure the Accelerometer */
	LSM303DLHCAcc_InitStructure.Power_Mode = LSM303DLHC_NORMAL_MODE;
	LSM303DLHCAcc_InitStructure.AccOutput_DataRate = LSM303DLHC_ODR_400_HZ;
	LSM303DLHCAcc_InitStructure.Axes_Enable = LSM303DLHC_AXES_ENABLE;
	LSM303DLHCAcc_InitStructure.AccFull_Scale = LSM303DLHC_FULLSCALE_2G;
	LSM303DLHCAcc_InitStructure.BlockData_Update = LSM303DLHC_BlockUpdate_Continous;
	LSM303DLHCAcc_InitStructure.Endianness = LSM303DLHC_BLE_LSB;
	LSM303DLHCAcc_InitStructure.High_Resolution = LSM303DLHC_HR_ENABLE;
	LSM303DLHC_AccInit(&LSM303DLHCAcc_InitStructure);

	/* Configure the Accelerometer HPF */
	/*LSM303DLHCAccFilter_InitStructure.HighPassFilter_Mode_Selection = LSM303DLHC_HPM_NORMAL_MODE;
	LSM303DLHCAccFilter_InitStructure.HighPassFilter_CutOff_Frequency = LSM303DLHC_HPFCF_16;
	LSM303DLHCAccFilter_InitStructure.HighPassFilter_AOI1 = LSM303DLHC_HPF_AOI1_DISABLE;
	LSM303DLHCAccFilter_InitStructure.HighPassFilter_AOI2 = LSM303DLHC_HPF_AOI2_DISABLE;
	LSM303DLHC_AccFilterConfig(&LSM303DLHCAccFilter_InitStructure);

	LSM303DLHC_AccFilterCmd(LSM303DLHC_HighPassFilter_DISABLE);*/
}

void GyroReadAngRate(int16_t* pfData)
{
	uint8_t tmpbuffer[6] = {0};
	//int16_t RawData[3] = {0};
	uint8_t i = 0;

	L3GD20_Read(tmpbuffer,L3GD20_OUT_X_L_ADDR,6);

	for(i=0; i<3; i++)
	{
		pfData[i] = (int16_t)(((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i]);
	}

	/* multiply by sensitivity (2000 DPS full scale : 70 mDPS/digit), output in DPS */
	/*for(i=0; i<3; i++)
	{
		pfData[i] = (float)RawData[i] * 0.07f;
	}*/
}

void AcceleroReadAcc(int16_t* pfData)
{
	uint8_t tmpbuffer[6] = {0};
	//int16_t RawData[3] = {0};
	uint8_t i = 0;

	LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_L_A, tmpbuffer, 6);

	for(i=0; i<3; i++)
	{
		pfData[i] = ((int16_t)((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i])/16;
	}

	/* multiply by sensitivity (2 g full scale : 1 mg/digit), output in mg */
	/*for(i=0; i<3; i++)
	{
		pfData[i] = (float)RawData[i] * 1.0f;
	}*/
}

void MagnetoReadMag(float* pfData)
{
	uint8_t tmpbuffer[6] = {0};
	uint8_t i = 0;

	LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_X_H_M, tmpbuffer, 2);
	LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Y_H_M, tmpbuffer+2, 2);
	LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Z_H_M, tmpbuffer+4, 2);

	/* divide by gain and multiply by 10 : 10/11 : * 0.909090909 (1.3 Gauss full scale : 1100 digit/Gauss for XY), output in mGauss */
	for(i=0; i<2; i++)
	{
		pfData[i]=(float)((int16_t)((uint16_t)tmpbuffer[2*i] << 8) + tmpbuffer[2*i+1]) * 0.9090909f;
	}

	/* divide by gain and multiply by 10 : 10/9.8 : * 1.020408163 (1.3 Gauss full scale : 980 digit/Gauss for Z), output in mGauss */
	pfData[2]=(float)((int16_t)((uint16_t)tmpbuffer[4] << 8) + tmpbuffer[5]) * 1.020408163f;
}

void ReadAccMag(float* pfData_Acc, float* pfData_Mag)
{
	uint8_t tmpbuffer[6] = {0};
	int16_t RawData[3] = {0};
	int i = 0;

	LSM303DLHC_Read(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_L_A, tmpbuffer, 6);

	for(i=0; i<3; i++)
	{
		RawData[i] = ((int16_t)((uint16_t)tmpbuffer[2*i+1] << 8) + tmpbuffer[2*i])/16;
	}

	/* multiply by sensitivity (2 g full scale : 1 mg/digit), output in mg */
	for(i=0; i<3; i++)
	{
		pfData_Acc[i] = (float)RawData[i] * 1.0f;
	}

	LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_X_H_M, tmpbuffer, 2);
	LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Y_H_M, tmpbuffer+2, 2);
	LSM303DLHC_Read(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Z_H_M, tmpbuffer+4, 2);

	/* divide by gain (1.3 Gauss full scale : 1100 digit/Gauss for XY, 980 digit/Gauss for Z), output in mGauss */
	for(i=0; i<2; i++)
	{
		pfData_Mag[i]=(float)((int16_t)(((uint16_t)tmpbuffer[2*i] << 8) + tmpbuffer[2*i+1])*1000) / 1100.0f;
	}

	pfData_Mag[2]=(float)((int16_t)(((uint16_t)tmpbuffer[4] << 8) + tmpbuffer[5])*1000) / 980.0f;
}
