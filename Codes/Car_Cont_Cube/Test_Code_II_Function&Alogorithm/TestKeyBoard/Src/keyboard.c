/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "keyboard.h"
//Input PC0, PC1, PC2, PC3
//Output PC4, PC5, PB0, PB1

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
//Be called in every 50 ms.
uint8_t kbd_ScanValue(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_SET)
	{
		return 1;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET)
	{
		return 2;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_SET)
	{
		return 3;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == GPIO_PIN_SET)
	{
		return 0x0A;
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
	
	
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_SET)
	{
		return 4;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET)
	{
		return 5;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_SET)
	{
		return 6;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == GPIO_PIN_SET)
	{
		return 0x0B;
	}
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_RESET);
	
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_SET)
	{
		return 7;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET)
	{
		return 8;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_SET)
	{
		return 9;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == GPIO_PIN_SET)
	{
		return 0x0C;
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
	
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_SET);
	if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_0) == GPIO_PIN_SET)
	{
		return 0x1F;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1) == GPIO_PIN_SET)
	{
		return 0;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == GPIO_PIN_SET)
	{
		return 0X0E;
	}
	else if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == GPIO_PIN_SET)
	{
		return 0x0F;
	}
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
	
	return 0xFF;
}
