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
void han_GPIO_Set(GPIO_TypeDef* GPIOx, \
	u16 GPIO_Pin, \
	GPIOSpeed_TypeDef GPIO_Speed, \
	GPIOMode_TypeDef GPIO_Mode);

void han_Timer_PWM_Opt(TIM_TypeDef* TIMx, \
	u16 PWM_Period, \
	u8 Channel_Number, \
	u8* Channel_Ptr);

void han_NVIC_Set(IRQn_Type IRQn, \
	u8 Preeption, \
	u8 Sub);

void han_Timer_Encoder(TIM_TypeDef* TIMx, \
	u16 LineNumber, \
	u16 CatchAngle);

void han_EXTI_Set(uint32_t EXTI_Line, \
	EXTIMode_TypeDef EXTI_Mode, \
	EXTITrigger_TypeDef EXTI_Trigger, \
	FunctionalState EXTI_LineCmd);

u8 han_Get_Counter_Direction(TIM_TypeDef* TIMx);

#endif /* __HANLIB_H */
