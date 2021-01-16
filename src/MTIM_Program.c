

#include  "LIB/STD_TYPES.h"
#include  "LIB/BIT_MATH.h"
#include  "LIB/ERROR_STATE.h"

#include "MTIM/MTIM_Private.h"
#include "MTIM/MTIM_Config.h"
#include "MTIM/MTIM_Interface.h"

#include "MRCC/MRCC_Interface.h"








/***********************************************//***********************************************//***********************************************//***********************************************/
/***********************************************//***************************************		TIMER_APIs 	**************************************//**********************************************/
/***********************************************//***********************************************//***********************************************//***********************************************/

/***************************************************************************/
/***************************************************************************/
ErrorState	MTIM_EnuInit(MTIM_Typedef * TIMx_Num , TIMER_Configurations * TIMx_Config )
{

	/********************************************************************************/
		/* Disable Timer Counter CEN */
		CLR_BIT ( TIMx_Num -> CR1 , CEN )  ;
	/********************************************************************************/



	/********************************************************************************/
		/* Disable URS  */
		CLR_BIT ( TIMx_Num -> CR1 , URS )  ;
	/********************************************************************************/


	/********************************************************************************/
		/* Update Event UDIS Config  */
		CLR_BIT ( TIMx_Num -> CR1 , UDIS )  ;
		TIMx_Num -> CR1 |= ( ~ TIMx_Config->TIM_EVENT_UPDATE) << UDIS  ;
	/********************************************************************************/



	/********************************************************************************/
		/* Continuous Pulse Mode OPM Config */
		CLR_BIT ( TIMx_Num -> CR1 , OPM )  ;

		TIMx_Num -> CR1 |=   TIMx_Config->TIM_PULSE_MODE << OPM  ;
	/********************************************************************************/



	/********************************************************************************/
		/*Counter Direction DIR Config */
		CLR_BIT ( TIMx_Num -> CR1 , DIR )  ;

		TIMx_Num -> CR1 |=   TIMx_Config->TIM_COUNTER_DIRECTION << DIR  ;
	/********************************************************************************/



	/********************************************************************************/
		/* Disable Auto Reload Preload ARRE */
		CLR_BIT ( TIMx_Num -> CR1 , ARRE )  ;
	/********************************************************************************/


	/********************************************************************************/

		if ( TIMx_Config -> TIM_INTERRUPT_STATUS == STATUS_DISABLE )
		{
			/* SET Update Generation UG */
			SET_BIT ( TIMx_Num -> EGR , UG )  ;

			/*  Interrupt UIE Config */
			CLR_BIT ( TIMx_Num -> DIER , UIE )  ;


		}
		else if (TIMx_Config -> TIM_INTERRUPT_STATUS == STATUS_ENABLE)
		{
			/* Clear Update Generation UG */
			CLR_BIT ( TIMx_Num -> EGR , UG )  ;

			/*  Interrupt UIE Config */
			SET_BIT ( TIMx_Num -> DIER , UIE )  ;
		}
	/********************************************************************************/



	/********************************************************************************/
		/* Initialize Preload */
		TIMx_Num -> CNT  =  0 ;
	/********************************************************************************/


	/********************************************************************************/
		/* Initialize Loaded Value */
		TIMx_Num -> ARR  =  0 ;
	/********************************************************************************/


	/********************************************************************************/
		/* Initialize Prescaller */ /* Time Base */
		TIMx_Num -> PSC  =  0 ;
		TIMx_Num -> PSC = TIMx_Config -> TIM_PRESCALLER ;
	/********************************************************************************/



	/********************************************************************************/
		/* No Repetition */
		TIMx_Num -> RCR  =  0 ;
		TIMx_Num -> RCR  =  TIMx_Config -> TIM_REPETITION_VAL ;
	/********************************************************************************/


	

	return ES_OK ;
}








/***************************************************************************/
/***************************************************************************/
ErrorState	MTIM_EnuStatus(MTIM_Typedef * TIMx_Num , UTILS_STATUS Copy_U8CounterStatus)
{
	ErrorState error =ES_NOK  ;

	switch(Copy_U8CounterStatus)
	{
		case STATUS_DISABLE :

			/* Disable Timer */
			CLR_BIT ( TIMx_Num -> CR1 , CEN )  ;

			/* Initialize Counts = 0 */
			TIMx_Num -> CNT  =  0 ;

			/* Clear Flag */
			CLR_BIT( TIMx_Num -> SR , UIF )   ;

			error = ES_OK ;

		break ;
	
		case STATUS_ENABLE :

			/* Enable Timer */
			SET_BIT ( TIMx_Num -> CR1 , CEN )  ;

			error = ES_OK ;
	
		break ;

		default :

			error = ES_NOK ;
	
	}
	
	return error ;
}






