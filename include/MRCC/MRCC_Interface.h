
#ifndef		_MRCC_INTERFACE_H_
#define 	_MRCC_INTERFACE_H_


#include "LIB/ERROR_STATE.h"


/***************************************************************************/
/************************	RCC_BUS_CHANNEL	****************************/
/***************************************************************************/
typedef enum BUSES_NAMES
{
	MRCC_AHB = 0  ,	MRCC_APB1   ,	MRCC_APB2

}BUS_NAME ;




/***************************************************************************/
/***********************	PERIPHERAL_SELECTION	***********************/
/***************************************************************************/

typedef enum PERIPHERALS_NAMES
{
	/* AHB Peripherals */
	MRCC_DMA1 = 0	, MRCC_DMA2 = 1 , MRCC_SRAM = 2 , 	MRCC_FLITF = 4 , 	MRCC_CRCE = 6 , 	MRCC_FSMC = 8 , 	MRCC_SDIO = 10 ,


	/* APB1 Peripherals */
	MRCC_TIM2 = 32     ,  MRCC_TIM3    , MRCC_TIM4    , MRCC_TIM5   , MRCC_TIM6  ,  MRCC_TIM7 , MRCC_TIM12 , MRCC_TIM13 , MRCC_TIM14   ,
	MRCC_WDT =43      ,
	MRCC_SPI2 = 46    ,  MRCC_SPI3    ,
	MRCC_USART2 = 49  ,  MRCC_USART3  ,  MRCC_USART4 , MRCC_USART5 , MRCC_I2C1  , MRCC_I2C2  ,  MRCC_USB  ,
	MRCC_CAN = 57 ,
	MRCC_DAC = 61 ,


	/* APB2 Peripherals */
	MRCC_AFIO=64 ,
	MRCC_GPIO = 66 ,
	MRCC_ADC1 = 73   ,  MRCC_ADC2   ,  MRCC_TIM1   ,  MRCC_SPI1   ,  MRCC_TIM8    ,  MRCC_USART1  ,  MRCC_ADC3   ,
	MRCC_TIM9 = 83  , 	MRCC_TIM10 , MRCC_TIM11


}PERIPHERAL_NAME ;






/*******************************************************************************************************/
/**************************************	MRCC  INITIALIZATION	*************************************/
/*******************************************************************************************************/
ErrorState MRCC_InitSysClk(void) ;








/***************************************************************************************************************/
/*****************************************		PERIPHERAL ENABLE  	****************************************/
/***************************************************************************************************************/

ErrorState 	MRCC_EnuEnablePeriphClock( u8 Copy_u8PeripheralId );









/***************************************************************************************************************/
/*****************************************		PERIPHERAL DISABLE  	****************************************/
/***************************************************************************************************************/

ErrorState 	MRCC_EnuDisablePeriphClock( u8 Copy_u8PeripheralId );







#endif
