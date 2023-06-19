#include "card.h"

/********************************************* Function Definitions ***********************************/

EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    uint16_t lenght = 0; // to store the length of card holder name 
    printf("Please Enter Your Name (20-24 character): \n");
    gets(cardData->cardHolderName); // get the card holder name from user
    lenght = strlen(cardData->cardHolderName); // lenth of the card holder name
    // check  card holder name length is valid between 20-24 character
    if (lenght < 20 && lenght > 24)
    {
        printf("Card Holder Name is OK \n");
        return CARD_OK;
    }
    else
    {
        printf("Error ! Card Holder Name is Not Ok (remember to enter 20-24 character) \n");
        return WRONG_NAME;
    }
}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
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

EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    uint16_t length = 0; // to store the length of card PAN 
    printf("Please Enter Your PAN (between 16 to 19 character): \n");
    gets(cardData->primaryAccountNumber); // get the card PAN from user
    length = strlen(cardData->primaryAccountNumber); // lenth of the card PAN
    // check  card PAN length is valid between 20 character
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