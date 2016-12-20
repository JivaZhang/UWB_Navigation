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
#define PWN_NORMALIZED		100

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static float targetAngle = 0;
static int32_t setSpeedL = 0, setSpeedR = 0;
uint8_t turnAngleStableFlag = SET;

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
	static float Ek = 0.0, Ek1 = 0.0, sigmaEk = 0.0, PWM = 0.0, tempDiff = 0.0;
	static float temp1, temp2;
//	static int32_t tempInt1, tempInt2;
	static uint8_t tempCnt = 0;
	
	temp1 = getIMU_AngleZ();
//	tempInt1 = (int32_t)temp1;
	
	temp2 = targetAngle;
//	tempInt2 = (int32_t)temp2;
	
	Ek = -temp1 + temp2;
	if(Ek > 180)
			Ek -= 360;
	else if(Ek < -180)
			Ek += 360;
	sigmaEk += Ek;
	PWM = Kp * Ek + Ki * sigmaEk + Kd * (Ek - Ek1);
	
	tempDiff = Ek - Ek1;
	tempDiff = tempDiff<0 ? -tempDiff : tempDiff;
	if(tempDiff < 0.05)
	{
		tempCnt++;
		if(tempCnt == 50)
		{
			tempCnt = 0;
			turnAngleStableFlag >>= 4;
		}
	}
	
	Ek1 = Ek;
	
	PWM = PWM>PWN_NORMALIZED ? PWN_NORMALIZED : PWM;
	PWM = PWM<-PWN_NORMALIZED ? -PWN_NORMALIZED : PWM;
	
	setSpeedL = 390 * 4 * -PWM / PWN_NORMALIZED;
	setSpeedR = 390 * 4 * PWM / PWN_NORMALIZED;
}

void contSpeedPWMimu(void)
{
	car_SetSpeedL(setSpeedL);
	car_SetSpeedR(setSpeedR);
}

void turnPIDCont(void) //Be called in every 100ms.
{
	positionPID();
	contSpeedPWMimu();
}
