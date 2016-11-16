/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "encoderPID.h"
#include "tim.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static int32_t valEncoderL, valEncoderR;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void readEncoRAWData(void)
{
	valEncoderL = (int32_t)(__HAL_TIM_GET_COUNTER(&htim3));
	valEncoderR = (int32_t)(__HAL_TIM_GET_COUNTER(&htim4));
}
