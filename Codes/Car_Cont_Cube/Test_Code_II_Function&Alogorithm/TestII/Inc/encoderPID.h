/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __sENCODERPID_H
#define __sENCODERPID_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void readEncoRAWData(void);
void movementPIDCont(void);
void setTargetSpeed(int32_t speedL, int32_t speedR);
void setTargetPos(int32_t posL, int32_t posR);

#endif /* __sENCODERPID_H */
