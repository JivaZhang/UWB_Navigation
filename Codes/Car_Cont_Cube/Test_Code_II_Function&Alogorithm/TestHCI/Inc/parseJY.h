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
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void initJY(void);
void receiveJY_DMA_Data(void);
float getIMU_AngleZ(void);

#endif /* __sPARSEJY_H */
