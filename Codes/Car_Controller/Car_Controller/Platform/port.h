/**
  ******************************************************************************
  * 接口定义
	* @Copyright Han ZHANG(haldak) | All rights reserved.
  ******************************************************************************
  */

#ifndef PORT_H_
#define PORT_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

#ifdef _MSC_VER //stdint.h patch for vs2015
#include "VSPatch.h"
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

//For Systick
#define CLOCKS_PER_SEC					1000

/* Exported functions ------------------------------------------------------- */
//Periph Init
void Our_Sys_Init(void);
	
void TimingDelay_Decrement(void);
void Delay(__IO uint32_t nTime);

#ifdef __cplusplus
}
#endif

#endif /* PORT_H_ */
