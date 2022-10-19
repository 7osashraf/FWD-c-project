#include "terminal.h"



EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	uint8_t temp[11];
	printf("Enter the transaction data  in the format DD/MM/YYYY : \n");
	gets(temp);
	if (strlen(temp) < 10) return WRONG_DATE;
	else if (temp[2] != '/' || temp[5] != '/') return WRONG_DATE;
	else if (temp[0] < 48 || temp[0] > 51)return WRONG_DATE;
	else if (temp[1] < 48 || temp[1] > 57)return WRONG_DATE;
	else if (temp[3] < 48 || temp[3] > 49)return WRONG_DATE;
	else if (temp[4] < 48 || temp[4] > 57)return WRONG_DATE;
	else if (temp[6] < 48 || temp[6] > 57)return WRONG_DATE;
	else if (temp[7] < 48 || temp[7] > 57)return WRONG_DATE;
	else if (temp[8] < 48 || temp[8] > 57)return WRONG_DATE;
	else if (temp[9] < 48 || temp[9] > 57)return WRONG_DATE;
	else if (temp[0] == 48 && temp[1] == 48)return WRONG_DATE;
	else if (temp[0] == 51 && temp[1] > 49)return WRONG_DATE;
	else if (temp[3] == 48 && temp[4] == 48)return WRONG_DATE;
	else if (temp[3] == 49 && temp[4] > 50)return WRONG_DATE;
	else
	{
		

		strcpy(termData->transactionDate, temp);
		return okTerminal;

	}
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
	if (cardData.cardExpirationDate[0] < termData.transactionDate[8])
	{
		return EXPIRED_CARD;
	}

	if (cardData.cardExpirationDate[0] == termData.transactionDate[8])
	{
		if (cardData.cardExpirationDate[1] < termData.transactionDate[9])
			{
				return EXPIRED_CARD;
			}

		if (cardData.cardExpirationDate[1] == termData.transactionDate[9])
			{
				if (cardData.cardExpirationDate[3] < termData.transactionDate[3])
					{
						return EXPIRED_CARD;
					}
				if (cardData.cardExpirationDate[3] == termData.transactionDate[3])
				{
						if (cardData.cardExpirationDate[4] < termData.transactionDate[4])
							{
								return EXPIRED_CARD;
							}
					
				}
			}

	}
		return okTerminal;
	
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	float temp=0.0;
	printf("Enter  transaction amount : \n");
	scanf("%f",&temp);
	if (temp <= 0)return INVALID_AMOUNT;
	else
	{
		termData->transAmount = temp;
		return okTerminal;
	}
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)return EXCEED_MAX_AMOUNT;
	else return okTerminal;

}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
	float temp=0.0;
	printf("Enter Max amount : \n");
	scanf("%f",&temp);
	if (temp <= 0)return INVALID_MAX_AMOUNT;
	else
	{
		termData->maxTransAmount = temp;
		return okTerminal;
	}

}

