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
static int32_t setSpeedL = 0, setSpeedR = 0;
uint8_t clearEncoderFlag = RESET, turnStableFlag = SET;

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

//PWM = Kp * e(k) + Ki * ¡Æe(k) + Kd * [e(k) - e(k-1)]
int32_t positionPIDL(int32_t encoderPosL, int32_t targetPosL)
{ 	
	static float Kp = 0.7, Ki = 0.0001, Kd = 0.15;
	static float Ek = 0.0, Ek1 = 0.0, sigmaEk = 0.0, PWML = 0.0;
	static int32_t temp;
	static uint8_t tempCnt = 0;
	temp = -encoderPosL + targetPosL;
	Ek = (float)temp;
	sigmaEk += Ek;
	PWML = Kp * Ek + Ki * sigmaEk + Kd * (Ek - Ek1);
//	if(Ek == Ek1)
//	{
//		tempCnt++;
//		if(tempCnt == 30)
//		{
//			tempCnt = 0;
//			turnStableFlag >>= 4;
//		}
//	}
	Ek1 = Ek;
//	PWML = PWML > 500 ? 500 : PWML;
//	PWML = PWML < -500 ? -500 : PWML;
	return (int32_t)PWML;
}

//PWM = Kp * e(k) + Ki * ¡Æe(k) + Kd * [e(k) - e(k-1)]
int32_t positionPIDR(int32_t encoderPosR, int32_t targetPosR)
{ 	
	static float Kp = 0.7, Ki = 0.0001, Kd = 0.15;
	static float Ek = 0.0, Ek1 = 0.0, sigmaEk = 0.0, PWMR = 0.0;
	static int32_t temp;
	static uint8_t tempCnt = 0;
	temp = -encoderPosR + targetPosR;
	Ek = (float)temp;
	sigmaEk += Ek;
	PWMR = Kp * Ek + Ki * sigmaEk + Kd * (Ek - Ek1);
//	if(Ek == Ek1)
//	{
//		tempCnt++;
//		if(tempCnt == 30)
//		{
//			tempCnt = 0;
//			turnStableFlag >>= 4;
//		}
//	}
	Ek1 = Ek;
//	PWMR = PWMR > 500 ? 500 : PWMR;
//	PWMR = PWMR < -500 ? -500 : PWMR;
	return (int32_t)PWMR;
}

//PWM += Kp * [e(k) - e(k-1)] + Ki * e(k) + Kd * [e(k) - 2 * e(k-1) + e(k-2)]
int32_t incrementalPIDL(int32_t encoderDiffPulseL, int32_t targetSpeedL)
{ 	
	static float Kp = 70.7, Ki = 0.1, Kd = 0.01;
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
	static float Kp = 70.7, Ki = 0.1, Kd = 0.01;
	static float Ek = 0.0, Ek1 = 0.0, Ek2 = 0.0, PWMR = 0.0;
	static int32_t temp;
	temp = -encoderDiffPulseR + targetSpeedR;
	Ek = (float)temp;
	PWMR += Kp * (Ek - Ek1) + Ki * Ek + Kd * (Ek - 2 * Ek1 + Ek2);
	Ek2 = Ek1;
	Ek1 = Ek;
	return (int32_t)PWMR;
}

void straightPIDConstraint(void) //A same speed constraint for going straight. Be called in every 100ms.
{
	//PWM += Kp * [e(k) - e(k-1)] + Ki * e(k) + Kd * [e(k) - 2 * e(k-1) + e(k-2)]
	static int32_t encoderDiffL = 0, encoderDiffR = 0, encoderDiffLR = 0;
	static float Kp = 177.7, Ki = 1.57, Kd = 0.007;
	static float Ek = 0.0, Ek1 = 0.0, Ek2 = 0.0, deltaPWM = 0.0;
	encoderDiffL = getEncoderDiffL();
	encoderDiffR = getEncoderDiffR();
	encoderDiffLR = encoderDiffL - encoderDiffR;
	
	Ek = -(float)encoderDiffLR;
	deltaPWM += Kp * (Ek - Ek1) + Ki * Ek + Kd * (Ek - 2 * Ek1 + Ek2);
	Ek2 = Ek1;
	Ek1 = Ek;
	
	setSpeedL += (int32_t)(deltaPWM / 2.0);
	setSpeedR -= (int32_t)(deltaPWM / 2.0);
}

void contSpeedPWM(void)
{
//	car_SetSpeedL(setSpeedL*0.92);
	car_SetSpeedL(setSpeedL);
	car_SetSpeedR(setSpeedR);
}


void movementPIDCont(void) //Be called in every 100ms.
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
//	setSpeedL = turnStableFlag ? pidSpeedPosL : pidSpeedIncL;
	setSpeedL = pidSpeedPosL;
	
	pidSpeedIncR = incrementalPIDR(encoderDiffR, targetSpeedR);
	pidSpeedPosR = positionPIDR(positionR, targetPosR);
//	setSpeedR = turnStableFlag ? pidSpeedPosR : pidSpeedIncR;
	setSpeedR = pidSpeedPosR;
//	if(turnStableFlag == 0)
//		straightPIDConstraint();
	
	contSpeedPWM();
}
