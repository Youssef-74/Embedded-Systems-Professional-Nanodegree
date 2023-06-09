#include <stdio.h>
#include <string.h>
#include "card.h"
#include "terminal.h"


EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint16_t length = 0 ,day,month,year;
	printf("Enter Transaction Date in the format DD/MM/YYYY : ");
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
	else if (length != 10)
	{
		printf("Transaction Date invalid (The user did not enter 10 characters) \n");
		return WRONG_DATE;
	}
	else
	{
		printf("Valid Transaction date \n");
		return TERMINAL_OK;
	}
}


EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	uint16_t Card_month = (cardData.cardExpirationDate[0] - '0') * 10 + cardData.cardExpirationDate[1] - '0';
	uint16_t Card_year = (cardData.cardExpirationDate[3] - '0') * 10 + cardData.cardExpirationDate[4] - '0';
	uint16_t Tran_month = (termData.transactionDate[3] - '0') * 10 + termData.transactionDate[4] - '0';
	uint16_t Tran_year = (termData.transactionDate[6] - '0') * 1000 + (termData.transactionDate[7] - '0') * 100 +
		(termData.transactionDate[8] - '0') * 10 + (termData.transactionDate[9] - '0');
	//printf("\n %hu %hu %hu %hu \n", Card_month, Card_year, Tran_month, Tran_year);
	if ( Tran_year < (Card_year+2000))
	{
		printf("Card is not expired \n");
		return TERMINAL_OK;
	}
	else if ( Tran_month <= Card_month && Tran_year == Card_year )

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
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float amount;
	printf("Enter transaction amount: \n");
	scanf_s("%f",&amount);
	if (amount <= 0)
	{
		printf("Invalid Amount \n");
		return INVALID_AMOUNT;
	}
	else
	{
		termData->transAmount = amount;
		printf("Valid transaction amount\n");
		return TERMINAL_OK;
	}
}

EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	float maxAmount;
	printf("Enter MaxAmount: \n");
	scanf_s("%f", &maxAmount);
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
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
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
