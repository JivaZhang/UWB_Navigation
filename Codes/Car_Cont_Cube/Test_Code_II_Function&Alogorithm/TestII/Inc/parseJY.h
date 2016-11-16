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

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void initJY(void);
void receiveJY_DMA_Data(void);

#endif /* __sPARSEJY_H */
