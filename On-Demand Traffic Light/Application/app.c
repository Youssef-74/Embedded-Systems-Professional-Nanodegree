/*
 * app.c
 *
 * Created: 9/12/2022 5:37:43 PM
 *  Author: Hossam
 */ 
#include "app.h"
#define false 0 
#define true 1 

//Global Variables 
volatile uint8_t Int_flag = false ;

void APP_init()
{
	// Configuration of the used PINS

	LED_init(PORT_A,0);
	LED_init(PORT_A,1);
	LED_init(PORT_A,2);
	LED_init(PORT_B,0);
	LED_init(PORT_B,1);
	LED_init(PORT_B,2);
	BUTTON_init(PORT_D,2);

	//interrupts Configuration
	sei(); // enable global interrupt
	RISING_EDGE_SETUP();
	SETUP_INT0();
}



void APP_Start() 
{

		//Normal mode activated 
		LED_ON(PORT_A,0); // Green for car
		LED_ON(PORT_B,2); // red for pedestrian 
		
		for(uint8_t i = 0 ; i < 10 ; i++)
		{
			Timer_halfsec();
			if(Int_flag == true)
			{
				pedestrian_mode();
				APP_Start();
			}
		}
		LED_OFF(PORT_A,0); // green for car 
		LED_OFF(PORT_B,2); // red for pedestrian 
		// Start the yellow led to blink	
		
		for(uint8_t i = 0 ; i < 10 ; i++)
		{
			LED_toggle(PORT_A,1);
			LED_toggle(PORT_B,1);
			Timer_halfsec();
			if(Int_flag == true)
			{
				pedestrian_mode();
				APP_Start();
			}
		}
		LED_OFF(PORT_A,1);
		LED_OFF(PORT_B,1);


		LED_ON(PORT_A,2);  // red for car 
		LED_ON(PORT_B,0); //  green for pedestrian
		
		for(uint8_t i = 0 ; i < 10 ; i++)
		{
			Timer_halfsec();
			if(Int_flag == true)
			{
				pedestrian_mode();
				APP_Start();
			}
		}
		
		LED_OFF(PORT_A,2); // red for car 
		LED_OFF(PORT_B,0); // green for pedestrian
		
		// Start the yellow led to blink
	for(uint8_t i = 0 ; i < 10 ; i++)
		{
			LED_toggle(PORT_A,1);
			LED_toggle(PORT_B,1);
			Timer_halfsec();
			if(Int_flag == true)
			{
				pedestrian_mode();
				APP_Start();
			}
		}	
	
}




void pedestrian_mode ()
{
	uint8_t Car_REDLED_status , Car_GreenLED_status ;

	// Pedestrian mode activated
	LED_read(PORT_A,2,&Car_REDLED_status);
	if(Car_REDLED_status == HIGH ) // if the car red led already active then extend it with another 5 secs
	{
		Timer_5sec();
	}
	else
	{
		LED_read(PORT_A,0,&Car_GreenLED_status);
		if(Car_GreenLED_status == LOW) // Indicates that the yellow led is blinking
		{
			LED_ON(PORT_B,2);
		}
		LED_OFF(PORT_A,0);
		LED_YellowBlink();
		LED_OFF(PORT_B,2);
		LED_ON(PORT_A,2);
		LED_ON(PORT_B,0);
		Timer_5sec();
	}

	LED_OFF(PORT_A,2);
	LED_YellowBlink();
	LED_OFF(PORT_B,0);
	LED_ON(PORT_B,2);
	LED_ON(PORT_A,0);
	
	Int_flag = false ;
}



ISR(EXT_INT_0)
{
	 Int_flag = true;
}