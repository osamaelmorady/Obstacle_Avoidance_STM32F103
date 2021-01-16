#ifndef 	_MGPIO_INTERFACE_H_
#define 	_MGPIO_INTERFACE_H_


#include "LIB/ERROR_STATE.h"



typedef enum 
{
	PIN_A0=0, PIN_A1  , PIN_A2  , PIN_A3  , PIN_A4  , PIN_A5  , PIN_A6  , PIN_A7  ,
	PIN_A8  , PIN_A9  , PIN_A10 , PIN_A11 , PIN_A12 , PIN_A13 , PIN_A14 , PIN_A15 ,
	PIN_B0=16 , PIN_B1 , PIN_B2 , PIN_B3 , PIN_B4 , PIN_B5 , PIN_B6 , PIN_B7 ,
	PIN_B8 , PIN_B9 , PIN_B10 , PIN_B11 , PIN_B12 , PIN_B13 , PIN_B14 , PIN_B15 ,
	PIN_C13=45 , PIN_C14 , PIN_C15 ,
	
	LOW=0 , HIGH
	
}GPIO_PIN_NUM ;



typedef enum
{
	/* INPUT_PULL_UP, INPUT_PULL_DOWN   5th  bit for up or down */
	INPUT_ANALOG=0b0000 , INPUT_FLOAT=0b0100 , INPUT_PULL_UP=0b01000 , INPUT_PULL_DOWN = 0b11000 ,
	
	OUTPUT_2MHZ_PP=0b0010  , OUTPUT_2MHZ_DRAIN=0b0110  ,  OUTPUT_2MHZ_PP_AF=0b1010  , OUTPUT_2MHZ_DRAIN_AF=0b1110  , 
	
	OUTPUT_10MHZ_PP=0b0001 , OUTPUT_10MHZ_DRAIN=0b0101 ,  OUTPUT_10MHZ_PP_AF=0b1001 , OUTPUT_10MHZ_DRAIN_AF=0b1101 ,
	
	OUTPUT_50MHZ_PP=0b0011 , OUTPUT_50MHZ_DRAIN=0b0111 ,  OUTPUT_50MHZ_PP_AF=0b1011 , OUTPUT_50MHZ_DRAIN_AF=0b1111
	
}MGPIO_MODES ;






/*************************************************************************/
/*************************	Pin Direction 	*******************************/
/*************************************************************************/
ErrorState 	MGPIO_EnuSetPinDir(u8 Copy_U8PinNumber,u8 Copy_U8PinMode) ;






/*************************************************************************/
/*************************	Pin Value 	*******************************/
/*************************************************************************/
ErrorState 	MGPIO_EnuSetPinVal(u8 Copy_U8PinNumber,u8 Copy_U8PinValue) ;






/*************************************************************************/
/*************************	Pin Value 	*******************************/
/*************************************************************************/
ErrorState 	MGPIO_EnuGetPinVal(u8 Copy_U8PinNumber,u8 * Copy_PU8PinValue) ;





/*************************************************************************/
/*************************	Toggle Pin 	*******************************/
/*************************************************************************/
ErrorState 	MGPIO_EnuTogglePinVal(u8 Copy_U8PinNumber) ;






#endif
