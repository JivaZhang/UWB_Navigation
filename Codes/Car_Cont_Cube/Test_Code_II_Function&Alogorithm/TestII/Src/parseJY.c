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
#define G		9.8
/* Private macro -------------------------------------------------------------*/
typedef struct
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
}STime;

typedef struct
{
	short a[3];
	short T;
}SAcc;

typedef struct
{
	short w[3];
	short T;
}SGyro;

typedef struct
{
	short Angle[3];
	short T;
}SAngle;

typedef struct
{
	short h[3];
	short T;
}SMag;

typedef struct
{
	short sDStatus[4];
}SDStatus;

typedef struct
{
	long lPressure;
	long lAltitude;
}SPress;

typedef struct
{
	long lLon;
	long lLat;
}SLonLat;

typedef struct
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
}SGPSV;


typedef struct
{
	float imuAx;
	float imuAy;
	float imuAz;
}IMUAcc;

typedef struct
{
	float imuWx;
	float imuWy;
	float imuWz;
}IMUGyro;

typedef struct
{
	float imuRollx;
	float imuPitchy;
	float imuYawz;
}IMUAngle;

typedef struct
{
	float imuMagx;
	float imuMagy;
	float imuMagz;
}IMUMag;

/* Private variables ---------------------------------------------------------*/
static uint8_t jy61sData[11];
static uint8_t tempBuffer, tempHeader;

static STime			stcTime;
static SAcc			stcAcc;
static SGyro			stcGyro;
static SAngle		stcAngle;
static SMag			stcMag;
static SDStatus	stcDStatus;
static SPress		stcPress;
static SLonLat		stcLonLat;
static SGPSV			stcGPSV;

static IMUAcc			carAcc;
static IMUGyro		carGyro;
static IMUAngle		carAngle;
static IMUMag			carMag;

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
			case 0x51: memcpy(&stcAcc, &jy61sData[2], 8); 
									carAcc.imuAx = stcAcc.a[0] * 16.0 * G / 32768.0;
									carAcc.imuAy = stcAcc.a[1] * 16.0 * G / 32768.0;
									carAcc.imuAz = stcAcc.a[2] * 16.0 * G / 32768.0;
									break;
			case 0x52: memcpy(&stcGyro, &jy61sData[2], 8); 
									carGyro.imuWx = stcGyro.w[0] * 2000.0 / 32768.0;
									carGyro.imuWy = stcGyro.w[1] * 2000.0 / 32768.0;
									carGyro.imuWz = stcGyro.w[2] * 2000.0 / 32768.0;
									break;
			case 0x53: memcpy(&stcAngle, &jy61sData[2], 8);
									carAngle.imuRollx = stcAngle.Angle[0] * 180.0 / 32768.0;
									carAngle.imuPitchy = stcAngle.Angle[1] * 180.0 / 32768.0;
									carAngle.imuYawz = stcAngle.Angle[2] * 180.0 / 32768.0;
									break;
			case 0x54: memcpy(&stcMag, &jy61sData[2], 8); 
									carMag.imuMagx = stcMag.h[0];
									carMag.imuMagy = stcMag.h[1];
									carMag.imuMagz = stcMag.h[2];
									break;
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

float getIMU_AngleZ(void)
{
	return carAngle.imuYawz;
}
