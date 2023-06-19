#include"button.h"

void BUTTON_init( uint8_t buttonPort , uint8_t buttonPin)
{
	 DIO_init( buttonPort ,  buttonPin , INPUT);
}
void BUTTON_read(uint8_t buttonPort , uint8_t buttonPin ,uint8_t *Button_Status)
{
	DIO_read( buttonPort , buttonPin, Button_Status);
}
