/*
 * LED.h
 *
 * Created: 9/11/2022 5:56:37 PM
 *  Author: Hossam
 */ 


#ifndef LED_H_
#define LED_H_
#include "../../MCAL/DIO driver/DIO.h"

// LED driver APIs //

//LED initialization   
void LED_init(uint8_t ledPort , uint8_t ledPin );

//LED Control 
void LED_Write(uint8_t ledPort, uint8_t ledPin, uint8_t LED_STATUS);
void LED_ON(uint8_t ledPort, uint8_t ledPin );
void LED_OFF(uint8_t ledPort, uint8_t ledPin );
void LED_toggle(uint8_t ledPort , uint8_t ledPin ); 
void LED_YellowBlink();

//LED Status 
void LED_read(uint8_t ledPort , uint8_t PinNumber , uint8_t *value);




#endif /* LED_H_ */