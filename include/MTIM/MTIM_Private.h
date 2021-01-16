#ifndef		_MTIM_PRIVATE_H_
#define 	_MTIM_PRIVATE_H_




typedef struct 
{
	volatile u16 CR1 ;
	volatile u16 RESERVED0 ;

	volatile u16 CR2 ;
	volatile u16 RESERVED1 ;

	volatile u16 SMCR ;
	volatile u16 RESERVED2 ;
	
	volatile u16 DIER ;
	volatile u16 RESERVED3 ;

	volatile u16 SR ;
	volatile u16 RESERVED4 ;

	volatile u16 EGR ;
	volatile u16 RESERVED5 ;
	
	volatile u16 CCMR1 ;
	volatile u16 RESERVED6 ;

	volatile u16 CCMR2 ;
	volatile u16 RESERVED7 ;

	volatile u16 CCER ;
	volatile u16 RESERVED8 ;

	
	volatile u16 CNT ;
	volatile u16 RESERVED9 ;

	volatile u16 PSC ;
	volatile u16 RESERVED10 ;

	volatile u16 ARR ;
	volatile u16 RESERVED11 ;

	volatile u16 RCR ;
	volatile u16 RESERVED12 ;

	volatile u16 CCR1 ;
	volatile u16 RESERVED13 ;

	volatile u16 CCR2 ;
	volatile u16 RESERVED14 ;

	volatile u16 CCR3 ;
	volatile u16 RESERVED15 ;

	volatile u16 CCR4 ;
	volatile u16 RESERVED16 ;

	volatile u16 BDTR ;
	volatile u16 RESERVED17 ;

	volatile u16 DCR ;
	volatile u16 RESERVED18 ;

	volatile u16 DMAR ;
	volatile u16 RESERVED19 ;
	
}MTIM_Typedef ;


#define   MTIM1		(( MTIM_Typedef *) 0x40012C00 )
#define   MTIM2		(( MTIM_Typedef *) 0x40000000 )
#define   MTIM3		(( MTIM_Typedef *) 0x40000400 )
#define   MTIM4		(( MTIM_Typedef *) 0x40000800 )
//#define   MTIM5		(( MTIM_Typedef *) 0x40000C00 )
//#define   MTIM6		(( MTIM_Typedef *) 0x40001000 )
//#define   MTIM7		(( MTIM_Typedef *) 0x40001400 )






#define TIM_INTERVAL_SINGLE			0
#define TIM_INTERVAL_CONTINOUS			1






/**********************************************************/
/**********************************************************/
/***********		CCR1    *************/
#define 	CEN		0
#define 	UDIS	1
#define 	URS		2
#define 	OPM		3
#define 	DIR		4
#define 	ARRE	7

/***********		DIER    *************/
#define 	UIE		0


/***********		EGR    *************/
#define 	UG		0


/***********		SR    *************/
#define 	UIF		0















#endif
