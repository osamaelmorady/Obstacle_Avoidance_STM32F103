#ifndef		_MNVIC_PRIVATE_H_
#define 	_MNVIC_PRIVATE_H_




typedef struct 
{
	volatile u32 ISER[32] ;
	volatile u32 ICER[32] ;
	volatile u32 ISPR[32] ;
	volatile u32 ICPR[32] ;
	
	volatile u32 IABR[32] ;
	volatile u32 RESERVED ;
	
	volatile u8 IPR[128] ;	
	
}MNVIC_TYPE ;



#define MNVIC  ( (volatile MNVIC_TYPE * ) 0xE000E100)

#define MNVIC_STIR  ( (volatile u32 * ) 0xE000EF00)









typedef struct 
{
	volatile u32	CPUID	;
	volatile u32	ICSR	;
	volatile u32	VTOR	;
	volatile u32	AIRCR	;
	volatile u32	SCR		;

	volatile u32	CCR		;
	volatile u32	SHPR[3]	;

	volatile u32	SHCRS	;
	volatile u32	CFSR	;
	volatile u32	HFSR	;
	
	volatile u32	RESERVED ;
	volatile u32	MMAR	;
	volatile u32	BFAR	;
	


}SCB_TYPE ;


#define SCB  ( (volatile SCB_TYPE * )  0xE000ED00)





/*  IRG_SUB_GROUP_DISTRIBUTION  */
/********************************/
#define GROUPS_4_SUB_0			0X5FA00300
#define GROUPS_3_SUB_1			0X5FA00400
#define GROUPS_2_SUB_2			0X5FA00500
#define GROUPS_1_SUB_3			0X5FA00600
#define GROUPS_0_SUB_4			0X5FA00700

#define GROUP_SUB_STEP   ( ( IRQ_SUB_GROUP_DISTRIBUTION - GROUPS_4_SUB_0 ) / 256 )











#endif
