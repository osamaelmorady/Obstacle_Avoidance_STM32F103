
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include "LIB/ERROR_STATE.h"



#include "MRCC/MRCC_Config.h"
#include "MRCC/MRCC_Private.h"

#include "MRCC/MRCC_Interface.h"





/*******************************************************************************************************/
/**************************************	RCC  INITIALIZATION	*************************************/
/*******************************************************************************************************/
ErrorState MRCC_InitSysClk(void)
{

#if MRCC_SYSTEM_CLOCK == MRCC_HSE_CRYSTAL

	/* Switch to HSE System Clock */
	MRCC ->	CFGR = 0x00000001  ;

	/* SET HSEON=1  , HSITRIM as Standard = (10000) , Bypass HSEBYP=0 */
	MRCC -> CR =0x00010080 ;

	/* Wait for the flag to be fired */
	while( !GET_BIT( MRCC -> CR , CR_HSERDY )	) ;


#elif MRCC_SYSTEM_CLOCK == MRCC_HSE_RC

	/* Switch to HSE System Clock */
	MRCC ->	CFGR = 0x00000001  ;

	/* SET HSEON=1  , HSITRIM as Standard = (10000) , Bypass HSEBYP=1 for EXT RC */
	MRCC -> CR =0x00050080 ;

	/* Wait for the flag to be fired */
	while( !GET_BIT( MRCC -> CR , CR_HSERDY )	) ;


#elif	MRCC_SYSTEM_CLOCK == MRCC_HSI

	/* Switch to HSI System Clock */
	MRCC ->	CFGR = 0x00000000  ;

	/* SET HSION=1  , HSITRIM as Standard = (10000) , Bypass HSEBYP=0 for INT RC */
	MRCC -> CR =0x00000081 ;

	/* Wait for the flag to be fired */
	while( !GET_BIT( MRCC -> CR , CR_HSIRDY )	) ;



#elif	MRCC_SYSTEM_CLOCK == MRCC_PLL

	/* Switch to HSI System Clock as default */
	MRCC ->	CFGR = 0x00000000  ;

	/* SET HSION=1  , HSITRIM as Standard = (10000) , Bypass HSEBYP=0 for INT RC */
	MRCC -> CR =0x00000081 ;

	/* Switch to PLL System Clock */
	MRCC ->	CFGR = 0x00000002  ;


	/* Multiplication Factor for PLL CLK */
	#if( MRCC_PLL_MUL_VAL >= MRCC_MUL_BY_2 ) && ( MRCC_PLL_MUL_VAL <= MRCC_MUL_BY_16 )

		/* Clear the 4 bits from Bit_18 to Bit_22 */
		(MRCC -> CFGR) &= ~( 0b1111 << 18 )  ;

		/* Modify the value on 4 bits from Bit_18 to Bit_22 */
		(MRCC -> CFGR) |= ( MRCC_PLL_MUL_VAL<<18 ) ;

	#else
		#error  "Attention, Wrong MRCC_PLL_MUL_VAL !!"
	#endif



	#if	MRCC_PLL_INPUT == MRCC_PLL_HSI_2

		/* HSI System CLK is already Enabled */
		/*  PLL Entry Clock Source Selection (HSI) */
		CLR_BIT( MRCC -> CFGR , CFGR_PLLSRC );

	#elif	MRCC_PLL_INPUT == MRCC_PLL_HSE_2

		/* Enable  HSE System Clock */
		SET_BIT( MRCC -> CR , CR_HSEON );

		/*  PLL Entry Clock Source Selection (HSE) */
		SET_BIT( MRCC -> CFGR , CFGR_PLLSRC );

		/* (HSE) Clock Divider Enabled to be divided by 2  */
		SET_BIT( MRCC -> CFGR , CFGR_PLLXTPRE );



	#elif	MRCC_PLL_INPUT == MRCC_PLL_HSE

		/* Enable  HSE System Clock */
		SET_BIT( MRCC -> CR , CR_HSEON );

		/*  PLL Entry Clock Source Selection (HSE) */
		SET_BIT( MRCC -> CFGR , CFGR_PLLSRC );

		/* (HSE) Clock Divider Disabled   */
		CLR_BIT( MRCC -> CFGR , CFGR_PLLXTPRE );



	#else
		#error "Attention, Wrong PLL_INPUT !!"
	#endif


		/* Enable  PLL System Clock */
		SET_BIT( MRCC -> CR , CR_PLLON );

		/* Wait for the flag to be fired */
		while( GET_BIT( MRCC -> CR , CR_PLLRDY ) == 0 );

#else
	#error	"Attention, Wrong MRCC_SYSTEM_CLOCK !!"
#endif


#if MRCC_SYSTEM_CLK_SECURITY	==	MRCC_ENABLE_CS

		/* Enable Clock System Security */
		SET_BIT( MRCC -> CR , CR_CSSON ) ;

#elif MRCC_SYSTEM_CLK_SECURITY	==	MRCC_DISABLE_CS

		/* Disable Clock System Security */
		CLR_BIT( MRCC -> CR , CR_CSSON ) ;


#else
	#error	"Attention, Wrong MRCC_SYSTEM_CLK_SECURITY !!"
#endif


		return ES_OK ;
}











