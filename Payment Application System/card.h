#ifndef CARD
#define CARD
/*************************************** Libraries ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
/******************************************* typedef ************************************************/
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

// structure that holdes card holder name - expiration date - PAN
typedef struct ST_cardData_t
{
     uint8_t cardHolderName[25]; // card holder name
     uint8_t primaryAccountNumber[20]; // PAN
     uint8_t cardExpirationDate[6]; // card expiration date
}ST_cardData_t;

// enumeration wich holdes the scinarios of responses 
typedef enum EN_cardError_t
{
     CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;
/******************************************* function prototypes ************************************************/

EN_cardError_t getCardHolderName(ST_cardData_t *cardData);// get Card Holder Name
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);// get Card Expiration Date
EN_cardError_t getCardPAN(ST_cardData_t *cardData);//get card PAN (Primarry Account Number) 
#endif /* end of card.h */