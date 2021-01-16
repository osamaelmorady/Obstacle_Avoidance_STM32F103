/*
 * BIT_MATH.h
 *
 *  Created on: DEC 5, 2020
 *      Author: OSAMA ELMORADY
 */

#ifndef 	_BIT_MATH_H_
#define 	_BIT_MATH_H_





/* To Set a bit in a register  */
#define SET_BIT(REG,BIT_NUMBER)		(	REG |= (1<<BIT_NUMBER)	)




/* To Clear a bit in a register  */
#define CLR_BIT(REG,BIT_NUMBER)		(	REG &= (~(1<<BIT_NUMBER))	)



/* To Toggle a bit in a register  */
#define TOGGLE_BIT(REG,BIT_NUMBER)		(	REG ^= (1<<BIT_NUMBER)	)



/* To Get a bit From a register  */
#define GET_BIT(REG,BIT_NUMBER)		(	( REG>>BIT_NUMBER )&1		)







#endif