/***************************************************************************************************************/
/*****************************************		PERIPHERAL CLK ENABLE  	****************************************/
/***************************************************************************************************************/

ErrorState	 MRCC_EnuEnablePeriphClock( u8 Copy_u8PeripheralId ){

	u8 Copy_u8BusId = Copy_u8PeripheralId/32 ;

	switch( Copy_u8BusId ){

		case MRCC_AHB   :

			SET_BIT( MRCC -> AHBENR  , Copy_u8PeripheralId  );  break;

		case MRCC_APB1  :

			Copy_u8PeripheralId = (Copy_u8PeripheralId % 32)  ;

			SET_BIT( MRCC -> APB1ENR , Copy_u8PeripheralId ) ;  break;

	    case MRCC_APB2  :

	    	Copy_u8PeripheralId = (Copy_u8PeripheralId % 64) ;

	    	if (Copy_u8PeripheralId >= GPIOA_BIT && Copy_u8PeripheralId <= GPIOG_BIT )

	    		{	MRCC -> APB2ENR |= ( GPIO_BITS << GPIOA_BIT )    ;	}

	    	else
	    		{	SET_BIT( MRCC -> APB2ENR , Copy_u8PeripheralId ) ;	}

	    	break;

	}

	return ES_OK ;
}







/***************************************************************************************************************/
/*****************************************		PERIPHERAL CLK DISABLE  	****************************************/
/***************************************************************************************************************/

ErrorState	 MRCC_EnuDisablePeriphClock( u8 Copy_u8PeripheralId ){

	u8 Copy_u8BusId = Copy_u8PeripheralId/32 ;

		switch( Copy_u8BusId ){

			case MRCC_AHB   :

				CLR_BIT( MRCC -> AHBENR  , Copy_u8PeripheralId  );  break;

			case MRCC_APB1  :

				Copy_u8PeripheralId = (Copy_u8PeripheralId % 32) ;

				CLR_BIT( MRCC -> APB1ENR , Copy_u8PeripheralId ) ;  break;

		    case MRCC_APB2  :

		    	Copy_u8PeripheralId = (Copy_u8PeripheralId % 64)  ;

		    	if ( Copy_u8PeripheralId >= GPIOA_BIT && Copy_u8PeripheralId <= GPIOG_BIT )

		    		    {	 MRCC -> APB2ENR  &= ~( GPIO_BITS << GPIOA_BIT )    ;	}

		    	else
		    			{	CLR_BIT( MRCC -> APB2ENR , Copy_u8PeripheralId ) ; 	}

		    	break;

		}

		return ES_OK ;
}



















