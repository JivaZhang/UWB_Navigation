/**
  ******************************************************************************
  * 电机驱动头文件定义
	* @Copyright Han ZHANG(haldak) | All rights reserved.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DRIVER_H
#define __DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
// Moyor driver pin definition
	//Left motor driver
		//Control line
		#define nFAULT_L
		#define MODE1_L
		#define MODE2_L
		#define nSLEEP_L
		#define Vpropi_L

		//Signal line
		#define PHASE_L
		#define ENABLE_L

	//Right motor driver
		//Control line
		#define nFAULT_R
		#define MODE1_R
		#define MODE2_R
		#define nSLEEP_R
		#define Vpropi_R

		//Signal line
		#define PHASE_R
		#define ENABLE_R

/* Exported functions ------------------------------------------------------- */

#endif /* __DRIVER_H */
