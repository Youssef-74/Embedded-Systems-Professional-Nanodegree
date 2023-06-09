/*
 * button.h
 *
 * Created: 9/11/2022 7:24:22 PM
 *  Author: Hossam
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../MCAL/DIO driver/DIO.h"

//Button Driver APIs

//button Initialization
 
void BUTTON_init( uint8_t buttonPort , uint8_t buttonPin);

// button Read 

uint8_t BUTTON_read(uint8_t buttonPort , uint8_t buttonPin);


#endif /* BUTTON_H_ */