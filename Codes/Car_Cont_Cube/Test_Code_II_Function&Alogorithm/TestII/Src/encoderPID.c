/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "encoderPID.h"
#include "tim.h"
#include "motor_cont.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static int32_t valEncoderL = 0, valEncoderR = 0; //, saveEncoderL = 0, saveEncoderR = 0;
static int32_t positionL = 0, positionR = 0;
static int32_t targetSpeedL = 0, targetSpeedR = 0;
static int32_t targetPosL = 0, targetPosR = 0;
uint8_t clearEncoderFlag = RESET;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void readEncoRAWData(void)
{
	//saveEncoderL = valEncoderL;
	//saveEncoderR = valEncoderR;
	valEncoderL = (int32_t)(__HAL_TIM_GET_COUNTER(&htim3));
	valEncoderR = (int32_t)(__HAL_TIM_GET_COUNTER(&htim4));
	__HAL_TIM_SET_COUNTER(&htim3, 5000);
	__HAL_TIM_SET_COUNTER(&htim4, 5000);
}

int32_t getEncoderDiffL(void)
{
	return valEncoderL - 5000; // - saveEncoderL;
}	

int32_t getEncoderDiffR(void)
{
	return valEncoderR - 5000; // - saveEncoderR;
}

void setTargetSpeed(int32_t speedL, int32_t speedR)
{
	targetSpeedL = speedL;
	targetSpeedR = speedR;
}

void setTargetPos(int32_t posL, int32_t posR)
{
	targetPosL = posL;
	targetPosR = posR;
}

//PWM += Kp * [e(k) - e(k-1)] + Ki * e(k) + Kd * [e(k) - 2 * e(k-1) + e(k-2)]
int32_t incrementalPIDL(int32_t encoderDiffPulseL, int32_t targetSpeedL)
{ 	
	static float Kp = 1.1, Ki = 0.0005, Kd = 0.01;
	static float Ek = 0.0, Ek1 = 0.0, Ek2 = 0.0, PWML = 0.0;
	static int32_t temp;
	temp = -encoderDiffPulseL + targetSpeedL;
	Ek = (float)temp;
	PWML += Kp * (Ek - Ek1) + Ki * Ek + Kd * (Ek - 2 * Ek1 + Ek2);
	Ek2 = Ek1;
	Ek1 = Ek;
	return (int32_t)PWML;
}

//PWM += Kp * [e(k) - e(k-1)] + Ki * e(k) + Kd * [e(k) - 2 * e(k-1) + e(k-2)]
int32_t incrementalPIDR(int32_t encoderDiffPulseR, int32_t targetSpeedR)
{ 	
	static float Kp = 1.1, Ki = 0.0005, Kd = 0.01;
	static float Ek = 0.0, Ek1 = 0.0, Ek2 = 0.0, PWMR = 0.0;
	static int32_t temp;
	temp = -encoderDiffPulseR + targetSpeedR;
	Ek = (float)temp;
	PWMR += Kp * (Ek - Ek1) + Ki * Ek + Kd * (Ek - 2 * Ek1 + Ek2);
	Ek2 = Ek1;
	Ek1 = Ek;
	return (int32_t)PWMR;
}


//PWM = Kp * e(k) + Ki * ¡Æe(k) + Kd * [e(k) - e(k-1)]
int32_t positionPIDL(int32_t encoderPosL, int32_t targetPosL)
{ 	
	static float Kp = 3.7, Ki = 0.0, Kd = 2.7;
	static float Ek = 0.0, Ek1 = 0.0, sigmaEk = 0.0, PWML = 0.0;
	static int32_t temp;
	temp = -encoderPosL + targetPosL;
	Ek = (float)temp;
	sigmaEk += Ek;
	PWML = Kp * Ek + Ki * sigmaEk + Kd * (Ek - Ek1);
	Ek1 = Ek;
	return (int32_t)PWML;
}

//PWM = Kp * e(k) + Ki * ¡Æe(k) + Kd * [e(k) - e(k-1)]
int32_t positionPIDR(int32_t encoderPosR, int32_t targetPosR)
{ 	
	static float Kp = 3.7, Ki = 0.0, Kd = 2.7;
	static float Ek = 0.0, Ek1 = 0.0, sigmaEk = 0.0, PWMR = 0.0;
	static int32_t temp;
	temp = -encoderPosR + targetPosR;
	Ek = (float)temp;
	sigmaEk += Ek;
	PWMR = Kp * Ek + Ki * sigmaEk + Kd * (Ek - Ek1);
	Ek1 = Ek;
	return (int32_t)PWMR;
}

void movementPIDCont(void) //Be called in every 10ms.
{
	static int32_t encoderDiffL = 0, encoderDiffR = 0;
	static int32_t pidSpeedIncL = 0, pidSpeedIncR = 0;
	static int32_t pidSpeedPosL = 0, pidSpeedPosR = 0;
	
	encoderDiffL = getEncoderDiffL();
	positionL += encoderDiffL;
	encoderDiffR = getEncoderDiffR();
	positionR += encoderDiffR;
	
	if(clearEncoderFlag == SET)
	{
		clearEncoderFlag = RESET;
		positionL = 0;
		positionR = 0;
	}
	
	pidSpeedIncL = incrementalPIDL(encoderDiffL, targetSpeedL);
	pidSpeedPosL = positionPIDL(positionL, targetPosL);
	car_SetSpeedL(pidSpeedPosL);
	
	pidSpeedIncR = incrementalPIDR(encoderDiffR, targetSpeedR);
	pidSpeedPosR = positionPIDR(positionR, targetPosR);
	car_SetSpeedR(pidSpeedPosR);
}
