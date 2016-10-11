/**
******************************************************************************
* This is Han's private STM32-F1 developping lib.
* Including the algorithms Han needs.
* @Version 1.0 - STM32F1Lib
* @Copyright Han ZHANG(haldak) | All rights reserved.
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "HanAlgorithm.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/*
	Discrete Position PID Controller
	Using equation below
	Pwm = Kp * e(k) + Ki * Sum(e(k)) + Kd * [e(k) - e(k-1)]
*/
u32 han_Position_PID(double Kp, double Ki, double Kd, u32 Error, u32* SumEk, u32* Ek1)
{
	double Pwm;
	*SumEk += Error;
	Pwm = Kp * Error + Ki * (*SumEk) + Kd * (Error - (*Ek1));
	*Ek1 = Error;
	return (u32)Pwm;
}

/*
	Discrete Incremental PID controller
	using equation below
	Pwm += Kp * [e(k) - e(k-1)] + Ki * e(k) + Kd * [e(k)- 2 * e(k-1) + e(k-2)]
*/
void han_Incremental_PID(double Kp, double Ki, double Kd, u32* Pwm, u32 Error, u32* Ek1, u32* Ek2)
{
	*Pwm = *Pwm + Kp * (Error - (*Ek1)) + Ki * Error + Kd * (Error - 2 * (*Ek1) + (*Ek2));
	*Ek2 = *Ek1;
	*Ek1 = Error;
}
