#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "card.h"

// GetCardHolderName function definition  

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint16_t length = 0; // define a variable to store the length of the CARD holder name 
	printf("Enter your name (20-24 characters) : \n"); // asking the user to enter his/her name 
	gets(cardData->cardHolderName); // Getting the name and storing it in cardHolderName
	length = strlen(cardData->cardHolderName); // getting the length of the cardHolderName

	if (length >= 20 && length <= 24)  // check if the entered name is within range or not 
	{
		printf("Card holder name is valid \n");
		return CARD_OK;
	}
	else
	{
		printf("ERROR ! card holder name is not valid (number of the characters is not within the range)  \n");
		return WRONG_NAME;
	}
}

 // getCardExpiryDate function definiton

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{

	uint16_t length = 0 , month , year;
	printf("\nEnter card expiry date in MM/YY format : \n");
	gets(cardData->cardExpirationDate); 
	month = (cardData->cardExpirationDate[0] - '0') * 10 + cardData->cardExpirationDate[1] - '0';  
	year = (cardData->cardExpirationDate[3] - '0') * 10 + cardData->cardExpirationDate[4] - '0';
	length = strlen(cardData->cardExpirationDate); // getting the length of the card expiration date 
	if (length != 5)
	{
		printf("ERROR ! cardExpiration date is not valid ( Not a valid number of characters ) \n");
		return WRONG_EXP_DATE;
	}
	else if (month < 1 || month > 12 || year < 0 || year > 99 || cardData->cardExpirationDate[2] != '/')
	{
		printf("ERROR ! cardExpiration date is not in a valid format \n");
		return WRONG_EXP_DATE;
	}
	else
	{
		printf("cardExpiration date is valid \n");
		return CARD_OK;
	}
}
 // getCardPan function definition 

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint16_t length = 0;
	printf("\nEnter card PAN (between 16 to 19 characters): \n");
	gets(cardData->primaryAccountNumber);
	length = strlen(cardData->primaryAccountNumber); // getting the length of the Card PAN

	if (length >= 16 && length <= 19)
	{
		for (int i = 0; i < length; i++)
		{
			if (!isdigit(cardData->primaryAccountNumber[i])) //to check if the PAN entered has a non numeric value 
			{
				printf("ERROR ! Card PAN has a non numeric value \n");
				return WRONG_PAN;
			}
		}
		printf("Card PAN is valid \n");
		return CARD_OK;
	}

	else
	{
		printf("ERROR ! Card PAN is not valid \n");
		return WRONG_PAN;
	}
}
