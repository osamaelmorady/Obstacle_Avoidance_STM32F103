#ifndef		_MNVIC_INTERFACE_H_
#define 	_MNVIC_INTERFACE_H_


#include "LIB/ERROR_STATE.h"






typedef enum INTERNAL_INTERRUPTS_IDS
{
	MNVIC_MEM_MANAGE_INT = -4 , MNVIC_BUS_FAULT_INT= -5	, MNVIC_USAGE_FAULT_INT= -6 	,
	
	MNVIC_SV_CALL_INT = -11	, MNVIC_PEND_SV_INT= -14		, MNVIC_SYS_TICK_INT= -15


}INTERNAL_INTERRUPTS_ID ;







typedef enum IRQ_IDS
{
	MNVIC_WWDG_INT =0  , MNVIC_PVD_INT   , MNVIC_TAMPER_INT , MNVIC_RTC_INT   , MNVIC_FLASH_INT , MNVIC_RCC_INT ,
	
	MNVIC_EXTI0_INT=6 , MNVIC_EXTI1_INT  , MNVIC_EXTI2_INT, MNVIC_EXTI3_INT  , MNVIC_EXTI4_INT ,
	
	MNVIC_DMA1_CH1_INT=11 , MNVIC_DMA1_CH2_INT , MNVIC_DMA1_CH3_INT , MNVIC_DMA1_CH4_INT ,  MNVIC_DMA1_CH5_INT , MNVIC_DMA1_CH6_INT , MNVIC_DMA1_CH7_INT ,
	
	/* ( ADC1 : ADC2 ) HAVE THE SAME INTERRUPT ID  */
	MNVIC_ADC1_INT=18 , MNVIC_ADC2_INT=18 ,
	
	MNVIC_USB_HP_CAN_TX_INT = 19 , MNVIC_USB_HP_CAN_RX0_INT , MNVIC_CAN_RX1_INT , MNVIC_CAN_SCE_INT ,
	
	/* ( EXTI5 : EXTI9 ) HAVE THE SAME INTERRUPT ID  */
	MNVIC_EXTI5_INT=23 , MNVIC_EXTI6_INT=23 , MNVIC_EXTI7_INT=23 , MNVIC_EXTI8_INT=23 , MNVIC_EXTI9_INT=23  , 
	
	MNVIC_TIM1_BRK_INT=24 ,  MNVIC_TIM1_UP_INT  , MNVIC_TIM1_TRG_COM_INT , MNVIC_TIM1_CC_INT , MNVIC_TIM2_INT , MNVIC_TIM3_INT , MNVIC_TIM4_INT ,
	
	MNVIC_I2C1_EV_INT=31  ,  MNVIC_I2C1_ER_INT  ,  MNVIC_I2C2_EV_INT     , MNVIC_I2C2_ER_INT , 
	
	MNVIC_SPI1_INT =35    ,  MNVIC_SPI2_INT 	,
	
	MNVIC_USART1_INT=37   ,  MNVIC_USART2_INT   , MNVIC_USART3_INT  	,
	
	/* ( EXTI10 : EXTI15 ) HAVE THE SAME INTERRUPT ID  */
	MNVIC_EXTI10_INT=40 , MNVIC_EXTI11_INT=40 , MNVIC_EXTI12_INT=40 , MNVIC_EXTI13_INT=40 , MNVIC_EXTI14_INT=40 , MNVIC_EXTI15_INT=40 ,
	
	MNVIC_RTC_ALARM_INT=41,  MNVIC_USB_WAKEUP_INT ,
	
	MNVIC_TIM8_BRK_INT=43 ,  MNVIC_TIM8_UP_INT  , MNVIC_TIM8_TRG_COM_INT , MNVIC_TIM8_CC_INT	 ,
	
	MNVIC_ADC3_INT = 47   ,  MNVIC_FSMC_INT  	, MNVIC_SDIO_INT  		 ,  MNVIC_TIM5_INT 		 , MNVIC_SPI3_INT  , MNVIC_UART4_INT  , MNVIC_UART5_INT , 
	
	MNVIC_TIM6_INT=54     ,  MNVIC_TIM7_INT 	 , 
	
	MNVIC_DMA2_CH1_INT=56 ,  MNVIC_DMA2_CH2_INT , MNVIC_DMA2_CH3_INT , 
	
	MNVIC_DMA2_CH4_INT=59 ,  MNVIC_DMA2_CH5_INT=59 
	
}IRQ_ID ;












/********************************************************/
/********************************************************/
/********************************************************/
ErrorState	 MNVIC_EnuInit(void) ;





/********************************************************/
/********************************************************/
/********************************************************/
ErrorState 	MNVIC_EnuEnableIRQ(u8 Copy_U8INTID) ;




/********************************************************/
/********************************************************/
/********************************************************/
ErrorState 	MNVIC_EnuDisableIRQ(u8 Copy_U8INTID) ;








/********************************************************/
/********************************************************/
/********************************************************/
ErrorState 	MNVIC_EnuSetPendingIRQ(u8 Copy_U8INTID) ;




/********************************************************/
/********************************************************/
/********************************************************/
ErrorState	 MNVIC_EnuClearPendingIRQ(u8 Copy_U8INTID) ;







/********************************************************/
/********************************************************/
/********************************************************/
ErrorState	 MNVIC_EnuGetIRQActiveFlag( u8 Copy_U8INTID , u8 * Copy_PU8ActiveFlagValue ) ;











/********************************************************/
/********************************************************/
/********************************************************/
ErrorState 	MNVIC_EnuSetIRQPriority( s8 Copy_U8INTID ,u8 Copy_U8GroupPriority , u8 Copy_U8SubPriority) ;














#endif
