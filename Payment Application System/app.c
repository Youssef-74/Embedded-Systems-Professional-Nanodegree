#define _CTR_SECURE_NO_WARNINGS
#define _CTR_NONSTDC_NO_WARNINGS
#include "app.h"
#include "card.h"
#include "terminal.h"
#include "server.h"
#include <stdio.h>

int main(void)
{
    appStart();
    printf("\n Operation Completed \n");

}

void appStart(void)
{
    /**********************************     Card module       **************************************/
    ST_cardData_t card_data; // ST_cardData_t variable
    ST_cardData_t *CardPtr = &card_data; //  store the address od card_data into CardPtr pointer
    EN_cardError_t CardHolderNameStatus, CardExpirationDateStatus, CardPANStatus;

                                          //  calling card module functions   //
    CardHolderNameStatus = getCardHolderName(CardPtr);
    while(CardHolderNameStatus == WRONG_NAME)
    {
        printf("\n\t -------- Wrong Name ! --------  \n");
        printf("Re_Enter the Name !\n");
        CardHolderNameStatus = getCardHolderName(CardPtr);
    }

    CardExpirationDateStatus = getCardExpiryDate(CardPtr);
    while (CardExpirationDateStatus == WRONG_EXP_DATE)
    {
        printf("\n\t -------- Wrong Expiration Date ! -------- \n");
        printf("Re_Enter Exp Date ! \n");
        CardExpirationDateStatus = getCardExpiryDate(CardPtr);
    }

    CardPANStatus = getCardPAN(CardPtr);
    while (CardPANStatus == WRONG_PAN)
    {
        printf("\n\t -------- Wrong PAN ! -------- \n");
        printf("Re_Enter PAN ! \n");
        CardPANStatus = getCardPAN(CardPtr);
    }

    /**********************************     Terminal module       **************************************/
    ST_terminalData_t TerminalData;
    ST_terminalData_t *TerminalPtr = &TerminalData;
    EN_terminalError_t TransactionDateStatus, CardExpirationStatus, TransactionAmountStatus, MaxAmountStatus, BelowMaxStatus;

                                              //  calling terminal module functions   //
    TransactionDateStatus = getTransactionDate(TerminalPtr);
    while(TransactionDateStatus == WRONG_DATE)
    {
        printf("\n\t -------- Wrong Transaction Date ! -------- \n");
        printf("Re_Enter Transaction Date ! \n");
        TransactionDateStatus = getTransactionDate(TerminalPtr);
    }

    printf("CHECKING if the CARD is expired or not .... \n");

    CardExpirationStatus = isCardExpired(CardPtr,TerminalPtr);
    while (CardExpirationStatus == EXPIRED_CARD)
    {
        printf("\n\t -------- DECLINED EXPIRED CARD ! -------- \n");
        return;                
    }
    
    TransactionAmountStatus = getTransactionAmount(TerminalPtr);
    while (TransactionAmountStatus == INVALID_AMOUNT)
    {
        printf("\n\t -------- INVALID TRANSACTION AMOUNT ! -------- \n");
        printf("Re-Enter\n");
        TransactionAmountStatus = getTransactionAmount(TerminalPtr);
    }
    
    MaxAmountStatus = setMaxAmount(TerminalPtr);
    while (MaxAmountStatus == INVALID_MAX_AMOUNT)
    {
        printf("\n\t -------- INVALID MAX AMOUNT ! -------- \n");
        printf("Re-Enter\n");
        MaxAmountStatus = setMaxAmount(TerminalPtr);
    }
    
    BelowMaxStatus = isBelowMaxAmount(TerminalPtr);
    while (BelowMaxStatus == EXCEED_MAX_AMOUNT)
    {
        printf("\n\t -------- DECLINED AMOUNT EXCEDDING LIMIT ! -------- \n");
        return;
    }

    /**********************************     Server module       **************************************/
    ST_transaction_t transData;   // declaring a variable as a ST_transaction_t Datatype
	EN_transState_t ReceiveTransactionStatus;   
	transData.cardHolderData = card_data; // Getting CardData in CardHoldeData which is a structure in TransactionData structure 
	transData.terminalData = TerminalData; // Getting TerminalData in terminalData which is a structure in TransactionData structure
    ReceiveTransactionStatus = recieveTransactionData(&transData); 
                                              //  calling server module functions   //
    
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
