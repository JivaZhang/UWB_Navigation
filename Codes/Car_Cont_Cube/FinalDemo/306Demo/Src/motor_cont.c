/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "motor_cont.h"
#include "tim.h"
#include "encoderPID.h"
#include "imuPID.h"
#include "delay.h"
#include "parseJY.h"

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
	if(speedL != 0)
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
	if(speedR != 0)
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

//void car_Turn(int32_t thetaTurn) //Cal -> thetaWheel = 2.25 * thetaTurn
//{
//	static int32_t thetaWheelL = 0, thetaWheelR = 0;
//	thetaTurn = thetaTurn % 360;
//	thetaWheelL = 2.1 * thetaTurn;
//	thetaWheelR = -2.1 * thetaTurn;
//	thetaWheelL = thetaWheelL * encoderPulse / 360.0;
//	thetaWheelR = thetaWheelR * encoderPulse / 360.0;
//	setTargetPos(thetaWheelL, thetaWheelR);
//	clearEncoderFlag = SET;
//	turnStableFlag = 0xEE;
//}

void car_Turn(int32_t angle) //-180~+180
{
	//Get angle now.
	static float angleNow = 0.0, angleTurn = 0.0, angleSet = 0.0;
	static int32_t angleTemp = 0;
	angleTurn = (float)angle;
	angleNow = getIMU_AngleZ() + 180.0; //0.0~360.0
	
	angleSet = angleNow + angleTurn;
	angleTemp = (int32_t)angleSet;
	angleTemp %= 360;
	angleTemp -= 180;
	angleSet = (float)angleTemp;
	
	setTargetAngle(angleSet);
	turnAngleStableFlag = 0x0F;
}

void car_Turnto(float angle) //-180~+180
{
	setTargetAngle(angle);
	turnAngleStableFlag = 0x0F;
}

void car_GoLength(int32_t targetLength) //PID
{
	setTargetPos(targetLength, targetLength);
	clearEncoderFlag = SET;
	turnStableFlag = 0xFF;
	saveIMUAngleZ = getIMU_AngleZ();
}

uint8_t ifTurnStable(void)
{
//	turnStableFlag = 0xFF;
//	DelayMS(50);
	return turnStableFlag;
}

uint8_t ifTurnToStable(void)
{
	return turnAngleStableFlag;
}

void car_GoStraight(int32_t targetSpeed) //Speed range: [0,121]
{
//	//targetSpeed = [28,121](Oct)
	static float maxEncoSpeed = 121.0, minEncoSpeed = 28.0;
	static float setSpeed = 0.0;
	static int32_t tranSpeed = 0;

	setSpeed = (float)targetSpeed;
	setSpeed = setSpeed > maxEncoSpeed ? maxEncoSpeed : setSpeed;
	setSpeed = setSpeed < -maxEncoSpeed ? -maxEncoSpeed : setSpeed;
	
	if(setSpeed > 0.0 && setSpeed < minEncoSpeed)
		setSpeed = minEncoSpeed;
	if(setSpeed < 0.0 && setSpeed > -minEncoSpeed)
		setSpeed = -minEncoSpeed;
	tranSpeed = (int32_t)setSpeed;
	
	saveIMUAngleZ = getIMU_AngleZ();
	setTargetSpeed(tranSpeed, tranSpeed);
}

void car_Stop(void)
{
	setTargetSpeed(0, 0);
	setTargetPos(0, 0);
	clearEncoderFlag = SET;
	car_SetSpeedL(0);
	car_SetSpeedR(0);
}
