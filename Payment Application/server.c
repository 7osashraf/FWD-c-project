#include "server.h"

uint32_t index = -1;
static uint32_t sequense = 0;


ST_accountsDB_t dataBase_acc[255] = {
	{2500.0,"1234567890123466789"},
	{3000.0,"1234789045560067876"},
	{1200.0,"1234543875845756577"}
};
ST_transaction_t transactionDataBase[255] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t* transData)
{
	if (isValidAccount(&transData->cardHolderData) == DECLINED_STOLEN_CARD)
	{
		transData->transState = DECLINED_STOLEN_CARD;
		return DECLINED_STOLEN_CARD;
	}
	if (isAmountAvailable(&transData->terminalData) == LOW_BALANCE)
	{
		transData->transState = DECLINED_INSUFFECIENT_FUND;
		return DECLINED_INSUFFECIENT_FUND;
	}
	
	dataBase_acc[index].balance -= transData->terminalData.transAmount;
	transData->transState = APPROVED;
	printf(" Balance available after withdrawal = %f\n", dataBase_acc[index].balance);

	if (saveTransaction(&transData) == SAVING_FAILED)
	{
		return INTERNAL_SERVER_ERROR;
	}

	return APPROVED;

}
EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
	uint32_t n = 0;
	while (n <= 255)
	{
		if (!strcmp(cardData->primaryAccountNumber , dataBase_acc[n].primaryAccountNumber))
		{
			index = n;
			return okServer;
		}
			n++;
	}
	 return DECLINED_STOLEN_CARD;

}
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
	if ((termData->transAmount) > (dataBase_acc[index].balance))
	{
		return LOW_BALANCE;
	}
	else
	{
		return okServer;
	}

}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	if (sequense < 0 || sequense > 255)
	{
		return SAVING_FAILED;
	}
	else
	{
		strcpy(transactionDataBase[sequense].cardHolderData.cardExpirationDate, transData->cardHolderData.cardExpirationDate);
		strcpy(transactionDataBase[sequense].cardHolderData.cardHolderName, transData->cardHolderData.cardHolderName);
		strcpy(transactionDataBase[sequense].cardHolderData.primaryAccountNumber, transData->cardHolderData.primaryAccountNumber);

		transactionDataBase[sequense].terminalData.maxTransAmount = transData->terminalData.maxTransAmount;
		transactionDataBase[sequense].terminalData.transAmount = transData->terminalData.transAmount;
		strcpy(transactionDataBase[sequense].terminalData.transactionDate, transData->terminalData.transactionDate);

		transData->transactionSequenceNumber = sequense;
		transactionDataBase[sequense].transactionSequenceNumber = 47859 + sequense;//47859 this is number for transaction will be increment every transaction 

		transactionDataBase[sequense].transState = transData->transState;

		sequense++;
		return okServer;
	}

	/*EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t * transData)
	{

	}*/
	


}
EN_serverError_t getTransaction(uint32_t transSequenceNumber)
{
	uint32_t n = 0;
	while (n <= 255)
	{
		if (transSequenceNumber == transactionDataBase[n].transactionSequenceNumber)
		{
			return okServer;
		}
	}
	return TRANSACTION_NOT_FOUND;
}