/***************************************************************************/
/***************************************************************************/
ErrorState	MTIM_EnuBusyWait(MTIM_Typedef * TIMx_Num , u32 Copy_U32Period_US)
{


	/* Initialize AutoReload */
	TIMx_Num -> ARR  =  Copy_U32Period_US ;

	/* Clear Flag */
	CLR_BIT( TIMx_Num -> SR , UIF )   ;

	/* Timer Turns On */
	MTIM_EnuStatus( TIMx_Num , STATUS_ENABLE)  ;

	while ( GET_BIT( TIMx_Num -> SR , UIF ) == 0 )  ;

	/* Clear Flag */
	CLR_BIT( TIMx_Num -> SR , UIF )   ;

	MTIM_EnuStatus(TIMx_Num , STATUS_DISABLE) ;

	return ES_OK ;
}






/***************************************************************************/
/***************************************************************************/
ErrorState	MTIM_EnuGetElapsedTime(MTIM_Typedef * TIMx_Num , u32 * Copy_U32Period_US)
{
	* Copy_U32Period_US = TIMx_Num -> CNT   ;

	return ES_OK ;
}



/***************************************************************************/
/***************************************************************************/
ErrorState	MTIM_EnuGetRemainingTime(MTIM_Typedef * TIMx_Num , u32 * Copy_U32Period_US)
{
	* Copy_U32Period_US = ( TIMx_Num -> ARR - TIMx_Num -> CNT )  ;

	return ES_OK ;
}




/***************************************************************************/
/***************************************************************************/
static void (* TIM_CallBackFun[10])(void)  ;


static u32 TIM_Interval[10] = {} ;





/***************************************************************************/
/***************************************************************************/
ErrorState	MTIM_EnuSingleInterval(MTIM_Typedef * TIMx_Num ,  u32 Copy_U32Period_US , void (* Copy_PFun)(void) )
{
	ErrorState error = ES_NOK ;

	/* Initialize AutoReload */
	TIMx_Num -> ARR  =  Copy_U32Period_US ;

	if (TIMx_Num == MTIM1)
	{
		TIM_CallBackFun[1] = Copy_PFun  ;

		TIM_Interval[1] = TIM_INTERVAL_SINGLE ;

		error = ES_OK ;
	}
	else if (TIMx_Num == MTIM2)
	{
		TIM_CallBackFun[2] = Copy_PFun  ;

		TIM_Interval[2] = TIM_INTERVAL_SINGLE ;

		error = ES_OK ;

	}
    else if (TIMx_Num == MTIM3)
    {
		TIM_CallBackFun[3] = Copy_PFun  ;

		TIM_Interval[3] = TIM_INTERVAL_SINGLE ;

		error = ES_OK ;

	}
	else if (TIMx_Num == MTIM4)
	{
		TIM_CallBackFun[4] = Copy_PFun  ;

		TIM_Interval[4] = TIM_INTERVAL_SINGLE ;

		error = ES_OK ;

    }
	else
	{
		error = ES_OUT_RANGE ;

	}

	return error ;
}







/***************************************************************************/
/***************************************************************************/
ErrorState	MTIM_EnuPeriodicInterval(MTIM_Typedef * TIMx_Num ,  u32 Copy_U32Period_US , void (* Copy_PFun)(void) )
{
	ErrorState error = ES_NOK ;

	/* Initialize AutoReload */
	TIMx_Num -> ARR  =  Copy_U32Period_US ;


    if (TIMx_Num == MTIM1)
	{
		TIM_CallBackFun[1] = Copy_PFun  ;

		TIM_Interval[1] = TIM_INTERVAL_CONTINOUS ;

		error = ES_OK ;
	}
	else if (TIMx_Num == MTIM2)
	{
		TIM_CallBackFun[2] = Copy_PFun  ;

		TIM_Interval[2] = TIM_INTERVAL_CONTINOUS ;

		error = ES_OK ;

	}
	else if (TIMx_Num == MTIM3)
	{
		TIM_CallBackFun[3] = Copy_PFun  ;

		TIM_Interval[3] = TIM_INTERVAL_CONTINOUS ;

		error = ES_OK ;

	}
	else if (TIMx_Num == MTIM4)
	{
		TIM_CallBackFun[4] = Copy_PFun  ;

		TIM_Interval[4] = TIM_INTERVAL_CONTINOUS ;

		error = ES_OK ;

	   }
	else
	{
		error = ES_OUT_RANGE ;
	}

	return error ;
}





