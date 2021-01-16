#ifndef		_SCAR_CONFIG_H_
#define 	_SCAR_CONFIG_H_




/*******************************************************************/
/*******************************************************************/
#define MOTOR_1_PIN1		PIN_A0
#define MOTOR_1_PIN2		PIN_A1
#define MOTOR_2_PIN1		PIN_A2
#define MOTOR_2_PIN2		PIN_A3




/*******************************************************************/
/*******************************************************************/
#define FRONT_LED_RIGHT_PIN	 PIN_A4
#define FRONT_LED_LEFT_PIN	 PIN_A5


#define BACK_LED_LEFT_PIN	 PIN_A6
#define BACK_LED_RIGHT_PIN	 PIN_A7






/*******************************************************************/
/*******************************************************************/
MOTOR_Configurations Motor1 = {MTIM2,PWM_CH1,PWM_CH2,10000} ;
MOTOR_Configurations Motor2 = {MTIM2,PWM_CH3,PWM_CH4,10000} ;










#endif
