/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "parseJY.h"
#include "string.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t jy61sData[11];

struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void parseJY_DMA_Data(void) //Be called when DMA interrupt.
{
	switch(jy61sData[1])
	{
			case 0x50: memcpy(&stcTime,&jy61sData[2], 8); break;
			case 0x51: memcpy(&stcAcc,&jy61sData[2], 8); break;
			case 0x52: memcpy(&stcGyro,&jy61sData[2], 8); break;
			case 0x53: memcpy(&stcAngle,&jy61sData[2], 8); break;
			case 0x54: memcpy(&stcMag,&jy61sData[2], 8); break;
			case 0x55: memcpy(&stcDStatus,&jy61sData[2], 8); break;
			case 0x56: memcpy(&stcPress,&jy61sData[2], 8); break;
			case 0x57: memcpy(&stcLonLat,&jy61sData[2], 8); break;
			case 0x58: memcpy(&stcGPSV,&jy61sData[2], 8); break;
	}
}
