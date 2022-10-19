#include "app.h"
ST_cardData_t cardData;
EN_cardError_t cardError;
ST_terminalData_t terminalData;
EN_terminalError_t terminalError;
ST_transaction_t transaction;
EN_transState_t tranState;
EN_serverError_t serverError;


int main()
{
	appStart();
	return 0;
};

void appStart(void)
{

	//CARD


	cardError = getCardHolderName(&cardData);
	while (cardError == WRONG_NAME)
	{
		printf("Wrong NAME PLEASE TRY AGAIN\n");
		cardError = getCardHolderName(&cardData);
	}

	cardError = getCardExpiryDate(&cardData);
	while (cardError == WRONG_EXP_DATE)
	{
		printf("Wrong EXPIRY DATE PLEASE TRY AGAIN\n");
		cardError = getCardExpiryDate(&cardData);
	}


	cardError = getCardPAN(&cardData);
	while (cardError == WRONG_PAN)
	{
		printf("Wrong PAN  PLEASE TRY AGAIN\n");
		cardError = getCardPAN(&cardData);
	}


	//TERMIANL
	terminalError = getTransactionDate(&terminalData);
	while (terminalError == WRONG_DATE)
	{
		printf("WRONG DATE PLEASE ENTER VALID DATE\n");
		terminalError = getTransactionDate(&terminalData);
	}

	

	terminalError = isCardExpired(cardData, terminalData);
	
	if (terminalError == EXPIRED_CARD)
	{
		printf("YOUR CARD IS EXPIRED\n");
		return 0;
	}

	terminalError = setMaxAmount(&terminalData);
	while (terminalError == INVALID_AMOUNT)
	{
		printf("INVALID_AMOUNT \n");
		printf("PLEASE  ENTER VALID AMOUNT \n");
		terminalError = setMaxAmount(&terminalData);
	}

	terminalError = getTransactionAmount(&terminalData);
	while (terminalError == INVALID_AMOUNT)
	{
		printf("INVALID_AMOUNT \n");
		printf("PLEASE  ENTER VALID AMOUNT \n");
		terminalError = getTransactionAmount(&terminalData);
	}

	terminalError = isBelowMaxAmount(&terminalData);
	if (terminalError == EXCEED_MAX_AMOUNT)
	{
		printf("EXCEED MAX AMOUNT \n");
		return 0;
	}


	transaction.terminalData = terminalData;
	transaction.cardHolderData = cardData;


	//SERVER

	
	tranState = recieveTransactionData(&transaction);

	if (tranState == APPROVED)
	{

		printf("\n APPROVED \n");
	}
	else if (tranState == DECLINED_STOLEN_CARD)
	{
		printf("\n DECLINED STOLEN CARD\n");
	}
	else if (tranState == DECLINED_INSUFFECIENT_FUND)
	{
		printf("\n DECLINED INSUFFECIENT FUND\n");
	}
	else if (tranState == INTERNAL_SERVER_ERROR)
	{
		printf("\n INTERNAL SERVER ERROR\n");
	}
	
	
	






}


