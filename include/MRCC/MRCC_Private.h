
#ifndef		_MRCC_PRIVATE_H_
#define 	_MRCC_PRIVATE_H_


/******************/
/* MRCC Registers */
/******************/
typedef struct
{
	volatile	u32	  CR	;		//0x40021000
	volatile	u32	  CFGR	;       //0x40021004
	volatile	u32	  CIR	;       //0x40021008
	volatile	u32	  APB2RSTR	;   //0x4002100C
	volatile	u32	  APB1RSTR	;   //0x40021010
	volatile	u32	  AHBENR	;   //0x40021014
	volatile	u32	  APB2ENR	;   //0x40021018
	volatile	u32	  APB1ENR	;   //0x4002101C
	volatile	u32	  BDCR	;       //0x40021020
	volatile	u32	  CSR	;       //0x40021024

}MRCC_TYPE	;



/* MRCC Base Address on Memory Mapped System */
#define MRCC	((volatile MRCC_TYPE *) 0x40021000 )




/***************************************************************************/
/*****************************	MRCC_BITS	********************************/
/***************************************************************************/
#define CR_HSION	0
#define CR_HSIRDY	1

#define CR_HSEON	16
#define CR_HSERDY	17

#define CR_PLLON	24
#define CR_PLLRDY	25

#define CR_CSSON		19


#define CFGR_PLLSRC		16
#define CFGR_PLLXTPRE	17




#define GPIOA_BIT	2
#define GPIOG_BIT	8
#define GPIO_BITS	0b1111111








/***************************************************************************/
/************************	MRCC_CLOCK_TYPE	****************************/
/***************************************************************************/
#define MRCC_HSE_CRYSTAL 0
#define MRCC_HSE_RC		 1
#define MRCC_HSI         2
#define MRCC_PLL		 3





/***************************************************************************/
/*************************	MRCC_PLL_INPUT		****************************/
/***************************************************************************/
#define MRCC_PLL_HSI_2   0
#define MRCC_PLL_HSE_2   1
#define MRCC_PLL_HSE     2









/***************************************************************************/
/*************************	MRCC_PLL_MUL_VAL	****************************/
/***************************************************************************/
#define    MRCC_MUL_BY_2     0
#define    MRCC_MUL_BY_3     1
#define    MRCC_MUL_BY_4     2
#define    MRCC_MUL_BY_5     3
#define    MRCC_MUL_BY_6     4
#define    MRCC_MUL_BY_7     5
#define    MRCC_MUL_BY_8     6
#define    MRCC_MUL_BY_9     7
#define    MRCC_MUL_BY_10    8
#define    MRCC_MUL_BY_11    9
#define    MRCC_MUL_BY_12    10
#define    MRCC_MUL_BY_13    11
#define    MRCC_MUL_BY_14    12
#define    MRCC_MUL_BY_15    13
#define    MRCC_MUL_BY_16    14






/***************************************************************************/
/*************************	MRCC_CS_SYS	*********************************/
/***************************************************************************/
#define MRCC_ENABLE_CS     1
#define MRCC_DISABLE_CS    0


#endif
