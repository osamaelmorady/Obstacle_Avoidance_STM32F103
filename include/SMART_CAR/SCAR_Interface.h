#ifndef		_SCAR_INTERFACE_H_
#define 	_SCAR_INTERFACE_H_


#include "LIB/ERROR_STATE.h"






/******************************************************/
/******************************************************/
ErrorState SCAR_EnuInit(void);


/******************************************************/
/******************************************************/
ErrorState SCAR_EnuSoftStart(void) ;



/******************************************************/
/******************************************************/
ErrorState SCAR_EnuSoftStop(void);




/******************************************************/
/******************************************************/
ErrorState SCAR_EnuMoveForward(u8 Copy_U8SpeedPercent);




/******************************************************/
/******************************************************/
ErrorState SCAR_EnuMoveBackWard(u8 Copy_U8SpeedPercent);




/******************************************************/
/******************************************************/
ErrorState SCAR_EnuTurnLeft(u8 Copy_U8SpeedPercent);




/******************************************************/
/******************************************************/
ErrorState SCAR_EnuTurnRight(u8 Copy_U8SpeedPercent);




/******************************************************/
/******************************************************/
ErrorState SCAR_EnuStop() ;




/******************************************************/
/******************************************************/
ErrorState SCAR_EnuAllLightOff(void) ;







#endif