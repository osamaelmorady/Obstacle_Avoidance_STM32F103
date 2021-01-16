#ifndef		_MOT_DC_INTERFACE_H_
#define		_MOT_DC_INTERFACE_H_



#include "MTIM/MTIM_Interface.h"



typedef enum
{
	DIR_CW , DIR_CCW

}DIRECTION_STATUS ;


typedef struct
{
	MTIM_Typedef * 	  TIMx_Num ;
	UTILS_PWM_CHANNEL CHx_Num1 ;
	UTILS_PWM_CHANNEL CHx_Num2 ;
	u32 		PWM_Frequency ;

}MOTOR_Configurations ;




/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  MOT_DC_EnuInit(MOTOR_Configurations MOTx );


/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
ErrorState MOT_DC_EnuSetMotorDirSpeed(MOTOR_Configurations MOTx , DIRECTION_STATUS	Copy_DirStatus , u8 Copy_U8SpeedPercent );










#endif
