#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"


#include "MEXTI/MEXTI_Interface.h"
#include "MEXTI/MEXTI_Private.h"
#include "MEXTI/MEXTI_Config.h"







/**********************************************************************************************************/
/********************************  EXTI Channel & TriggerMode Selection  **********************************/
/**********************************************************************************************************/
ErrorState		MEXTI_EnuInit(u8 Copy_U8EXTIChannelNum,u8 Copy_U8TriggerMode) 
{
	
	switch (Copy_U8TriggerMode) 
	{
		case MEXTI_TRIGGER_RISING :
		
			SET_BIT ( MEXTI -> RTSR , Copy_U8EXTIChannelNum )  ;
			
			CLR_BIT ( MEXTI -> FTSR , Copy_U8EXTIChannelNum )  ;
		
		break ;
		
		case MEXTI_TRIGGER_FALLING :
		
			CLR_BIT ( MEXTI -> RTSR , Copy_U8EXTIChannelNum )  ;

			SET_BIT ( MEXTI -> FTSR , Copy_U8EXTIChannelNum )  ;
		
		break ;
		
		case MEXTI_TRIGGER_ON_CHANGE :
		
			SET_BIT ( MEXTI -> RTSR , Copy_U8EXTIChannelNum )  ;

			SET_BIT ( MEXTI -> FTSR , Copy_U8EXTIChannelNum )  ;
		
		break;
		
		default : return ES_OUT_RANGE ;  break ;
		
	}
	
	SET_BIT ( MEXTI -> IMR , Copy_U8EXTIChannelNum )  ;
	
	
	return ES_OK ;
	
}








/*******************************************************************************************************/
/********************************  EXTI Channel Enable  ************************************************/
/*******************************************************************************************************/
ErrorState		MEXTI_EnuChannelEnable(u8 Copy_U8EXTIChannelNum) 
{
	SET_BIT ( MEXTI -> IMR , Copy_U8EXTIChannelNum )  ;
	
	return ES_OK ;
	
}





/*******************************************************************************************************/
/********************************  EXTI Channel Disable  ***********************************************/
/*******************************************************************************************************/
ErrorState		MEXTI_EnuChannelDisable(u8 Copy_U8EXTIChannelNum) 
{
	CLR_BIT ( MEXTI -> IMR , Copy_U8EXTIChannelNum )  ;
	
	return ES_OK ;
	
}





/************************************************************************************************/
/********************************  EXTI Wait For Flag  ******************************************/
/************************************************************************************************/
ErrorState		MEXTI_EnuLinePolling(u8 Copy_U8EXTILineNum) 
{
	while ( ! GET_BIT(MEXTI -> PR , Copy_U8EXTILineNum ) )  ;
	
	return ES_OK ;
}







/*******************************************************************************************************/
/********************************  EXTI Triggering by Software  ****************************************/
/*******************************************************************************************************/
ErrorState		MEXTI_EnuChannelSoftWareTrigger(u8 Copy_U8EXTIChannelNum)
{
	SET_BIT ( MEXTI -> SWIER , Copy_U8EXTIChannelNum ) ;
	
	return ES_OK ;
}










/*******************************************************************************************************/
/********************************  CallBack Function Configuration *************************************/
/*******************************************************************************************************/
static void (* CallBackPTR[16])(void) ;


ErrorState		MEXTI_EnuSetCallBack(u8 Copy_U8EXTIChannelNum , void (*PFun)(void)) 
{
	CallBackPTR[Copy_U8EXTIChannelNum]  =  PFun  ;
	
	return ES_OK ;
}













/*********************************************************************************/
/********************************  IRQ Handlers  *********************************/
/*********************************************************************************/
void EXTI0_IRQHandler(void)
{
	CallBackPTR[MEXTI_CH0]() ;
	
	SET_BIT(MEXTI -> PR , MEXTI_CH0 )  ;
}



/********************************************************************/
void EXTI1_IRQHandler(void)
{
	CallBackPTR[MEXTI_CH1]() ;
	
	SET_BIT(MEXTI -> PR , MEXTI_CH1 )  ;
}


/********************************************************************/
void EXTI2_IRQHandler(void)
{
	CallBackPTR[MEXTI_CH2]() ;
	
	SET_BIT(MEXTI -> PR , MEXTI_CH2 )  ;
}


/********************************************************************/
void EXTI3_IRQHandler(void)
{
	CallBackPTR[MEXTI_CH3]() ;
	
	SET_BIT(MEXTI -> PR , MEXTI_CH3 )  ;	
}


/********************************************************************/
void EXTI4_IRQHandler(void)
{
	CallBackPTR[MEXTI_CH4]() ;
	
	SET_BIT(MEXTI -> PR , MEXTI_CH4 )  ;
}


/********************************************************************/
void EXTI9_5_IRQHandler(void)
{
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH5 ) )
	{
		CallBackPTR[MEXTI_CH5]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH5 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH6 ) )
	{
		CallBackPTR[MEXTI_CH6]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH6 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH7 ) )
	{
		CallBackPTR[MEXTI_CH7]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH7 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH8 ) )
	{
		CallBackPTR[MEXTI_CH8]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH8 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH9 ) )
	{
		CallBackPTR[MEXTI_CH9]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH9 )  ;
	}
	
}


/********************************************************************/
void EXTI15_10_IRQHandler(void)
{
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH10 ) )
	{
		CallBackPTR[MEXTI_CH10]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH10 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH11 ) )
	{
		CallBackPTR[MEXTI_CH11]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH11 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH12 ) )
	{
		CallBackPTR[MEXTI_CH12]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH12 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH13 ) )
	{
		CallBackPTR[MEXTI_CH13]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH13 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH14 ) )
	{
		CallBackPTR[MEXTI_CH14]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH14 )  ;
	}
	
	if ( GET_BIT ( MEXTI -> PR , MEXTI_CH15 ) )
	{
		CallBackPTR[MEXTI_CH15]() ;
	
		SET_BIT(MEXTI -> PR , MEXTI_CH15 )  ;
	}
	
}


