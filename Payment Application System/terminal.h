#ifndef TERMINAL
#define TERMINAL
/*************************************** Libraries ***************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include "card.h"
/******************************************* typedef ************************************************/

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t ;

/******************************************* function prototypes ************************************************/

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData); // get date of the day (now ast day / now month / now year)
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData); // check if the day date excedded the expiration date and return 0 if excedded and 1 if not
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData); //  get tarnsaction amount requested by the card holder
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData); // check if  the transaction amount requested exced the the max amount available for today return 0 if not excedded and 1 if excedded
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);
//EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional
#endif /* end of terminal.h */