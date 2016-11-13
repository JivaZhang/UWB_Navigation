/**
  ******************************************************************************
  * 电机驱动io控制
	* @Copyright Han ZHANG(haldak) | All rights reserved.
  ******************************************************************************
  */
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __IO_DRIVER_H
#define __IO_DRIVER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
//void TIM3_IRQHDL(void);
//void TIM4_IRQHDL(void);
void TIM5_IRQHDL(void);
void Motor_Move_Controller(void);

void IO_Init(void);
#endif /* __IO_DRIVER_H */
