#include "LED.h"


void LED_init(uint8_t ledPort , uint8_t ledPin )
{
	 DIO_init( ledPort ,  ledPin ,  OUTPUT);	
}

void LED_Write(uint8_t ledPort, uint8_t ledPin ,uint8_t LED_STATUS )
{
	 DIO_write( ledPort ,  ledPin ,  LED_STATUS);

}

void LED_ON(uint8_t ledPort, uint8_t ledPin )
{
	
	 DIO_write( ledPort ,  ledPin ,  HIGH);	
}

void LED_OFF(uint8_t ledPort, uint8_t ledPin )
{
	
	DIO_write( ledPort ,  ledPin , LOW);
}

void LED_toggle(uint8_t ledPort , uint8_t ledPin )
{
	 DIO_toggle( ledPort ,  ledPin);
}

void LED_read(uint8_t ledPort , uint8_t ledPin , uint8_t *LED_STATUS)
{
	  DIO_read( ledPort , ledPin, LED_STATUS); 
}

void LED_YellowBlink()
{
	for(uint8_t i = 0 ; i < 5 ; i++)
	{
		LED_toggle(PORT_A,1);
		LED_toggle(PORT_B,1);
		Timer_1sec();
	}
	LED_OFF(PORT_A,1);
	LED_OFF(PORT_B,1);
}