/***************************************************************************/
/***************************************************************************/
void TIM1_UP_IRQHandler()
{
	/* Clear Flag */
	CLR_BIT( MTIM1 -> SR , 0 )   ;

	if (TIM_Interval[1] == TIM_INTERVAL_SINGLE)
	{
		/*  Disable Interrupt UIE */
		CLR_BIT ( MTIM1 -> DIER , UIE )  ;

		MTIM_EnuStatus( MTIM1 , STATUS_DISABLE) ;
	}
	else if (TIM_Interval[1] == TIM_INTERVAL_CONTINOUS)
	{

	}

	TIM_CallBackFun[1]() ;

}



/***************************************************************************/
/***************************************************************************/
void TIM2_IRQHandler()
{
	/* Clear Flag */
	CLR_BIT( MTIM2 -> SR , 0 )   ;

	if (TIM_Interval[2] == TIM_INTERVAL_SINGLE)
	{
		/*  Disable Interrupt UIE */
		CLR_BIT ( MTIM2 -> DIER , UIE )  ;

		MTIM_EnuStatus( MTIM2 , STATUS_DISABLE) ;
	}
	else if (TIM_Interval[2] == TIM_INTERVAL_CONTINOUS)
	{

	}

	TIM_CallBackFun[2]() ;


}



/***************************************************************************/
/***************************************************************************/
void TIM3_IRQHandler()
{
	/* Clear Flag */
	CLR_BIT( MTIM3 -> SR , 0 )   ;

	if (TIM_Interval[3] == TIM_INTERVAL_SINGLE)
	{
		/*  Disable Interrupt UIE */
		CLR_BIT ( MTIM3 -> DIER , UIE )  ;

		MTIM_EnuStatus( MTIM3 , STATUS_DISABLE) ;
	}
	else if (TIM_Interval[3] == TIM_INTERVAL_CONTINOUS)
	{

	}

	TIM_CallBackFun[3]() ;


}



/***************************************************************************/
/***************************************************************************/
void TIM4_IRQHandler()
{
	/* Clear Flag */
	CLR_BIT( MTIM4 -> SR , 0 )   ;

	if (TIM_Interval[4] == TIM_INTERVAL_SINGLE)
	{
		/*  Disable Interrupt UIE */
		CLR_BIT ( MTIM4 -> DIER , UIE )  ;

		MTIM_EnuStatus( MTIM4 , STATUS_DISABLE) ;
	}
	else if (TIM_Interval[4] == TIM_INTERVAL_CONTINOUS)
	{

	}

	TIM_CallBackFun[4]() ;


}









































/***********************************************//***********************************************//***********************************************//***********************************************/
/***********************************************//***************************************		PWM_APIs 	******************************************//**********************************************/
/***********************************************//***********************************************//***********************************************//***********************************************/







