
#ifndef DIO_H_
#define DIO_H_
#include "../Utilities/types.h"
#include "../Utilities/registers.h"
#include "timer.h"
#include "../Utilities/interrupts.h"

// all internal typedef
typedef enum EN_PortDirection_t 
{
	INPUT , OUTPUT
}EN_PortDirection_t;

typedef enum EN_PortValue_t 
{
    LOW , HIGH
}EN_PortValue_t;

// all driver macros 

#define SET_BIT(X,BIT_NO) X |= (1<<BIT_NO)
#define CLEAR_BIT(X,BIT_NO) X &= ~(1<<BIT_NO)
#define TOGGLE_BIT(X,BIT_NO) X ^= (1<<BIT_NO)
#define READ_BIT(X,BIT_NO) (X&(1<<BIT_NO))>>BIT_NO
#define PORT_A  'A'
#define PORT_B  'B'
#define PORT_C  'C'
#define PORT_D  'D'

// DIO APIs
 
 void DIO_init(uint8_t PortNumber , uint8_t PinNumber , uint8_t direction ); // Initialize DIO direction 
 void DIO_write(uint8_t PortNumber , uint8_t PinNumber , uint8_t value); // write data to DIO 
 void DIO_toggle(uint8_t PortNumber , uint8_t PinNumber); // toggle DIO 
 void DIO_read(uint8_t PortNumber , uint8_t PinNumber, uint8_t *value); // read DIO 



#endif /* DIO_H_ */