#include "server.h"

ST_transaction_t transactionDB[255] = { 0 }; // Define Transaction Data base 
int account_number; // declare a global variable to store the index of the found account 

//Defining a global array of ST_accountsDB_t for the valid accounts database
ST_accountsDB_t AccountsDatabase[255] = { 
500.0,    RUNNING ,"6228710870023450848" ,
100000.0, BLOCKED, "3254806311009193612" ,
600.0,    RUNNING ,"0128009909101280099" ,
2450  ,   RUNNING ,"4448165228813082938" ,
4510.0,   BLOCKED, "8582410934590079952" ,
};

/******************************************* function Definition  ************************************************/

//This function take all transaction data and validate its data, it contains all server logic
EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
    if(isValidAccount(transData->cardHolderData) == ACCOUNT_NOT_FOUND)
    {
        printf("Account Not Found ! \n");
        return FRAUD_CARD;
    }
    else if(isAmountAvailable(&(transData->terminalData)) == LOW_BALANCE)
    {
        printf("Insuffecient Fund ! \n");
        return DECLINED_INSUFFECIENT_FUND;
    }
    else if(AccountsDatabase[account_number].state == BLOCKED)
    {
        printf("Account is Blocked !\n");
        return DECLINED_STOLEN_CARD;
    }
    else
    {
        if(saveTransaction(transData) == SAVING_FAILED)
        {
            printf("Internal server Error !\n");
            return INTERNAL_SERVER_ERROR;
        }
        else
        {
            printf("Approved operation\n");
            return APPROVED;
        }
        
    }
}

// This function take card data and validate if the account related to this card exists or not.
EN_serverError_t isValidAccount(ST_cardData_t cardData)
{
    uint8_t i;
    for(i = 0; i < 255; i++)
    {
        if(strcmp (cardData.primaryAccountNumber, AccountsDatabase[i].primaryAccountNumber) == 0)
        {
            printf("Account is found\n");
            account_number = i;
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

//This function will take terminal data and a reference to the account in the database and check if the account has a sufficient amount to withdraw or not.
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
    if (termData->transAmount <= AccountsDatabase[account_number].balance)
    {
        printf("balance is sufficient \n");
        return SERVER_OK;
    }
    else
    {
        printf("low balance \n");
        return LOW_BALANCE;
    }
}

//This function store all transaction data in the transactions database.
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    static uint32_t sequenceNumber= 0;

    if (sequenceNumber != 255)
    {
        transactionDB[sequenceNumber].cardHolderData = transData->cardHolderData;
        transactionDB[sequenceNumber].terminalData = transData->terminalData;
        transactionDB[sequenceNumber].transactionSequenceNumber = sequenceNumber;
        transactionDB[sequenceNumber].transState = transData->transState;
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

// This function display all data for specific transaction 
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t* transData)
{
    uint8_t i;
    for(i = 0; i< 255; i++)
    {
        if(transactionDB[i].transactionSequenceNumber == transactionSequenceNumber)
        {
            printf("Card Holder Name \n: %s", transactionDB[i].cardHolderData.cardHolderName);
            printf("Expiration Date of Card \n: %s", transactionDB[i].cardHolderData.cardExpirationDate);
            printf("PAN of Card \n: %s", transactionDB[i].cardHolderData.primaryAccountNumber);
            printf("Terminal Max Transaction Amount \n: %f", transactionDB[i].terminalData.maxTransAmount);
            printf("Transaction Date \n: %s", transactionDB[i].terminalData.transactionDate);
            printf("Transaction Amount \n: %f", transactionDB[i].terminalData.transAmount);
            return SERVER_OK;
        } 
    }
    printf("Transaction Not Found !");
    return TRANSACTION_NOT_FOUND;
}