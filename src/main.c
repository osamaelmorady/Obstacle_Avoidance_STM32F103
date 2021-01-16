/*
 * main.c
 *
 *  Created on: Jan 12, 2021
 *      Author: Osama Elmorady
 */
#include "LIB/STD_TYPES.h"
#include "LIB/DELAY.h"

#include "MRCC/MRCC_Interface.h"
#include "MSTK/MSTK_Interface.h"
#include "STMU/STMU_interface.h"
#include "MGPIO/MGPIO_Interface.h"

#include "RGB_LED/RGB_Interface.h"
#include "DC_Motors/MOT_DC_Interface.h"

#include "BUZ/BUZ_Interface.h"
#include "IR_S/IR_S_Interface.h"

#include "SMART_CAR/SCAR_Interface.h"


void Check_IR_S(void) ;
void IR_S_action(void) ;
void UpWard (void) ;
void DownWard (void) ;
void Left (void) ;
void Right (void) ;
void Stop (void) ;

void Line(void) ;
void circle(void);
void Triangle(void) ;
void Rectangle(void);







u8 IR_S_Status  = 1  ;
u8 i=0 ;


task_t task1 = {IR_S_action , 1} ;
task_t task2 = {Check_IR_S , 1} ;








/*******************************************************************/
/*******************************************************************/

int main (void)
{
MRCC_InitSysClk() ;
MRCC_EnuEnablePeriphClock(MRCC_GPIO) ;
BUZ_EnuInit() ;
IR_S_EnuInit() ;
RGB_EnuInit() ;
SCAR_EnuInit() ;



STMU_voidInit() ;
STMU_voidAddTask(task1) ;
STMU_voidAddTask(task2) ;
STMU_voidStartScheduler(50) ;



SCAR_EnuAllLightOff() ;
RGB_EnuLightStatus(PIN_A5,COLOR_GREEN,STATUS_ON)  ;
RGB_EnuLightStatus(PIN_A4,COLOR_GREEN,STATUS_ON)  ;
_delay_ms(2500) ;

UpWard() ;
_delay_ms(1000) ;

DownWard () ;
_delay_ms(800)  ;



while(1)
{
	Rectangle() ;

	circle() ;

	Line() ;

	Triangle() ;

}
return 0 ;
}








void Check_IR_S(void)
{
	IR_S_EnuGetStatus(&IR_S_Status) ;
}



void IR_S_action(void)
{
	if (IR_S_Status==0)
	{
		BUZ_EnuStatus(STATUS_ON) ;
		SCAR_EnuStop() ;
		SCAR_EnuAllLightOff() ;

		DownWard() ;
		_delay_ms(20) ;

		Left () ;
		_delay_ms(20) ;

	}
	else if  (IR_S_Status==1)
	{
		BUZ_EnuStatus(STATUS_OFF) ;

	}

}


void UpWard (void)
{


	SCAR_EnuAllLightOff() ;
	SCAR_EnuMoveForward(100) ;

}
void DownWard (void)
{
		SCAR_EnuAllLightOff() ;
		SCAR_EnuMoveBackWard(100) ;
}
void Left (void)
{

	SCAR_EnuAllLightOff() ;
	SCAR_EnuTurnLeft(100)  ;

}

void Right (void)
{

	SCAR_EnuAllLightOff() ;
	SCAR_EnuTurnRight(100)  ;

}


void Stop (void)
{

	SCAR_EnuAllLightOff() ;
	SCAR_EnuStop() ;

}




void circle(void)
{
	i=0 ;

	while(i<15)
	{
		UpWard () ;
		_delay_ms(200) ;
		Left () ;
		_delay_ms(300) ;

		i++ ;
	}

}


void Triangle(void)
{
	i=0 ;

	while(i<3)
	{
		UpWard () ;
		_delay_ms(2000) ;
		Left () ;
		_delay_ms(1800) ;

		i++ ;
	}

}


void Rectangle(void)
{
	i=0 ;

	while(i<1)
	{


		UpWard () ;
		_delay_ms(2000) ;
		Left () ;
		_delay_ms(1300) ;

		Right () ;
		_delay_ms(1300) ;

		DownWard () ;
		_delay_ms(2000) ;

		Right () ;
		_delay_ms(1300) ;

		UpWard () ;
		_delay_ms(2000) ;




		i++ ;
	}

}


void Line(void)
{
	i=0 ;

	while(i<2)
	{
		UpWard () ;
		_delay_ms(1000) ;
		DownWard () ;
		_delay_ms(1000) ;

		i++ ;
	}

}
