/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "parseJY.h"
#include "string.h"
#include "usart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t jy61sData[11];
static uint8_t tempBuffer, tempHeader;

STime			stcTime;
SAcc			stcAcc;
SGyro			stcGyro;
SAngle		stcAngle;
SMag			stcMag;
SDStatus	stcDStatus;
SPress		stcPress;
SLonLat		stcLonLat;
SGPSV			stcGPSV;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void findHeader(void)
{
	//Change DMA to get only 1 bit data
	HAL_UART_DMAStop(&huart1);
	HAL_UART_Receive_DMA(&huart1, &tempBuffer, 1);
	tempHeader = SET;
}

void initJY(void)
{
	findHeader();
}

void parseJY_DMA_Data(void)
{
	//Check SUM
	static uint8_t tempSum, i;
	tempSum = 0;
	for(i = 0; i < 10; i++)
		tempSum += jy61sData[i];
	if(tempSum != jy61sData[10])
		return;
	
	//Parse Data
	switch(jy61sData[1])
	{
			case 0x50: memcpy(&stcTime, &jy61sData[2], 8); break;
			case 0x51: memcpy(&stcAcc, &jy61sData[2], 8); break;
			case 0x52: memcpy(&stcGyro, &jy61sData[2], 8); break;
			case 0x53: memcpy(&stcAngle, &jy61sData[2], 8); break;
			case 0x54: memcpy(&stcMag, &jy61sData[2], 8); break;
			case 0x55: memcpy(&stcDStatus, &jy61sData[2], 8); break;
			case 0x56: memcpy(&stcPress, &jy61sData[2], 8); break;
			case 0x57: memcpy(&stcLonLat, &jy61sData[2], 8); break;
			case 0x58: memcpy(&stcGPSV, &jy61sData[2], 8); break;
	}
}

void receiveJY_DMA_Data(void)
{
	static uint8_t tempCnt, findingFlag;
	if(tempHeader == SET)
	{
		if(tempBuffer == 0x55)
		{
			tempCnt = 0;
			findingFlag = SET;
		}
		else if(findingFlag == SET)
		{
			tempCnt++;
			if(tempCnt == 10)
			{
				findingFlag = RESET;
				tempHeader = RESET;
				HAL_UART_DMAStop(&huart1);
				HAL_UART_Receive_DMA(&huart1, jy61sData, 11);
			}
		}
	}
	else
	{
		if(jy61sData[0] != 0x55)
			findHeader();
		else
			parseJY_DMA_Data();
	}
}
