/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "imuPID.h"
#include "parseJY.h"
#include "motor_cont.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static float targetAngle = 0;
static int32_t setSpeedL = 0, setSpeedR = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void setTargetAngle(float angle)
{
	targetAngle = angle;
}

//PWM = Kp * e(k) + Ki * ¡Æe(k) + Kd * [e(k) - e(k-1)]
void positionPID()
{ 	
	static float Kp = 1.1, Ki = 0.0001, Kd = 15.55;
	static float Ek = 0.0, Ek1 = 0.0, sigmaEk = 0.0, PWM = 0.0;
	static float temp1, temp2;
	temp1 = getIMU_AngleZ();
	temp2 = targetAngle;
	Ek = -temp1 + temp2;
	sigmaEk += Ek;
	PWM = Kp * Ek + Ki * sigmaEk + Kd * (Ek - Ek1);
	Ek1 = Ek;
	
	PWM = PWM>100 ? 100 : PWM;
	PWM = PWM<-100 ? -100 : PWM;
	
	setSpeedL = 390 * 4 * -PWM / 100.0;
	setSpeedR = 390 * 4 * PWM / 100.0;
}

void contSpeedPWM(void)
{
	car_SetSpeedL(setSpeedL);
	car_SetSpeedR(setSpeedR);
}

void turnPIDCont(void) //Be called in every 100ms.
{
	positionPID();
	contSpeedPWM();
}

//test turn angle
void car_Turnto(float angle) //-180~+180
{
	setTargetAngle(angle);
}
