#define _CRT_SECURE_NO_WARNNINGS 
#define _CRT_NONSTDC_NO_WARNINGS
#include "app.h"
#include <stdio.h>

int main()
{
	
	 appStart();
	 printf("\nOperation is Compeleted \t \n");



}
void appStart(void)
{
										     	//  The card module //

	ST_cardData_t card_data; // declaring a ST_cardData_t variable 
	ST_cardData_t* CardPtr = &card_data; // store the address of the card_data structer into the CardPtr pointer
	EN_cardError_t CardHolderNameStatus , CardExpirationDateStatus , CardPanStatus; // declaring an EN_cardError_t variable to store the return of the Card module functions
	
											/* Calling the Card moudule functions */


							        		//calling get CardHolderName function	

	CardHolderNameStatus = getCardHolderName(CardPtr);
	while (CardHolderNameStatus == WRONG_NAME)
	{
		printf("\n\t--===WRONG_NAME===--\n");
		printf("Re-enter:\n");
		CardHolderNameStatus = getCardHolderName(CardPtr);

	}
										   // calling getCardExpiryDate function

	CardExpirationDateStatus = getCardExpiryDate(CardPtr); 
	while (CardExpirationDateStatus == WRONG_EXP_DATE)
	{
		printf("\n\t--===WRONG_EXPIRATION_DATE===--\n");
		printf("Re-enter:\n");
		CardExpirationDateStatus = getCardExpiryDate(CardPtr);
	}
	
											// calling getCardpan function
	CardPanStatus = getCardPAN(CardPtr);	    
	while (CardPanStatus == WRONG_PAN)
	{
		printf("\n\t--===WRONG_PAN===--\n");
		printf("Re-enter:\n");
		CardPanStatus = getCardPAN(CardPtr);

	}

										    	// The terminal module //

	ST_terminalData_t TerminalData; // declaring a ST_terminalData_t variable
	ST_terminalData_t* TerminalPtr = &TerminalData; // store the address of the TerminalData structer into the TerminalPtr pointer
	EN_terminalError_t TransactionDateStatus, CardExpirationStatus, TransactionAmountStatus, MaxAmountStatus, BeloxMaxStatus;
	
	
										// Calling the terminal module functions 
	
	TransactionDateStatus = getTransactionDate(TerminalPtr);
	while (TransactionDateStatus == WRONG_DATE)
	{
		printf("\n\t--===WRONG_Transaction_DATE===--\n");
		printf("Re-enter:\n");
		TransactionDateStatus = getTransactionDate(TerminalPtr);
	}
	
	printf("CHECKING if the CARD is expired Or not.... \n ");

	CardExpirationStatus = isCardExpired(card_data, TerminalData);
	
	if (CardExpirationStatus == EXPIRED_CARD)
	{
		printf("Declined Expired Card \n");
		return;
	}

	TransactionAmountStatus = getTransactionAmount(TerminalPtr);
	while (TransactionAmountStatus == INVALID_AMOUNT)
	{
		printf("\n\t--===INVALID TRANSACTION AMOUNT===--\n");
		printf("Re-enter:\n");
		TransactionAmountStatus = getTransactionAmount(TerminalPtr);
	}

	MaxAmountStatus = setMaxAmount(TerminalPtr);
	while (MaxAmountStatus == INVALID_MAX_AMOUNT)
	{
		printf("\n\t--===INVALID MAX AMOUNT===--\n");
		printf("Re-enter:\n");
		MaxAmountStatus = setMaxAmount(TerminalPtr);
	}

	BeloxMaxStatus = isBelowMaxAmount(TerminalPtr);
	if (BeloxMaxStatus == EXCEED_MAX_AMOUNT)
	{
		printf("Declined ! AMOUNT EXCEEDING LIMIT \n");
		return;
	}


										// The server module // 

	ST_transaction_t transData;   // declaring a variable as a ST_transaction_t Datatype
	EN_transState_t ReceiveTransactionStatus;   
	transData.cardHolderData = card_data; // Getting CardData in CardHoldeData which is a structure in TransactionData structure 
	transData.terminalData = TerminalData; // Getting TerminalData in terminalData which is a structure in TransactionData structure
	ReceiveTransactionStatus = recieveTransactionData(&transData); 
	if (ReceiveTransactionStatus == FRAUD_CARD)
	{
		printf("Declined Invalid Account \n");
		return;
	}
	else if (ReceiveTransactionStatus == DECLINED_INSUFFECIENT_FUND)
	{
		printf("Declined insuffecient funds \n");
		return;
	}
	else if (ReceiveTransactionStatus == DECLINED_STOLEN_CARD)
	{
		return;
	}
	else
	
	{
		/*To check the transaction database
		uint32_t SeqNum;
		EN_serverError_t TransactionStatus;
		printf("Enter Transaction Sequence number: \n");
		scanf_s("%d",&SeqNum);
		TransactionStatus = getTransaction(SeqNum, &transData);*/


		if (ReceiveTransactionStatus == APPROVED)
		{
			printf("\nOperation is approved \n");
			return;
		}
		else
		{
			printf("\nTransaction can't be saved \n ");
			return;
		}

	}















}