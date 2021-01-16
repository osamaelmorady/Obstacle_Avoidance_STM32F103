#ifndef		_MSTK_INTERFACE_H_
#define		_MSTK_INTERFACE_H_



#include "LIB/ERROR_STATE.h"






ErrorState  MSTK_EnuTimerInit(void) ;





ErrorState  MSTK_EnuBusyDelay(u32 Copy_U32TimePeriod) ;




ErrorState  MSTK_EnuStopTimer( void ) ;





ErrorState  MSTK_EnuGetElapsedTime( u32 * Copy_PU32TimerElapsedValue ) ;



ErrorState  MSTK_EnuGetRemainingTime( u32 * Copy_PU32TimerRemainingValue ) ;







ErrorState 	MSTK_EnuSingleInterval   ( u32 Copy_U32TimePeriod , void ( *Copy_PFun )( void ) ); 




ErrorState 	MSTK_EnuPeriodicInterval ( u32 Copy_U32TimePeriod , void ( *Copy_PFun )( void ) );         





#endif