/***********************************************/
/***********************************************/
ErrorState	MPWM_EnuInit(MTIM_Typedef * TIMx_Num   , PWM_Configurations  CHx_Config )
{

	/********************************************************************************/
		/* Disable Timer Counter CEN */
		CLR_BIT ( TIMx_Num -> CR1 , CEN )  ;				// Disable the timer
	/********************************************************************************/



	/********************************************************************************/
		/* Disable URS  */ /* For overflow & underflow update only */
		CLR_BIT ( TIMx_Num -> CR1 , URS )  ;			// Disable update request
	/********************************************************************************/


	/********************************************************************************/
		/* Update Event UDIS Config  */
		SET_BIT ( TIMx_Num -> CR1 , UDIS )  ;			// Disable update event  ( No need to UEV in PWM (optional) )
	/********************************************************************************/



	/********************************************************************************/
		/* Continuous Pulse Mode OPM Config */
		CLR_BIT ( TIMx_Num -> CR1 , OPM )  ;			// Enable continuous ( Disable OPM )
	/********************************************************************************/



	/********************************************************************************/
		/*Counter Direction DIR Config */ /* Up or dowm */
		CLR_BIT ( TIMx_Num -> CR1 , DIR )  ;           // Up Counter
	/********************************************************************************/


	/********************************************************************************/
		/* Center Aligned Mode */ /* Edge-Mode , Center-Aligned-Mode1 , Center-Aligned-Mode2 , Center-Aligned-Mode3 */
		CLR_BIT ( TIMx_Num -> CR1 , 5 )  ;
		CLR_BIT ( TIMx_Num -> CR1 , 6 )  ; 			// Edge-Mode
    /********************************************************************************/


	/********************************************************************************/
		/* Auto Reload Preload Buffer ARRE */
		CLR_BIT ( TIMx_Num -> CR1 , ARRE )  ;				// Disable	Auto-Reload Buffer
	/********************************************************************************/


	/********************************************************************************/

	/* SET Update Generation UG */
		CLR_BIT ( TIMx_Num -> EGR , UG )  ;		//  Disable Software update event generate
		CLR_BIT ( TIMx_Num -> EGR , 1 )  ;			//  Disable Software update Compare generate
		CLR_BIT ( TIMx_Num -> EGR , 2 )  ;			//  Disable Software update Compare generate
		CLR_BIT ( TIMx_Num -> EGR , 3 )  ;			//  Disable Software update Compare generate
		CLR_BIT ( TIMx_Num -> EGR , 4 )  ;			//  Disable Software update Compare generate

	/*  Interrupt UIE Config */
		CLR_BIT ( TIMx_Num -> DIER , UIE )  ;			// Disable UEV Interrupt

	/********************************************************************************/


	


	/********************************************************************************/
		/* Capture Compare Selection  CC1 , CC2 , CC3 , CC4 */
		TIMx_Num -> CCMR1  &= ~ 0b11 ;
		TIMx_Num -> CCMR1  |= 0b00 ; 			//		CC1 Configured as Output
		
		/* Capture Compare Selection  CC2 */
		TIMx_Num -> CCMR1  &= ~ ( 0b11 << 8 ) ;
		TIMx_Num -> CCMR1  |= ( 0b00 << 8 ) ; 			//		CC2 Configured as Output
		
		/* Capture Compare Selection CC3  */
		TIMx_Num -> CCMR2  &= ~ 0b11 ;
		TIMx_Num -> CCMR2  |= 0b00 ; 			//		CC3 Configured as Output
		
		/* Capture Compare Selection CC4  */
		TIMx_Num -> CCMR2  &= ~( 0b11 << 8 ) ;
		TIMx_Num -> CCMR2  |= ( 0b00 << 8 ); 			//		CC4 Configured as Output
	/********************************************************************************/
	
	


	
	/********************************************************************************/
		SET_BIT ( TIMx_Num -> CCMR1 , 2 )  ;			// Fast Enable
		SET_BIT ( TIMx_Num -> CCMR1 , 10 )  ;			// Fast Enable
		SET_BIT ( TIMx_Num -> CCMR2 , 2 )  ;			// Fast Enable
		SET_BIT ( TIMx_Num -> CCMR2 , 10 )  ;			// Fast Enable
	/********************************************************************************/
		

	/********************************************************************************/
		/* Capture Compare Preload Selection  */
		CLR_BIT ( TIMx_Num -> CCMR1 , 3 )  ;			//		Disable Auto reload Buffer
		CLR_BIT ( TIMx_Num -> CCMR1 , 11 )  ;			//		Disable Auto reload Buffer
		CLR_BIT ( TIMx_Num -> CCMR2 , 3 )  ;			//		Disable Auto reload Buffer
		CLR_BIT ( TIMx_Num -> CCMR2 , 11 )  ;			//		Disable Auto reload Buffer

	/********************************************************************************/

	

	/********************************************************************************/
		/* Output Compare Mode Selection  */
		MPWM_EnuChannelCompareMode( TIMx_Num , CHx_Config.Channel_Num , CHx_Config.Channel_CompareMode )	 ;
	/********************************************************************************/


	/********************************************************************************/
		/* Capture Compare Output Polarity  */
		MPWM_EnuChannelPolarity( TIMx_Num ,  CHx_Config.Channel_Num , CHx_Config.Channel_Polarity )   ;
	/********************************************************************************/


	/********************************************************************************/
		/* Capture Compare main Out Enable MOE  */
		SET_BIT ( TIMx_Num -> BDTR , 15 )  ;
	/********************************************************************************/







	/********************************************************************************/
		/* Initialize Preload */
		TIMx_Num -> CNT  =  0 ;
	/********************************************************************************/


	/********************************************************************************/
		/* Initialize Loaded Value */
		TIMx_Num -> ARR  =  0xFFFF ;
	/********************************************************************************/


	/********************************************************************************/
		/* Initialize Prescaller */ /* PWM Base */
		TIMx_Num -> PSC  =  8 ;		// Default 8
	/********************************************************************************/

	/********************************************************************************/
		/* Initialize DutyCycle */ /* PWM Base */
		TIMx_Num -> CCR1  = ( (u32) TIMx_Num -> ARR ) /2 ;   // Default 50% Duty Cycle
		TIMx_Num -> CCR2  = ( (u32) TIMx_Num -> ARR ) /2 ;   // Default 50% Duty Cycle
		TIMx_Num -> CCR3  = ( (u32) TIMx_Num -> ARR ) /2 ;   // Default 50% Duty Cycle
		TIMx_Num -> CCR4  = ( (u32) TIMx_Num -> ARR ) /2 ;   // Default 50% Duty Cycle
	/********************************************************************************/



	/********************************************************************************/
		/* No Repetition */
		TIMx_Num -> RCR  =  0 ;
	/********************************************************************************/


	/********************************************************************************/
		/* CC Output Pin Enable/Disable  */
		MPWM_EnuChannelStatus( TIMx_Num ,  CHx_Config.Channel_Num , CHx_Config.Channel_Status )   ;
	/********************************************************************************/




		return ES_OK ;


}







