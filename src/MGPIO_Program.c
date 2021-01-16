#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"

#include "MGPIO/MGPIO_Interface.h"
#include "MGPIO/MGPIO_Private.h"
#include "MGPIO/MGPIO_Config.h"







/*************************************************************************/
/*************************	Pin Direction 	*******************************/
/*************************************************************************/
ErrorState 	MGPIO_EnuSetPinDir(u8 Copy_U8PinNumber,u8 Copy_U8PinMode) 
{	
	u8 Local_U8PortNum = Copy_U8PinNumber/PINS_NUM_IN_PORT  ;

	Copy_U8PinNumber%=PINS_NUM_IN_PORT ;

	
	switch (Local_U8PortNum)
	{
		case MGPIO_PORTA :
		
			/* Check for pin0 - pin7  in PORTA */
			if ( (Copy_U8PinNumber) < CRL_SEQ_NUM )
			{
				/* clear the 4 bits for MODE & CFD */
				MGPIOA -> CRL &= ~( 0b1111        <<(Copy_U8PinNumber*4)) ;
				/* Set the 4 bits for MODE & CFD */
				MGPIOA -> CRL |=  ( ( Copy_U8PinMode & 0b1111 ) <<(Copy_U8PinNumber*4)) ;
		
			}
			/* Check for pin8 - pin15  in PORTA */
			else if ( (Copy_U8PinNumber) >= CRL_SEQ_NUM )
			{
				Copy_U8PinNumber -=CRL_SEQ_NUM ;
				MGPIOA -> CRH &= ~( 0b1111        <<(Copy_U8PinNumber*4)) ;
				MGPIOA -> CRH |=  (( Copy_U8PinMode & 0b1111 ) <<(Copy_U8PinNumber*4)) ;
				
			}
		break ;
			
			
		case MGPIO_PORTB :
			/* Check for pin0 - pin7  in PORTB */
			if ( (Copy_U8PinNumber) < CRL_SEQ_NUM )
			{
				MGPIOB -> CRL &= ~( 0b1111        <<(Copy_U8PinNumber*4)) ;
				MGPIOB -> CRL |=  (( Copy_U8PinMode & 0b1111 ) <<(Copy_U8PinNumber*4)) ;
		
			}
			/* Check for pin8 - pin15  in PORTB */
			else if ( (Copy_U8PinNumber) >= CRL_SEQ_NUM )
			{
				Copy_U8PinNumber -=CRL_SEQ_NUM ;
				MGPIOB -> CRH &= ~( 0b1111        <<(Copy_U8PinNumber*4)) ;
				MGPIOB -> CRH |=  (( Copy_U8PinMode & 0b1111 ) <<(Copy_U8PinNumber*4)) ;
				
			}
		break ;
		
		
		case MGPIO_PORTC :
			
			/* Check for pin0 - pin7  in PORTC */
			if ( (Copy_U8PinNumber) < CRL_SEQ_NUM )
			{
				MGPIOC -> CRL &= ~( 0b1111        <<(Copy_U8PinNumber*4)) ;
				MGPIOC -> CRL |=  (( Copy_U8PinMode & 0b1111 ) <<(Copy_U8PinNumber*4)) ;
		
			}
			/* Check for pin8 - pin15  in PORTC */
			else if ( (Copy_U8PinNumber) >= CRL_SEQ_NUM )
			{
				Copy_U8PinNumber -=CRL_SEQ_NUM ;
				MGPIOC -> CRH &= ~( 0b1111        <<(Copy_U8PinNumber*4)) ;
				MGPIOC -> CRH |=  (( Copy_U8PinMode & 0b1111 ) <<(Copy_U8PinNumber*4)) ;
				
			}
		break ;
		
		default : 
			
			 return ES_OUT_RANGE ;
			
		break ;
			
		
	}
	
	if ( Copy_U8PinMode ==  INPUT_PULL_UP )
	{
		MGPIO_EnuSetPinVal( Copy_U8PinNumber , MGPIO_HIGH_LEVEL )  ;
	}
	else if ( Copy_U8PinMode == INPUT_PULL_DOWN )
	{
		MGPIO_EnuSetPinVal( Copy_U8PinNumber , MGPIO_LOW_LEVEL )  ;
	}
	
	
	return ES_OK ;
}






