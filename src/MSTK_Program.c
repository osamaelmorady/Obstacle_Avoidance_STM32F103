#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"


#include "MSTK/MSTK_Interface.h"
#include "MSTK/MSTK_Private.h"
#include "MSTK/MSTK_Config.h"


u32 tick_counter;


/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  MSTK_EnuTimerInit(void) 
{
	/* Disable SysTick ,, Disable INT ,, CLK source = User_defined   */
	MSTK -> CTRL = MSTK_CLKSOURCE     ;
	
	/* Reset Preload Value to 0 ,, Reset Flag to 0 */
	MSTK -> VAL = 0 ;
	
	return ES_OK ;
}






/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  MSTK_EnuBusyDelay(u32 Copy_U32TimePeriod) 
{
	MSTK -> LOAD = Copy_U32TimePeriod -1 ;
	
	SET_BIT( MSTK -> CTRL , 0) ;
	
	while( !GET_BIT( MSTK -> CTRL , 16 )  );
	
	
	MSTK -> CTRL = MSTK_CLKSOURCE ;
	MSTK -> VAL  = 0 ;
	MSTK -> LOAD = 0 ;
	
	
	return ES_OK ;
}






/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  MSTK_EnuStopTimer( void )
{
	MSTK -> CTRL = MSTK_CLKSOURCE ;
	MSTK -> VAL  = 0 ;
	MSTK -> LOAD = 0 ;
	
	return ES_OK ;
}




/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  MSTK_EnuGetElapsedTime( u32 * Copy_PU32TimerElapsedValue )
{
	* Copy_PU32TimerElapsedValue =  ( MSTK -> LOAD ) - ( MSTK -> VAL ) ;
	
	return ES_OK ;
}




/****************************************************************************************************/
/****************************************************************************************************/
ErrorState  MSTK_EnuGetRemainingTime( u32 * Copy_PU32TimerRemainingValue ) 
{
	
	* Copy_PU32TimerRemainingValue =  MSTK -> VAL ;
	
	return ES_OK ;
}










/****************************************************************************************************/
/****************************************************************************************************/
#define NULL '\0'
static void (*FUN_PTR)(void) = NULL ;

static  u8  MSTK_U32HelperVal = 1 ;
/****************************************************************************************************/
/****************************************************************************************************/

ErrorState 	MSTK_EnuSingleInterval   ( u32 Copy_U32TimePeriod , void ( *Copy_PFun )( void ) )
{
	/* Reset And Load */
	CLR_BIT( MSTK -> CTRL , 0) ;
	MSTK -> VAL = 0            ;
	MSTK -> LOAD = Copy_U32TimePeriod  ;
	
	/*Start the Timer*/
	SET_BIT( MSTK -> CTRL , 0) ;
	SET_BIT( MSTK -> CTRL , 1) ;
	
	FUN_PTR = Copy_PFun ;
	
	MSTK_U32HelperVal = MSTK_SINGLE_INTERVAL ;
	
	return ES_OK ;
}







ErrorState 	MSTK_EnuPeriodicInterval ( u32 Copy_U32TimePeriod , void ( *Copy_PFun )( void ) )
{
	/* Reset And Load */
	CLR_BIT( MSTK -> CTRL , 0) ;
	MSTK -> VAL = 0            ;
	MSTK -> LOAD = Copy_U32TimePeriod  ;
	
	/*Start the Timer*/
	SET_BIT( MSTK -> CTRL , 0) ;
	SET_BIT( MSTK -> CTRL , 1) ;
	
	FUN_PTR = Copy_PFun ;
	
	MSTK_U32HelperVal = MSTK_PERIODIC_INTERVAL ;
	
	return ES_OK ;
} 






void SysTick_Handler(void) 
{
	/*To Clear the CountFlag ,Read The Flag_Bit */
	u8 LOC_u8ReadFlag = GET_BIT( MSTK -> CTRL , 16 )	;
	
	if ( MSTK_U32HelperVal == MSTK_SINGLE_INTERVAL )
	{
		MSTK -> CTRL = MSTK_CLKSOURCE ;
		MSTK -> VAL  = 0 ;
		MSTK -> LOAD = 0 ;		
	}

	 tick_counter++ ;
	
	FUN_PTR() ;
		
		
}







