/*
 * DIO.c
 *
 * Created: 9/10/2022 8:55:31 PM
 *  Author: Hossam
 */ 

// including .h
#include "DIO.h"
// Global variable

// functions definitions 
void DIO_init(uint8_t PortNumber , uint8_t PinNumber , uint8_t direction )
{
 /*
 * Description : The function define the direction of the desired pin 
 */
	
 switch (PortNumber)
 {
	 case PORT_A:
	 
		 if(direction == OUTPUT)
		 {
			 SET_BIT(DDRA,PinNumber);
		 }
		 else if (direction ==INPUT)
		 {
			 CLEAR_BIT(DDRA,PinNumber);
		 }
		 else 
		 {
			 // ERROR HANDLING 
		 }
	 break;
	 
	 case PORT_B:
	 
		 if(direction == OUTPUT)
		 {
			 SET_BIT(DDRB,PinNumber);
		 }
		 else if (direction ==INPUT)
		 {
			 CLEAR_BIT(DDRB,PinNumber);
		 }
		 else
		 {
			 // ERROR HANDLING
		 }
	 break;

	 case PORT_C:
	 
		 if(direction == OUTPUT)
		 {
			 SET_BIT(DDRC,PinNumber);
		 }
		 else if (direction ==INPUT)
		 {
			 CLEAR_BIT(DDRC,PinNumber);
		 }
		 else
		 {
			 // ERROR HANDLING
		 }
	  break;

	 case PORT_D:
	 
		 if(direction == OUTPUT)
		 {
			 SET_BIT(DDRD,PinNumber);
		 }
		 else if (direction ==INPUT)
		 {
			 CLEAR_BIT(DDRD,PinNumber);
		 }
		 else
		 {
			 // ERROR HANDLING
		 }
	  break;
	  
	default:
			//Error HANDLING
	 break;
 }
}

void DIO_write(uint8_t PortNumber , uint8_t PinNumber , uint8_t value)
{
	switch(PortNumber)
	{
	case PORT_A:
	
		if(value == HIGH)
		{
			SET_BIT(PORTA,PinNumber);
		}
		else if (value == LOW)
		{
			CLEAR_BIT(PORTA,PinNumber);
		}
		else
		{
			// ERROR HANDLING
		}
	break;
	
	case PORT_B:
	
		if(value == HIGH)
		{
			SET_BIT(PORTB,PinNumber);
		}
		else if (value == LOW)
		{
			CLEAR_BIT(PORTB,PinNumber);
		}
		else
		{
			// ERROR HANDLING
		}
	break;

	case PORT_C:
	
		if(value == HIGH)
		{
			SET_BIT(PORTC,PinNumber);
		}
		else if (value == LOW)
		{
			CLEAR_BIT(PORTC,PinNumber);
		}
		else
		{
			// ERROR HANDLING
		}
	break;

	case PORT_D:
	
		if(value == HIGH)
		{
			SET_BIT(PORTD,PinNumber);
		}
		else if (value ==LOW)
		{
			CLEAR_BIT(PORTD,PinNumber);
		}
		else
		{
			// ERROR HANDLING
		}
	break;
	
	default:
	
		printf("PORT UNDEFINED");
		
	break;
	}
}
	

void DIO_toggle(uint8_t PortNumber , uint8_t PinNumber)
{
  switch(PortNumber)	
  {
	case PORT_A :
	
		TOGGLE_BIT(PORTA,PinNumber);
		break;
		
	case PORT_B:
		
		TOGGLE_BIT(PORTB,PinNumber);	
		break;
		
	case PORT_C:
	
		TOGGLE_BIT(PORTC,PinNumber);
		break;
		
	case PORT_D:
	
		TOGGLE_BIT(PORTD,PinNumber);	
		break;
	
	default:
		printf(" PORT is not defined");
		break;
		
  }
	
}

void DIO_read(uint8_t PortNumber , uint8_t PinNumber, uint8_t *value)
{
	
	switch(PortNumber)
	{
		case PORT_A :
		
		*value=(READ_BIT(PINA,PinNumber)); 

		
		break;
		
		case PORT_B:
		
		*value =(READ_BIT(PINB,PinNumber));
		
		break;
		
		case PORT_C:
		
		*value =(READ_BIT(PINC,PinNumber));
		
		break;
		
		case PORT_D:
		
		*value=(READ_BIT(PIND,PinNumber));
		
		break;
		
		default:
		printf(" PORT is not defined");
		break;
		
	}
	
	
	
}