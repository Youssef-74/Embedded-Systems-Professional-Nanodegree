
#include "timer.h"


void Timer_init( uint8_t MODE , uint8_t Initial_Value )
{
	
	switch(MODE)
	{
		case NORMAL:
		TCCR0 = 0x00; 
		TCNT0 = Initial_Value;
		break;
		case CTC:
		TCCR0 = 0x08;
		TCNT0 = Initial_Value;
		break;
		case FAST_PWM:
		TCCR0 = 0x48;
		TCNT0 = Initial_Value;
		break;
		case PWM_PC:
		TCCR0 = 0x40;
		TCNT0 = Initial_Value;
		break;
	}
}
void Timer_Start(unsigned int PRESCALAR)
{
	switch (PRESCALAR)
	{
		case NO_PRESCALAR:
		SET_BIT(TCCR0,0);
		break; 
		
		case PRESCALAR_8:
		SET_BIT(TCCR0,1);
		break;
		
		case PRESCALAR_64:
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,1);
		break;
		
		case PRESCALAR_256:
		SET_BIT(TCCR0,2);
		break;
		
		case PRESCALAR_1024:
		SET_BIT(TCCR0,0);
		SET_BIT(TCCR0,2);
		break;	
	}	
}


void Timer_Stop()
{
	TCCR0 = 0x00;
}

void Clear_OVERFLOWFLAG()
{
	SET_BIT(TIFR,0);
}

uint8_t Timer_status ()
{
	return READ_BIT(TIFR,0);
}

void Timer_5sec()
{
	Timer_init(NORMAL,255);
	Timer_Start(PRESCALAR_256);
	for(unsigned int i=0 ; i < 76 ; i++)
	{
		while(Timer_status() == 0 );
		Clear_OVERFLOWFLAG();
	}
	Timer_Stop();
}

void Timer_1sec()
{
	Timer_init(NORMAL,255);
	Timer_Start(PRESCALAR_256);
	for(unsigned int i=0 ; i < 16 ; i++)
	{
		while(Timer_status() == 0 );
		Clear_OVERFLOWFLAG();
	}
	Timer_Stop();
}

void Timer_halfsec()
{
	Timer_init(NORMAL,255);
	Timer_Start(PRESCALAR_256);
	for(unsigned int i=0 ; i < 8 ; i++)
	{
		while(Timer_status() == 0 );
		Clear_OVERFLOWFLAG();
	}
	Timer_Stop();
}