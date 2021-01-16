
#include "LIB/STD_TYPES.h"
#include "LIB/ERROR_STATE.h"


#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"
#include "MTIM/MTIM_Interface.h"
#include "DC_Motors/MOT_DC_Interface.h"




/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  MOT_DC_EnuInit(MOTOR_Configurations MOTx )
{
	ErrorState error = ES_NOK ;

	MRCC_InitSysClk() ;

	MRCC_EnuEnablePeriphClock(MRCC_GPIO) ;
	MRCC_EnuEnablePeriphClock(MRCC_AFIO) ;

	if 		(MOTx.TIMx_Num == MTIM1)		MRCC_EnuEnablePeriphClock(MRCC_TIM1) ;
	else if (MOTx.TIMx_Num == MTIM2)		MRCC_EnuEnablePeriphClock(MRCC_TIM2) ;
	else if (MOTx.TIMx_Num == MTIM3) 		MRCC_EnuEnablePeriphClock(MRCC_TIM3) ;
	else if (MOTx.TIMx_Num == MTIM4) 		MRCC_EnuEnablePeriphClock(MRCC_TIM4) ;
	else { return ES_OUT_RANGE ; }

	u32 Local_TimerNum = (u32)MOTx.TIMx_Num  ;

	switch (Local_TimerNum)
	{
		case (u32)MTIM1:


			MGPIO_EnuSetPinDir(MOTx.CHx_Num1 +8,OUTPUT_10MHZ_PP_AF) ;
			MGPIO_EnuSetPinDir(MOTx.CHx_Num2 +8,OUTPUT_10MHZ_PP_AF) ;

		break ;

		case (u32)MTIM2:

			MGPIO_EnuSetPinDir(MOTx . CHx_Num1  , OUTPUT_10MHZ_PP_AF) ;
			MGPIO_EnuSetPinDir(MOTx . CHx_Num2  , OUTPUT_10MHZ_PP_AF) ;

			break ;

		case (u32)MTIM3:

			if ((MOTx . CHx_Num1 <= 1 ) && ( MOTx . CHx_Num2 <= 1))
			{
				MGPIO_EnuSetPinDir(MOTx . CHx_Num1 +6 , OUTPUT_10MHZ_PP_AF) ;
				MGPIO_EnuSetPinDir(MOTx . CHx_Num2 +6 , OUTPUT_10MHZ_PP_AF) ;
			}
			else if ((MOTx . CHx_Num1 <= 3 ) && ( MOTx . CHx_Num2 <= 3))
			{
				MGPIO_EnuSetPinDir(MOTx . CHx_Num1 +16 , OUTPUT_10MHZ_PP_AF) ;
				MGPIO_EnuSetPinDir(MOTx . CHx_Num2 +16 , OUTPUT_10MHZ_PP_AF) ;
			}
			else
			{
				error = ES_OUT_RANGE ;
			}

			break ;

		case (u32)MTIM4:

			if ((MOTx . CHx_Num1 <= 1) && (MOTx . CHx_Num2 <= 1 ))
			{
				MGPIO_EnuSetPinDir(MOTx . CHx_Num1 +22 , OUTPUT_10MHZ_PP_AF) ;
				MGPIO_EnuSetPinDir(MOTx . CHx_Num2 +22 , OUTPUT_10MHZ_PP_AF) ;

			}

			break ;

		default :	error = ES_OUT_RANGE ; 			break ;


		}


		PWM_Configurations CH1_Config1 = {MOTx . CHx_Num1 , PWM_POLARITY_ACTIVE_HIGH  , STATUS_DISABLE ,  PWM_CM_UP_COUNTER_ACTIVE}  ;
		PWM_Configurations CH2_Config2 = {MOTx . CHx_Num2 , PWM_POLARITY_ACTIVE_HIGH  , STATUS_DISABLE ,  PWM_CM_UP_COUNTER_ACTIVE}  ;

		MPWM_EnuInit(MOTx . TIMx_Num , CH1_Config1) ;
		MPWM_EnuInit(MOTx . TIMx_Num , CH2_Config2) ;

		MPWM_EnuPulseFrequency(MOTx . TIMx_Num , MOTx . PWM_Frequency)  ;

		MPWM_EnuSetDutyCycle(MOTx . TIMx_Num , MOTx . CHx_Num1 , 0 )  ;
		MPWM_EnuSetDutyCycle(MOTx . TIMx_Num , MOTx . CHx_Num2 , 0 )  ;

		MPWM_EnuStatus(MOTx . TIMx_Num , STATUS_ENABLE)  ;

		MPWM_EnuChannelStatus(MOTx . TIMx_Num, MOTx . CHx_Num1 ,STATUS_ENABLE) ;
		MPWM_EnuChannelStatus(MOTx . TIMx_Num, MOTx . CHx_Num2 ,STATUS_ENABLE) ;


	return error ;
}




/****************************************************************************************************/
/****************************************************************************************************/
/****************************************************************************************************/
ErrorState MOT_DC_EnuSetMotorDirSpeed(MOTOR_Configurations MOTx , DIRECTION_STATUS	Copy_DirStatus , u8 Copy_U8SpeedPercent )
{
	ErrorState error = ES_NOK ;

	if (Copy_DirStatus == DIR_CW)
		{
			MPWM_EnuSetDutyCycle(MOTx . TIMx_Num , MOTx . CHx_Num1 , Copy_U8SpeedPercent )  ;
			MPWM_EnuSetDutyCycle(MOTx . TIMx_Num , MOTx . CHx_Num2 , 0 )  ;
		}
	if (Copy_DirStatus == DIR_CCW)
		{
			MPWM_EnuSetDutyCycle(MOTx . TIMx_Num , MOTx . CHx_Num1 , 0 )  ;
			MPWM_EnuSetDutyCycle(MOTx . TIMx_Num , MOTx . CHx_Num2 , Copy_U8SpeedPercent )  ;

		}

	return error ;
}







