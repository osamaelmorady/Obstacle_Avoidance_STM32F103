#ifndef		_DELAY_H_
#define 	_DELAY_H_




#ifndef 	F_CPU	
#define 	F_CPU	1000000UL
#endif 

typedef unsigned long long int U64_Tim ;

#define _delay_ms(PERIOD)	for(U64_Tim i=0 ; i < (PERIOD*500*(F_CPU/1000000)) ; i++ )  asm("nop") 


#define _delay_us(PERIOD)	for(U64_Tim i=0 ; i < (PERIOD*500000*(F_CPU/1000000)) ; i++ )  asm("nop") 














#endif