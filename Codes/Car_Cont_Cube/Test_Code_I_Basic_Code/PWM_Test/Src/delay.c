/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "delay.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t sTick;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

//Call for Systick IRQ Handler
//Overwrite weak definition in stm32f1xx_hal.c

void DecTick(void)
{
	if (sTick != 0)
	{
		sTick--;
	}
}

uint32_t GetTick(void)
{
	return sTick;
}

void SetTick(uint32_t setTick)
{
	sTick = setTick;
}

void DelayMS(uint32_t delayTimeMS)
{
	SetTick(delayTimeMS);
	while (GetTick() != 0);
}
