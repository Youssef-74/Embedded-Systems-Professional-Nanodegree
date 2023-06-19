#include "DIO.h"

#ifndef TIMER_H_
#define TIMER_H_

// USER defined macros 
#define NORMAL 'N'
#define CTC    'C'
#define FAST_PWM 'F'
#define PWM_PC 'P'
#define NO_PRESCALAR '0'
#define PRESCALAR_8 '1'
#define PRESCALAR_64 '2'
#define PRESCALAR_256 '3'
#define PRESCALAR_1024 '4'


// Timer APIs
void Timer_init( uint8_t MODE , uint8_t Initial_Value); //Initialize the timer by defining the mode and the initial value
void Timer_Start(unsigned int PRESCALAR); // Start the timer by defining the prescalar 
void Timer_Stop(); // Stop the timer 
void Clear_OVERFLOWFLAG(); // Clear overflow flag by setting bit 0 in TIFR register 
void Timer_5sec(); // Start a timer with 5 seconds delay  
void Timer_1sec(); // start a timer with 1 second delay 
void Timer_halfsec();
uint8_t Timer_status(); // Get the timer status by checking on the overflow flag 




#endif /* TIMER_H_ */