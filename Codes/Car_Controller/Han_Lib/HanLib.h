/**
  ******************************************************************************
  * Header file for HanLib.c
	* @Version 1.0 - STM32F1Lib
	* @Copyright Han ZHANG(haldak) | All rights reserved.
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HANLIB_H
#define __HANLIB_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void han_GPIO_Set	(GPIO_TypeDef* GPIOx, \
										u16 GPIO_Pin, \
										GPIOSpeed_TypeDef GPIO_Speed, \
										GPIOMode_TypeDef GPIO_Mode);

#endif /* __HANLIB_H */
