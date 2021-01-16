#ifndef		_MSTK_PRIVATE_H_
#define		_MSTK_PRIVATE_H_



typedef struct
{
	volatile u32 CTRL ;
	volatile u32 LOAD ;
	volatile u32 VAL ;
	volatile u32 CALIB ;
	
} STK_TYPE ;




#define  MSTK  ( (volatile STK_TYPE *) 0xE000E010 )




#define MSTK_CLKSOURCE_AHB_8	0x00000000
#define MSTK_CLKSOURCE_AHB		0x00000004



#define MSTK_SINGLE_INTERVAL       0
#define MSTK_PERIODIC_INTERVAL     1













#endif