
#include "LIB/STD_TYPES.h"
#include "LIB/ERROR_STATE.h"

#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"
#include "MTIM/MTIM_Interface.h"


#include "RGB_LED/RGB_Config.h"
#include "RGB_LED/RGB_Interface.h"




ErrorState RGB_EnuInit(void) 
{
	u32 Local_U32Counter = 0 ;
	
	MRCC_EnuEnablePeriphClock(MRCC_GPIO) ;
	
	while (LED_PINs[ Local_U32Counter ] != '\0')
	{
		MGPIO_EnuSetPinDir( LED_PINs[ Local_U32Counter ] , OUTPUT_10MHZ_PP )  ;
		
		MGPIO_EnuSetPinVal( LED_PINs[ Local_U32Counter ] , HIGH )  ;
		
		Local_U32Counter ++ ;
	}
	
	MGPIO_EnuSetPinDir(RGB_RED_PIN , OUTPUT_10MHZ_PP) ;
	MGPIO_EnuSetPinDir(RGB_GREEN_PIN , OUTPUT_10MHZ_PP) ;
	MGPIO_EnuSetPinDir(RGB_BLUE_PIN , OUTPUT_10MHZ_PP) ;

	MGPIO_EnuSetPinVal(RGB_RED_PIN , LOW)  ;
	MGPIO_EnuSetPinVal(RGB_GREEN_PIN , LOW)  ;
	MGPIO_EnuSetPinVal(RGB_BLUE_PIN , LOW)  ;
	
	return ES_OK ;
	
}






ErrorState 	RGB_EnuLightStatus(  u8 Copy_U8PinNum ,  LED_COLOR  Copy_U8Color , LED_STATUS	LedStatus  )
{
	ErrorState error = ES_NOK ;
	
	switch (Copy_U8Color)
	{
		case COLOR_RED : 	MGPIO_EnuSetPinVal( RGB_RED_PIN , LedStatus ) ;
		
							MGPIO_EnuSetPinVal( RGB_GREEN_PIN , LedStatus^1 ) ;
							
							MGPIO_EnuSetPinVal( RGB_GREEN_PIN , LedStatus^1 ) ;
							
							error = ES_OK ;
							
		break ;

		case COLOR_GREEN : 	MGPIO_EnuSetPinVal( RGB_RED_PIN , LedStatus^1 ) ;
		
							MGPIO_EnuSetPinVal( RGB_GREEN_PIN , LedStatus ) ;
							
							MGPIO_EnuSetPinVal( RGB_GREEN_PIN , LedStatus^1 ) ;
							
							error = ES_OK ;
							
		break ;
		
		case COLOR_BLUE : 	MGPIO_EnuSetPinVal( RGB_RED_PIN , LedStatus^1 ) ;
		
							MGPIO_EnuSetPinVal( RGB_GREEN_PIN , LedStatus^1 ) ;
							
							MGPIO_EnuSetPinVal( RGB_GREEN_PIN , LedStatus ) ;
							
							error = ES_OK ;
							
		break ;
	}
	
	MGPIO_EnuSetPinVal( Copy_U8PinNum , LedStatus^1 )  ;
	
	return error ;
	
	
}




ErrorState RGB_EnuAllLightOff(void)
{
	for (u8 Count = 0 ; LED_PINs[Count]!='\0' ;Count ++)
	{
	RGB_EnuLightStatus(  LED_PINs[Count] ,  COLOR_RED , LED_OFF  ) ;
	RGB_EnuLightStatus(  LED_PINs[Count] ,  COLOR_GREEN , LED_OFF  ) ;
	RGB_EnuLightStatus(  LED_PINs[Count] ,  COLOR_BLUE , LED_OFF  ) ;

	}

	return ES_OK ;

}
