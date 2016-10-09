/**
  ******************************************************************************
  * Motor Driver Pin Map
	* @Copyright Han ZHANG(haldak) | All rights reserved.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DRIVER_IO_CONF_H
#define __DRIVER_IO_CONF_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
		/*
		// Moyor driver pin definition
			//Left motor driver
				//Control line
				#define nFAULT_L	//PC0 - GPIO_EXTI0
				#define MODE1_L		//PC6
				#define MODE2_L		//PC8
				#define nSLEEP_L	//PB12
				#define Vpropi_L	//PA4 - ADC1_IN4

				//Signal line
				#define PHASE_L		//PA11
				#define ENABLE_L	//PA0 - TIM2_CH1

			//Right motor driver
				//Control line
				#define nFAULT_R	//PC1 - GPIO_EXTI1
				#define MODE1_R		//PC7
				#define MODE2_R		//PC9
				#define nSLEEP_R	//PC12
				#define Vpropi_R	//PA5 - ADC1_IN5

				//Signal line
				#define PHASE_R		//PA12
				#define ENABLE_R	//PA1 - TIM2_CH2
		*/

/* Exported functions ------------------------------------------------------- */

#endif /* __DRIVER_IO_CONF_H */
