/**
  ******************************************************************************
  * This is Han's private STM32-F1 developping lib.
	* Including the algorithms and functions Han needs.
	* @Version 1.0 - STM32F1Lib
	* @Copyright Han ZHANG(haldak) | All rights reserved.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "HanLib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void han_GPIO_Set	(GPIO_TypeDef* GPIOx, \
										u16 GPIO_Pin, \
										GPIOSpeed_TypeDef GPIO_Speed, \
										GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
	
	GPIO_Init	(GPIOx, &GPIO_InitStructure);
}
