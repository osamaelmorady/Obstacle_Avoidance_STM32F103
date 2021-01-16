#ifndef		_ERROR_STATE_H_
#define 	_ERROR_STATE_H_





typedef enum	ERROR_STATE
{
	/* Check for not met condition  */
	ES_NOK=0			 ,


	/* Check for met condition  */
	ES_OK=1				 ,


	/* Check for overflow condition  */
	ES_OV=2				 ,


	/* Check for entered parameter is out of range condition  */
	ES_OUT_RANGE=2

}ErrorState 	;














#endif
/* _ERROR_STATE_H_ */
