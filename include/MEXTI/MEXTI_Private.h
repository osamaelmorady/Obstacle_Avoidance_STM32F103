#ifndef		_MEXTI_PRIVATE_H_
#define 	_MEXTI_PRIVATE_H_





typedef struct 
{
	volatile u32 IMR ;
	volatile u32 EMR ;
	volatile u32 RTSR ;
	volatile u32 FTSR ;
	volatile u32 SWIER ;
	volatile u32 PR ;
	
	
}MEXTI_TYPE ;







#define	 MEXTI  ((volatile MEXTI_TYPE *) 0x40010400 )

















#endif