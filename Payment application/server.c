#include "card.h"
#include "terminal.h"
#include "server.h"
#include <stdio.h>
#include <string.h>

ST_transaction_t transactionsDatabase[255] = { 0 }; // Define Transaction Data base 
 int account_number; // declare a global variable to store the index of the found account 

//Defining a global array of ST_accountsDB_t for the valid accounts database
 ST_accountsDB_t AccountsDatabase[255] = { 
	500.0,    RUNNING ,"6228710870023450848" ,
	100000.0, BLOCKED, "3254806311009193612" ,
    600.0,    RUNNING ,"0128009909101280099" ,
	2450  ,   RUNNING ,"4448165228813082938" ,
	4510.0,   BLOCKED, "8582410934590079952" ,
};



EN_transState_t  recieveTransactionData(ST_transaction_t* transData)
{
	EN_serverError_t ValidAccountStatus ,transactionStatus; 
	EN_accountState_t accountStatus;

	if (ValidAccountStatus = isValidAccount(transData->cardHolderData) == ACCOUNT_NOT_FOUND)
	{
		printf("Account is not found \n");
		return FRAUD_CARD;
	}
	else if ((ValidAccountStatus = isAmountAvailable(&(transData->terminalData)) == LOW_BALANCE))
	{
		printf("INSUFFECIEND FUND \n");
		return DECLINED_INSUFFECIENT_FUND;
	}
	else if ((accountStatus = AccountsDatabase[account_number].state == BLOCKED))
	{
		printf("Account is blocked \n");
		return DECLINED_STOLEN_CARD;
	}
	else
	{
		transactionStatus = saveTransaction(transData);
		if (transactionStatus == SAVING_FAILED)
		{
			return INTERNAL_SERVER_ERROR;
		}
		else
		{
			printf("Approved \n");
			return APPROVED;

		}
	}

}

EN_serverError_t isValidAccount(ST_cardData_t cardData)
{
	for (int i = 0; i < 255; i++)
	{
		if (strcmp(cardData.primaryAccountNumber, AccountsDatabase[i].primaryAccountNumber) == 0)
		{
			printf("Account is found\n");
			account_number = i;
			return SERVER_OK;
		}	
	}
	return ACCOUNT_NOT_FOUND;
}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{

	if (termData->transAmount > AccountsDatabase[account_number].balance)
	{
		printf("Low balance\n");
		return LOW_BALANCE;
	}
	else
	{
		("Balance is sufficient \n");
		return SERVER_OK;
	}

}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	static uint32_t sequenceNumber =0 ;


	if (sequenceNumber != 255)
	{
		transactionsDatabase[sequenceNumber].cardHolderData = transData->cardHolderData;
		transactionsDatabase[sequenceNumber].terminalData = transData->terminalData;
		transactionsDatabase[sequenceNumber].transactionSequenceNumber = sequenceNumber;
		printf("\n sequence number of the transaction is : %d \n", sequenceNumber);
		sequenceNumber++;
		AccountsDatabase[account_number].balance -= transData->terminalData.transAmount;
		printf("\n New balance is: %f \n ", AccountsDatabase[account_number].balance);
		printf("SAVING SUCCESS\n");
		return SERVER_OK;
	}
	else
	{
		printf("SAVING FAILED ");
		return SAVING_FAILED;
	}

}
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
	for (int i = 0; i < 255; i++)
	{
		if (transactionsDatabase[i].transactionSequenceNumber == transactionSequenceNumber)
		{
			printf("Card Holder name : %s \n", transactionsDatabase[i].cardHolderData.cardHolderName);
			printf("Card expiration date : %s \n", transactionsDatabase[i].cardHolderData.cardExpirationDate);
			printf("Card PAN : %s \n", transactionsDatabase[i].cardHolderData.primaryAccountNumber);
			printf("Terminal Max amount %f \n", transactionsDatabase[i].terminalData.maxTransAmount);
			printf("Transaction date : %s \n", transactionsDatabase[i].terminalData.transactionDate);
			printf("Transaction amount : %f \n", transactionsDatabase[i].terminalData.transAmount);
			return SERVER_OK;
		}
	}
	printf("\nTransaction Not found \n");
	return TRANSACTION_NOT_FOUND;

}
