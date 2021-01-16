#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"



#include "MNVIC/MNVIC_Interface.h"
#include "MNVIC/MNVIC_Private.h"
#include "MNVIC/MNVIC_Config.h"












/********************************************************/
/********************************************************/
/********************************************************/
ErrorState	 MNVIC_EnuInit(void) 
{
	SCB -> AIRCR = IRQ_SUB_GROUP_DISTRIBUTION ;
	
	return ES_OK ;
}





/********************************************************/
/********************************************************/
/********************************************************/
ErrorState 	MNVIC_EnuEnableIRQ(u8 Copy_U8INTID)
{
	
	MNVIC -> ISER[ Copy_U8INTID/32 ]  |= ( 1 << ( Copy_U8INTID % 32 ) )  ;
	
	return ES_OK ;
	
}




/********************************************************/
/********************************************************/
/********************************************************/
ErrorState 	MNVIC_EnuDisableIRQ(u8 Copy_U8INTID)
{
	
	MNVIC -> ICER[ Copy_U8INTID/32 ]  &= ~( 1 << ( Copy_U8INTID % 32 ) )  ;
	
	return ES_OK ;
	
}








/********************************************************/
/********************************************************/
/********************************************************/
ErrorState 	MNVIC_EnuSetPendingIRQ(u8 Copy_U8INTID)
{
	
	MNVIC -> ISPR[ Copy_U8INTID/32 ]  |= ( 1 << ( Copy_U8INTID % 32 ) )  ;
	
	return ES_OK ;
	
}




/********************************************************/
/********************************************************/
/********************************************************/
ErrorState	 MNVIC_EnuClearPendingIRQ(u8 Copy_U8INTID)
{

	MNVIC -> ICPR[ Copy_U8INTID/32 ]  &= ~( 1 << ( Copy_U8INTID % 32 ) )  ;
	
	return ES_OK ;
	
}







/********************************************************/
/********************************************************/
/********************************************************/
ErrorState	 MNVIC_EnuGetIRQActiveFlag( u8 Copy_U8INTID , u8 * Copy_PU8ActiveFlagValue ) 
{
	
	* Copy_PU8ActiveFlagValue = GET_BIT( MNVIC -> IABR[ Copy_U8INTID/32 ] , ( Copy_U8INTID % 32 ) ) ;
	
	return ES_OK ;
	
}











/********************************************************/
/********************************************************/
/********************************************************/
ErrorState 	MNVIC_EnuSetIRQPriority( s8 Copy_U8INTID ,u8 Copy_U8GroupPriority , u8 Copy_U8SubPriority)
{
	// GROUP_SUB_STEP = 0 : 4  --->  0 BIT_GROUP TO 4 BIT_GROUP
	u8 Local_U8PriorityValue  = ( Copy_U8SubPriority | (Copy_U8GroupPriority << GROUP_SUB_STEP )) << 4  ;
	
	if (Copy_U8INTID >= 0)
	{
		MNVIC -> IPR[Copy_U8INTID] =  Local_U8PriorityValue ;
		
	}
	else 
	{
		Copy_U8INTID=  -Copy_U8INTID - 4 ;
		
		SCB -> SHPR[Copy_U8INTID/4] = Local_U8PriorityValue ;
	
	}
	
	
	return ES_OK ;
}