/*************************************************************************/
/*************************	Pin Value 	*******************************/
/*************************************************************************/
ErrorState 	MGPIO_EnuSetPinVal(u8 Copy_U8PinNumber,u8 Copy_U8PinValue) 
{
	u8 Local_U8PortNum = Copy_U8PinNumber/PINS_NUM_IN_PORT  ;

	Copy_U8PinNumber%=PINS_NUM_IN_PORT ;

#if GPIO_ACCESS_MODE_SELECTION == ATOMIC_ACCESS_DISABLED
	
	switch (Local_U8PortNum)
	{
		case MGPIO_PORTA :
		
			if (Copy_U8PinValue==MGPIO_LOW_LEVEL)
				
				CLR_BIT(MGPIOA -> ODR ,Copy_U8PinNumber) ;
			
			else if (Copy_U8PinValue==MGPIO_HIGH_LEVEL)
				
				SET_BIT(MGPIOA -> ODR ,Copy_U8PinNumber) ;
		
		break ;
		
		
		case MGPIO_PORTB :
		
			if (Copy_U8PinValue==MGPIO_LOW_LEVEL)
				
				CLR_BIT(MGPIOB -> ODR ,Copy_U8PinNumber) ;
			
			else if (Copy_U8PinValue==MGPIO_HIGH_LEVEL)
				
				SET_BIT(MGPIOB -> ODR ,Copy_U8PinNumber) ;
		
		break ;
		
		
		case MGPIO_PORTC :
			
			if (Copy_U8PinValue==MGPIO_LOW_LEVEL)
				
				SET_BIT(MGPIOC -> ODR ,Copy_U8PinNumber) ;
			
			else if (Copy_U8PinValue==MGPIO_HIGH_LEVEL)
				
				CLR_BIT(MGPIOC -> ODR ,Copy_U8PinNumber) ;
			
		break ;
		
	}


#elif GPIO_ACCESS_MODE_SELECTION == ATOMIC_ACCESS_ENABLED

	switch (Local_U8PortNum)
	{
		case MGPIO_PORTA :
		
			if (Copy_U8PinValue==MGPIO_LOW_LEVEL)
				
				MGPIOA -> BRR = 1<<Copy_U8PinNumber ;
			
			else if (Copy_U8PinValue==MGPIO_HIGH_LEVEL)
				
				MGPIOA -> BSRR = 1<<Copy_U8PinNumber ;
		
		break ;
		
		
		case MGPIO_PORTB :
		
			if (Copy_U8PinValue==MGPIO_LOW_LEVEL)
				
				MGPIOB -> BRR = 1<<Copy_U8PinNumber ;
			
			else if (Copy_U8PinValue==MGPIO_HIGH_LEVEL)
				
				MGPIOB -> BSRR = 1<<Copy_U8PinNumber ;
		
		break ;
		
		
		case MGPIO_PORTC :
			
			if (Copy_U8PinValue==MGPIO_LOW_LEVEL)
				
				MGPIOC -> BSRR = 1<<Copy_U8PinNumber ;
			
			else if (Copy_U8PinValue==MGPIO_HIGH_LEVEL)
				
				MGPIOC -> BRR = 1<<Copy_U8PinNumber ;
			
		break ;
		
	}
	
#else 
	#error "Attention, Wrong GPIO_ACCESS_MODE_SELECTION !!"
#endif
	
	return ES_OK ;
}






/*************************************************************************/
/*************************	Pin Value 	*******************************/
/*************************************************************************/
ErrorState 	MGPIO_EnuGetPinVal(u8 Copy_U8PinNumber,u8 * Copy_PU8PinValue) 
{
	u8 Local_U8PortNum = Copy_U8PinNumber/PINS_NUM_IN_PORT  ;

	Copy_U8PinNumber%=PINS_NUM_IN_PORT ;
	
	switch (Local_U8PortNum)
	{
		case MGPIO_PORTA :
	
			* Copy_PU8PinValue = GET_BIT(MGPIOA -> IDR , Copy_U8PinNumber) ;
		
		break ;
		
		case MGPIO_PORTB :
		
			* Copy_PU8PinValue = GET_BIT(MGPIOB -> IDR , Copy_U8PinNumber) ;
		
		break ;
		
		case MGPIO_PORTC :
	
			* Copy_PU8PinValue = GET_BIT(MGPIOC -> IDR , Copy_U8PinNumber) ;
	
		break ;
	
	}
	
	return ES_OK ;
}





/*************************************************************************/
/*************************	Toggle Pin 	*******************************/
/*************************************************************************/
ErrorState 	MGPIO_EnuTogglePinVal(u8 Copy_U8PinNumber) 
{
	u8 Local_U8PortNum = Copy_U8PinNumber/PINS_NUM_IN_PORT  ;

	Copy_U8PinNumber%=PINS_NUM_IN_PORT ;
	
	switch (Local_U8PortNum)
	{
		case MGPIO_PORTA :	TOGGLE_BIT(MGPIOA -> ODR ,Copy_U8PinNumber) ;		break ;
		
		case MGPIO_PORTB :	TOGGLE_BIT(MGPIOB -> ODR ,Copy_U8PinNumber) ;		break ;
		
		case MGPIO_PORTC : 	TOGGLE_BIT(MGPIOC -> ODR ,Copy_U8PinNumber) ; 		break ;
		
	}

	return ES_OK ;
	
}





















