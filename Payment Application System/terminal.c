#include "terminal.h"

/******************************************* function Definition  ************************************************/
// This function ask for the transaction date and store it in terminal data in 10 characters in format (DD/MM/YYYY)
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) 
{
    uint16_t length = 0, day, month, year;
    printf("\nEnter card transaction date in DD/MM/YYYY format : \n");
	gets(termData->transactionDate);
    day = (termData->transactionDate[0] - '0') * 10 + termData->transactionDate[1] - '0'; // to convert the two chars to a whole digit
	month = (termData->transactionDate[3] - '0') * 10 + termData->transactionDate[4] - '0'; 
	year = (termData->transactionDate[6] - '0') * 1000 + ( termData->transactionDate[7] - '0' ) * 100 + 
		(termData->transactionDate[8] - '0') * 10 + (termData->transactionDate[9] - '0');
    length = strlen(termData->transactionDate);
    if (termData->transactionDate[2] != '/' || termData->transactionDate[5] != '/' || month > 12 || month < 1 || day < 1 || day > 31
		|| year < 2000 || year > 2100)
	{
		printf("Transaction data is invalid (Wrong Format) ");
		return WRONG_DATE;
	}
    else if(length < 1 || length > 10)
    {
        printf("Error ! in valid transaction date \n");
        return WRONG_DATE;
    } 
    else 
    {
        printf("Valid Transaction date Card Terminal Ok\n");
        return TERMINAL_OK;
    }
}

// This function compares the card expiry date with the transaction date.
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    uint8_t Ex_month, Tr_month, Ex_year, Tr_year;
    Ex_month = (cardData->cardExpirationDate[0] - '0') * 10 + (cardData->cardExpirationDate[1] - '0');
    Ex_year = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');

    Tr_month = (cardData->cardExpirationDate[3] - '0') * 10 + (cardData->cardExpirationDate[4] - '0');
    Tr_year = (cardData->cardExpirationDate[6] - '0') * 1000 + (cardData->cardExpirationDate[7] - '0') * 100 + (cardData->cardExpirationDate[8] - '0') * 10 + (cardData->cardExpirationDate[9] - '0');

    if ( Tr_year < (Ex_year+2000))
	{
		printf("Card is not expired \n");
		return TERMINAL_OK;
	}
	else if ( Tr_month <= Ex_month && Tr_year == Ex_year )

	{
		printf("Card is not expired \n");
		return TERMINAL_OK;
	}
	else
	{
		printf("Card is expired \n");
		return EXPIRED_CARD;
	}
}

// This function asks for the transaction amount and saves it into terminal data.
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    float amount;
    printf("Enter Amount of Transaction \n");
    scanf("%f",&amount);

    if(amount <= 0)
    {
        printf("Invalid Amount !\n");
        return INVALID_AMOUNT;
    }
    else
    {
        termData->transAmount = amount;
        printf("Valid Transaction Amount\n");
        return TERMINAL_OK;
    }
}

// This function compares the transaction amount with the terminal max allowed amount.
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount > termData->maxTransAmount)
	{
		printf("\nOperation Failed !You exceeded the maximum amount \n");
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		printf("\nOperation Completed ! Transaction amount is below max Amount \n");
		return TERMINAL_OK;
	}
}

// This function takes the maximum allowed amount and stores it into terminal data.
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	float maxAmount;
	printf("Enter MaxAmount: \n");
	scanf("%f", &maxAmount);
	if (maxAmount <= 0)
	{
		printf("Invalid max Amount \n");
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = maxAmount;
		printf("Valid max amount \n");
		return TERMINAL_OK;
	}
}