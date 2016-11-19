/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __sMOTORCONT_H
#define __sMOTORCONT_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void car_Sleep(void);
void car_Awake(void);
void car_Brake(void);
void car_FastDecay(void);
void car_SetSpeedL(int32_t speedL);
void car_SetSpeedR(int32_t speedR);
uint8_t car_GetDirecL(void);
uint8_t car_GetDirecR(void);
void car_Turn(int32_t thetaTurn);
uint8_t ifTurnStable(void);
void car_GoStraight(int32_t targetSpeed);
void car_GoLength(int32_t targetLength);

#endif /* __sMOTORCONT_H */
