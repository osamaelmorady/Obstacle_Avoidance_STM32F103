#ifndef 	_MGPIO_PRIVATE_H_
#define 	_MGPIO_PRIVATE_H_



typedef struct 
{
	volatile u32 CRL ;
	volatile u32 CRH ;
	volatile u32 IDR ;
	volatile u32 ODR ;
	volatile u32 BSRR ;
	volatile u32 BRR ;
	volatile u32 LCKR ;
		
} MGPIO_TYPE ;



#define MGPIOA  ((volatile MGPIO_TYPE *) 0x40010800 )
#define MGPIOB  ((volatile MGPIO_TYPE *) 0x40010C00 )
#define MGPIOC  ((volatile MGPIO_TYPE *) 0x40011000 )





#define MGPIO_PORTA   0 
#define MGPIO_PORTB   1
#define MGPIO_PORTC   2



#define PIN_SEQUENCED_BITS	0b1111

#define CRL_SEQ_NUM			8

#define PINS_NUM_IN_PORT	16




#define MGPIO_LOW_LEVEL			0
#define MGPIO_HIGH_LEVEL		1






#define ATOMIC_ACCESS_DISABLED	0
#define ATOMIC_ACCESS_ENABLED	1





#endif
