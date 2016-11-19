/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "motor_cont.h"
#include "tim.h"
#include "encoderPID.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t forwardFlagL, forwardFlagR;
static uint16_t encoderPulse = 390 * 4; //Encoder maximum output.
static uint16_t minSpeed = 400; //Minimum speed.

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void car_Sleep(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET);
}

void car_Awake(void)
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET);
}

void car_Brake(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8 | GPIO_PIN_9, GPIO_PIN_RESET);
}

void car_FastDecay(void)
{
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_RESET);
}

void car_SetSpeedL(int32_t speedL)
{
	forwardFlagL = speedL > 0 ? SET : RESET;
	if(forwardFlagL == SET)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_11, GPIO_PIN_RESET);
	}
	
	speedL = speedL > 0 ? speedL : -speedL;
	speedL = speedL > encoderPulse ? encoderPulse : speedL;
	speedL = speedL < minSpeed ? minSpeed : speedL;
	
	htim2.Instance->CCR1 = speedL;
}

void car_SetSpeedR(int32_t speedR)
{
	forwardFlagR = speedR < 0 ? SET : RESET; //Filp motor connector.
	if(forwardFlagR == SET)
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
	}
	
	
	speedR = speedR > 0 ? speedR : -speedR;
	speedR = speedR > encoderPulse ? encoderPulse : speedR;
	speedR = speedR < minSpeed ? minSpeed : speedR;
	
	htim2.Instance->CCR2 = speedR;
}

uint8_t car_GetDirecL(void)
{
	return forwardFlagL;
}

uint8_t car_GetDirecR(void)
{
	return forwardFlagR;
}

void car_Turn(int32_t degree) //Cal?
{
	setTargetPos(degree, degree);
	clearEncoderFlag = SET;
}

void car_GoStraight(int32_t targetSpeed) //Speed = [21,100]
{
	//targetSpeed = [7,33](Oct)
	static float setSpeed = 0.0, calSpeed = 0.0;
	static int32_t tranSpeed = 0;
	
	setSpeed = (float)targetSpeed;
	setSpeed = setSpeed > 100.0 ? 100.0 : setSpeed;
	setSpeed = setSpeed < -100.0 ? -100.0 : setSpeed;
	
	calSpeed = setSpeed / 100.0 * 33.0;
	if(calSpeed > 0.0 && calSpeed < 7.0)
		calSpeed = 7.0;
	if(calSpeed < 0.0 && calSpeed > -7.0)
		calSpeed = -7.0;
	tranSpeed = (int32_t)calSpeed;
	
	setTargetSpeed(tranSpeed, tranSpeed);
}

void car_GoLength(int32_t targetLength) //PID
{
	setTargetPos(targetLength, targetLength);
	clearEncoderFlag = SET;
}
