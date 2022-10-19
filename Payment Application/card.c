#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	uint8_t temp[25];
	printf("Enter cardholder's name : \n");


	gets(temp);

	if (strlen(temp) < 20 || strlen(temp) > 24) return WRONG_NAME;
	else
	{
		strcpy(cardData->cardHolderName, temp);
		return okCard;
	}
}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	uint8_t temp[6];
	printf("Enter  the card  expiry date in format YY/MM : \n");
	gets(temp);

	if (strlen(temp) < 5 || strlen(temp) > 5)return WRONG_EXP_DATE;
	else if (temp[2] != '/')return WRONG_EXP_DATE;
	else if (temp[0] > 57 || temp[0] < 48) return WRONG_EXP_DATE;
	else if (temp[1] > 57 || temp[1] < 48) return WRONG_EXP_DATE;
	else if (temp[3] == 48)
	{
		if (temp[4] > 57 || temp[4] < 49) return WRONG_EXP_DATE;
		else
		{
			strcpy(cardData->cardExpirationDate, temp);
			return okCard;
		}
	}
	else if (temp[3] == 49)
	{
		if (temp[4] == 48 || temp[4] == 49 || temp[4] == 50)
		{
			strcpy(cardData->cardExpirationDate, temp);
			return okCard;
		}
		else return WRONG_EXP_DATE;
	}
	else return WRONG_EXP_DATE;

}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	uint8_t temp[20];
	printf("Enter  the card's Primary Account Number : \n");
	gets(temp);
	if(strlen(temp)<16 || strlen(temp)>19)return WRONG_PAN;
	else
	{
		for (unit16_t i = 0; i < strlen(temp); i++)
		{
			if (temp[i] < 48 || temp[i] > 57) return WRONG_PAN;
		}
		strcpy(cardData->primaryAccountNumber, temp);
		return okCard;
	}
}