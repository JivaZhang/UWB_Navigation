/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __sPARSEJY_H
#define __sPARSEJY_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
struct STime
{
	unsigned char ucYear;
	unsigned char ucMonth;
	unsigned char ucDay;
	unsigned char ucHour;
	unsigned char ucMinute;
	unsigned char ucSecond;
	unsigned short usMiliSecond;
};

struct SAcc
{
	short a[3];
	short T;
};

struct SGyro
{
	short w[3];
	short T;
};

struct SAngle
{
	short Angle[3];
	short T;
};

struct SMag
{
	short h[3];
	short T;
};

struct SDStatus
{
	short sDStatus[4];
};

struct SPress
{
	long lPressure;
	long lAltitude;
};

struct SLonLat
{
	long lLon;
	long lLat;
};

struct SGPSV
{
	short sGPSHeight;
	short sGPSYaw;
	long lGPSVelocity;
};

/* Exported constants --------------------------------------------------------*/
extern uint8_t jy61sData[];
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void parseJY_DMA_Data(void);

#endif /* __sPARSEJY_H */
