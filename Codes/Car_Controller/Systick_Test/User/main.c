/**
  ******************************************************************************
  * ����������
	* @Copyright Han ZHANG(haldak) @ Wenhao DING(Gilgamesh) | All rights reserved.
	* �廪��ѧ����ϵӲ���� & δ��ͨ����Ȥ�Ŷ�
	* Ӳ����ƴ���
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "port.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int main(void)
{
	//Start with board specific hardware init.
	Our_Sys_Init();
	
	GPIO_SetBits(GPIOD, GPIO_Pin_2);

	//Infinite loop to deal with your project.
	while(1)
	{
		
	}
}
