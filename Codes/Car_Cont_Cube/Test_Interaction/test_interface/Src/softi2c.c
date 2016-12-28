/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "softi2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define SCL_High()	{GPIOA->BSRR = (uint32_t)GPIO_PIN_9;}
#define SCL_Low()		{GPIOA->BRR = (uint32_t)GPIO_PIN_9;}
#define SDA_High()	{GPIOA->BSRR = (uint32_t)GPIO_PIN_10;}
#define SDA_Low()		{GPIOA->BRR = (uint32_t)GPIO_PIN_10;}

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t softTick;
uint8_t digitalNumber[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x80};

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void DelayUS(uint32_t delayTimeUS)
{
	static uint32_t told = 0, tnow = 0, tcnt = 0, reload = 0, ticks = 0;
	tcnt = 0;
	told = SysTick->VAL;
	reload = SysTick->LOAD;
	ticks = delayTimeUS * (SystemCoreClock / 1000000.0);
	while(1)
	{
		tnow = SysTick->VAL;
		if(tnow != told)
		{
			if(tnow > told)//counter up mode
			{
				tcnt += tnow - told;
			}
			else//reload mode
			{
				tcnt += tnow + reload - told;
			}
			told = tnow;
			
			if(tcnt >= ticks)
			{
				break;
			}
		}
	}
}

GPIO_PinState SDA_Read(void)
{
  if ((GPIOA->IDR & GPIO_PIN_10) != (uint32_t)GPIO_PIN_RESET)
  {
    return GPIO_PIN_SET;
  }
  return GPIO_PIN_RESET;
}

void soft_I2CStart(void)
{
	SCL_High();
	SDA_High();
	DelayUS(2);
	SDA_Low();
}

void soft_I2CACK(void)
{
	SCL_Low();
	DelayUS(5);
	while(SDA_Read() == GPIO_PIN_SET) {}
	SCL_High();
	DelayUS(2);
	SCL_Low();
}

void soft_I2CStop(void)
{
	SCL_Low();
	DelayUS(2);
	SDA_Low();
	DelayUS(2);
	SCL_High();
	DelayUS(2);
	SDA_High();
}

void soft_I2CWrByte(uint8_t data)
{
	static uint8_t i;
	for(i = 0; i < 8; i++)
	{
		SCL_Low();
		if(data & 0x01)
		{
			SDA_High();
		}
		else
		{
			SDA_Low();
		}
		DelayUS(3);
		data >>= 1;
		SCL_High();
		DelayUS(3);
	}
}

void soft_SmgDisplay(void)
{
	static uint8_t i;
	soft_I2CStart();
	soft_I2CWrByte(0x40);
	soft_I2CACK();
	soft_I2CStop();
	
	soft_I2CStart();
	soft_I2CWrByte(0xC0);
	soft_I2CACK();
	for(i = 0; i < 4; i++)
	{
		soft_I2CWrByte(digitalNumber[0]);
		soft_I2CACK();
	}
	soft_I2CStop();
	
	soft_I2CStart();
	soft_I2CWrByte(0x8F);
	soft_I2CACK();
	soft_I2CStop();
}