/***************************************************************************/
/***********************  PWM Mode Enable/Disable  *************************/
/***************************************************************************/
ErrorState	MPWM_EnuStatus(MTIM_Typedef * TIMx_Num   , UTILS_STATUS Copy_U8Status)
{
	ErrorState error =ES_NOK  ;

	switch(Copy_U8Status)
	{
		case STATUS_DISABLE :

			/* Disable Timer */
			CLR_BIT ( TIMx_Num -> CR1 , CEN )  ;

			/* Clear Flag */
			CLR_BIT( TIMx_Num -> SR , UIF )   ;		error = ES_OK ;			break ;
	
		case  STATUS_ENABLE :

			/* Enable Timer */
			SET_BIT ( TIMx_Num -> CR1 , CEN )  ;		error = ES_OK ;				break ;

		default :

			error = ES_NOK ;
	
	}
	
	return error ;
}












/***************************************************************************/
/***************************************************************************/
ErrorState	MPWM_EnuChannelPolarity(MTIM_Typedef * TIMx_Num   , UTILS_PWM_CHANNEL Copy_U8Channel , UTILS_CHANNEL_POLARITY Copy_U8Polarity)
{
	ErrorState error = ES_NOK ;
	
	switch (Copy_U8Channel)
	{
			/*  Set Pulse Polarity */
		
	/* CC1P */
		case PWM_CH1   :		CLR_BIT(TIMx_Num -> CCER , 1 )  ;			TIMx_Num -> CCER |= Copy_U8Polarity << 1  ;			error = ES_OK  ;		break ;
		
	/* CC2P */
		case PWM_CH2   :		CLR_BIT(TIMx_Num -> CCER , 5 ) ;			TIMx_Num -> CCER |= Copy_U8Polarity << 5  ;			error = ES_OK  ;		break ;

	/* CC3P */
		case PWM_CH3   :		CLR_BIT(TIMx_Num -> CCER , 9 ) ;			TIMx_Num -> CCER |= Copy_U8Polarity << 9  ;			error = ES_OK  ;		break ;

	/* CC4P */
		case PWM_CH4   :		CLR_BIT(TIMx_Num -> CCER , 13 ) ;			TIMx_Num -> CCER |= Copy_U8Polarity << 13  ;			error = ES_OK  ;		break ;


		default :  error = ES_OUT_RANGE ;	break ;
	}

	return error  ;
		
}




