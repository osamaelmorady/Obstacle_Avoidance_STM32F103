
#include "LIB/STD_TYPES.h"
#include "LIB/DELAY.h"

#include "MRCC/MRCC_Interface.h"
#include "MTIM/MTIM_Interface.h"

#include "MGPIO/MGPIO_Interface.h"
#include "DC_Motors/MOT_DC_Interface.h"
#include "RGB_LED/RGB_Interface.h"

#include "SMART_CAR/SCAR.config.h"
#include "SMART_CAR/SCAR_Interface.h"



#define RESPONSE_DELAY		1


/******************************************************/
/******************************************************/
ErrorState SCAR_EnuInit(void)
{
	MOT_DC_EnuInit(Motor1) ;
	MOT_DC_EnuInit(Motor2) ;

	MOT_DC_EnuSetMotorDirSpeed(Motor1,DIR_CW,0)  ;
	_delay_ms(RESPONSE_DELAY) ;
	MOT_DC_EnuSetMotorDirSpeed(Motor2,DIR_CW,0)  ;
	_delay_ms(RESPONSE_DELAY) ;

	return ES_OK ;
}



/******************************************************//******************************************************/
/******************************************************//******************************************************/
ErrorState SCAR_EnuSoftStart(void)
{
	RGB_EnuLightStatus(FRONT_LED_LEFT_PIN,COLOR_BLUE,LED_ON)  ;
	RGB_EnuLightStatus(FRONT_LED_RIGHT_PIN,COLOR_BLUE,LED_ON)  ;

	/*  (Soft Start for 2 sec) */
	for (s8 i=0 ; i<=100 ;i+=1)
		{
			MOT_DC_EnuSetMotorDirSpeed(Motor1,DIR_CW,i)  ;
			_delay_ms(RESPONSE_DELAY) ;
			MOT_DC_EnuSetMotorDirSpeed(Motor2,DIR_CW,i)  ;
			_delay_ms(RESPONSE_DELAY) ;

			_delay_ms(10 - ( RESPONSE_DELAY *2) ) ;
		}
			

	return ES_OK ;
}





/******************************************************//******************************************************/
/******************************************************//******************************************************/
ErrorState SCAR_EnuSoftStop(void)
{
	RGB_EnuLightStatus(FRONT_LED_LEFT_PIN,COLOR_BLUE,LED_ON)  ;
	RGB_EnuLightStatus(FRONT_LED_RIGHT_PIN,COLOR_BLUE,LED_ON)  ;

	/*  (Soft Stop for 2 sec) */
	for (s8 i=100 ; i>=0 ;i-=1)
		{
			MOT_DC_EnuSetMotorDirSpeed(Motor1,DIR_CW,i)  ;
			_delay_ms(RESPONSE_DELAY) ;
			MOT_DC_EnuSetMotorDirSpeed(Motor2,DIR_CW,i)  ;
			_delay_ms(RESPONSE_DELAY) ;

			_delay_ms(20 - RESPONSE_DELAY *2) ;

		}
		
	return ES_OK ;
}






/******************************************************//******************************************************/
/******************************************************//******************************************************/
ErrorState SCAR_EnuMoveForward(u8 Copy_U8SpeedPercent)
{
	RGB_EnuLightStatus(FRONT_LED_LEFT_PIN,COLOR_BLUE,LED_ON)  ;
	RGB_EnuLightStatus(FRONT_LED_RIGHT_PIN,COLOR_BLUE,LED_ON)  ;

	/* Move Forward  */
	MOT_DC_EnuSetMotorDirSpeed(Motor1,DIR_CW,Copy_U8SpeedPercent)  ;
	_delay_ms(RESPONSE_DELAY) ;
	MOT_DC_EnuSetMotorDirSpeed(Motor2,DIR_CW,Copy_U8SpeedPercent)  ;
	_delay_ms(RESPONSE_DELAY) ;
	
	return ES_OK ;

}





/******************************************************//******************************************************/
/******************************************************//******************************************************/
ErrorState SCAR_EnuMoveBackWard(u8 Copy_U8SpeedPercent)
{
	RGB_EnuLightStatus(BACK_LED_LEFT_PIN,COLOR_RED,LED_ON)  ;
	RGB_EnuLightStatus(BACK_LED_RIGHT_PIN,COLOR_RED,LED_ON)  ;

	/* Move Backward  */
	MOT_DC_EnuSetMotorDirSpeed(Motor1,DIR_CCW,Copy_U8SpeedPercent)  ;
	_delay_ms(RESPONSE_DELAY) ;
	MOT_DC_EnuSetMotorDirSpeed(Motor2,DIR_CCW,Copy_U8SpeedPercent)  ;
	_delay_ms(RESPONSE_DELAY) ;
		
	return ES_OK ;
}




/******************************************************//******************************************************/
/******************************************************//******************************************************/
ErrorState SCAR_EnuTurnLeft(u8 Copy_U8SpeedPercent)
{
	RGB_EnuLightStatus(BACK_LED_RIGHT_PIN,COLOR_RED,LED_ON)  ;
	RGB_EnuLightStatus(FRONT_LED_RIGHT_PIN,COLOR_RED,LED_ON)  ;

	MOT_DC_EnuSetMotorDirSpeed(Motor1,DIR_CW,Copy_U8SpeedPercent)  ;
	_delay_ms(RESPONSE_DELAY) ;
	MOT_DC_EnuSetMotorDirSpeed(Motor2,DIR_CCW,Copy_U8SpeedPercent)  ;
	_delay_ms(RESPONSE_DELAY) ;
	
	return ES_OK ;
}




/******************************************************//******************************************************/
/******************************************************//******************************************************/
ErrorState SCAR_EnuTurnRight(u8 Copy_U8SpeedPercent)
{
	RGB_EnuLightStatus(BACK_LED_LEFT_PIN,COLOR_RED,LED_ON)  ;
	RGB_EnuLightStatus(FRONT_LED_LEFT_PIN,COLOR_RED,LED_ON)  ;

	MOT_DC_EnuSetMotorDirSpeed(Motor1,DIR_CCW,Copy_U8SpeedPercent)  ;
	_delay_ms(RESPONSE_DELAY) ;
	MOT_DC_EnuSetMotorDirSpeed(Motor2,DIR_CW,Copy_U8SpeedPercent)  ;
	_delay_ms(RESPONSE_DELAY) ;
	
	return ES_OK ;
}





/******************************************************//******************************************************/
/******************************************************//******************************************************/
ErrorState SCAR_EnuStop()
{
	MOT_DC_EnuSetMotorDirSpeed(Motor1,DIR_CW,0)  ;
	_delay_ms(RESPONSE_DELAY) ;
	MOT_DC_EnuSetMotorDirSpeed(Motor2,DIR_CW,0)  ;
	_delay_ms(RESPONSE_DELAY) ;
	
	return ES_OK ;

}



ErrorState SCAR_EnuAllLightOff(void)
{
	RGB_EnuAllLightOff() ;

	return ES_OK ;
}





