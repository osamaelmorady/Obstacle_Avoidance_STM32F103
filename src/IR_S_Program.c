
#include "LIB/DELAY.h"
#include "LIB/STD_TYPES.h"
#include "LIB/ERROR_STATE.h"

#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"
#include "MTIM/MTIM_Interface.h"

#include "IR_S/IR_S_Config.h"
#include "IR_S/IR_S_Interface.h"


#include "MNVIC/MNVIC_Interface.h"
#include "MEXTI/MEXTI_Interface.h"




/******************************************************************************/
ErrorState IR_S_EnuInit(void)
{
	MRCC_EnuEnablePeriphClock(MRCC_GPIO) ;

	MGPIO_EnuSetPinDir(IR_S_PIN , INPUT_PULL_UP)  ;

	return ES_OK ;

}



ErrorState IR_S_EnuGetStatus(u8 * Copy_PU8IRStatus)
{
	* Copy_PU8IRStatus = 0 ;

	MGPIO_EnuGetPinVal(IR_S_PIN, Copy_PU8IRStatus ) ;

	_delay_ms(1)  ;

	MGPIO_EnuGetPinVal(IR_S_PIN, Copy_PU8IRStatus ) ;

	return ES_OK ;

}




/******************************************************************************/
ErrorState IR_S_EnuSetCallBack(void (*PFun)(void))
{
	MRCC_EnuEnablePeriphClock(MRCC_GPIO) ;
	MRCC_EnuEnablePeriphClock(MRCC_AFIO)  ;

	MNVIC_EnuInit() ;
	MNVIC_EnuEnableIRQ(MNVIC_EXTI8_INT) ;

	MGPIO_EnuSetPinDir(PIN_A8,INPUT_PULL_DOWN) ;


	MEXTI_EnuInit(MEXTI_CH8,MEXTI_TRIGGER_FALLING) ;
	MEXTI_EnuSetCallBack(MEXTI_CH8,PFun) ;
	MEXTI_EnuChannelEnable(MEXTI_CH8) ;


	return ES_OK ;

}