/***************************************************************************/
/***************************************************************************/
ErrorState	MPWM_EnuChannelCompareMode(MTIM_Typedef * TIMx_Num   , UTILS_PWM_CHANNEL Copy_U8Channel , UTILS_CHANNEL_COMPARE_MODE Copy_U8Mode)
{
	ErrorState error = ES_NOK ;
	
	switch (Copy_U8Channel)
	{
			/*  Set Channel Compare Mode OC2M */
		
		case PWM_CH1   :		TIMx_Num -> CCMR1  &= ~ ( 0b111 << 4 ) ;		TIMx_Num -> CCMR1  |=  ( Copy_U8Mode << 4 ) ;		error = ES_OK  ;		break ;
		
		case PWM_CH2   :		TIMx_Num -> CCMR1  &= ~ ( 0b111 << 12 ) ;		TIMx_Num -> CCMR1  |=  ( Copy_U8Mode << 12 ) ;		error = ES_OK  ;		break ;
		
		case PWM_CH3   :		TIMx_Num -> CCMR2  &= ~ ( 0b111 << 4 ) ;		TIMx_Num -> CCMR2  |=  ( Copy_U8Mode << 4 ) ;		error = ES_OK  ;		break ;
		
		case PWM_CH4   :		TIMx_Num -> CCMR2  &= ~ ( 0b111 << 12 ) ;		TIMx_Num -> CCMR2  |=  ( Copy_U8Mode << 12 ) ;		error = ES_OK  ;		break ;


		default :  error = ES_OUT_RANGE ;	break ;
	}

	return error  ;
		
}







/***************************************************************************/
/***************************************************************************/
ErrorState	MPWM_EnuChannelStatus(MTIM_Typedef * TIMx_Num   , UTILS_PWM_CHANNEL Copy_U8Channel , UTILS_STATUS  Copy_U8Status)
{
	ErrorState error = ES_NOK ;
	
	switch (Copy_U8Channel)
	{
			/*  Enable/Disable GPIO output  */
		
		case PWM_CH1   :		CLR_BIT(TIMx_Num -> CCER , 0 )  ;			TIMx_Num -> CCER |= Copy_U8Status << 0  ;			error = ES_OK  ;		break ;
		
		case PWM_CH2   :		CLR_BIT(TIMx_Num -> CCER , 4 )  ;			TIMx_Num -> CCER |= Copy_U8Status << 4  ;			error = ES_OK  ;		break ;
		
		case PWM_CH3   :		CLR_BIT(TIMx_Num -> CCER , 8 )  ;			TIMx_Num -> CCER |= Copy_U8Status << 8  ;			error = ES_OK  ;		break ;
		
		case PWM_CH4   :		CLR_BIT(TIMx_Num -> CCER , 12 )  ;			TIMx_Num -> CCER |= Copy_U8Status << 12  ;			error = ES_OK  ;		break ;


		default :  error = ES_OUT_RANGE ;	break ;
	}

	return error  ;
	
	
	
}






/***************************************************************************/
/***************************************************************************/
ErrorState	MPWM_EnuSetDutyCycle(MTIM_Typedef * TIMx_Num   ,  UTILS_PWM_CHANNEL Copy_U8Channel , u32 Copy_U32Percent)
{
	ErrorState error = ES_NOK  ;
	
	u32 Local_U32DutyCycleValue = ( Copy_U32Percent * ( (u32) TIMx_Num -> ARR ) ) / 100 ;
	
	switch (Copy_U8Channel)
	{
			/*  AutoReload Set Value */
		
		case PWM_CH1   :	TIMx_Num -> CCR1  =   Local_U32DutyCycleValue ; error = ES_OK  ;  break ;
		
		case PWM_CH2   :	TIMx_Num -> CCR2  =   Local_U32DutyCycleValue ; error = ES_OK  ;  break ;
		
		case PWM_CH3   :	TIMx_Num -> CCR3  =   Local_U32DutyCycleValue ; error = ES_OK  ;  break ;
		
		case PWM_CH4   :	TIMx_Num -> CCR4  =   Local_U32DutyCycleValue ; error = ES_OK  ;  break ;

		default :  error = ES_OUT_RANGE ;	break ;
	}

	return error ;
}







/***************************************************************************/
/***************************************************************************/
ErrorState	MPWM_EnuPulseFrequency(MTIM_Typedef * TIMx_Num   ,  u32 Copy_U32Frequency)
{
	/* Initialize AutoReload */
	TIMx_Num -> ARR  =  8000000 / ( ( ( u32 ) TIMx_Num -> PSC ) * Copy_U32Frequency  )  ;

	return ES_OK ;
}





