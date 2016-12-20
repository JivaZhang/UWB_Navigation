/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __sIMUPID_H
#define __sIMUPID_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __sIMUPID_H */
void car_Turnto(float angle); //-180~+180
void turnPIDCont(void); //Be called in every 100ms.
