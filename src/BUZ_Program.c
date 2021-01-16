
#include "LIB/STD_TYPES.h"
#include "LIB/ERROR_STATE.h"

#include "MRCC/MRCC_Interface.h"
#include "MGPIO/MGPIO_Interface.h"
#include "MTIM/MTIM_Interface.h"


#include "BUZ/BUZ_Config.h"
#include "BUZ/BUZ_Interface.h"




/******************************************************************************/
ErrorState BUZ_EnuInit(void)
{
	MRCC_EnuEnablePeriphClock(MRCC_GPIO)  ;

	MGPIO_EnuSetPinDir(BUZZER_PIN,OUTPUT_10MHZ_PP) ;

	return ES_OK ;

}




/******************************************************************************/
ErrorState BUZ_EnuStatus(UTILS_STATUS Copy_Status)
{
	MGPIO_EnuSetPinVal(BUZZER_PIN,Copy_Status)  ;

	return ES_OK ;

}











