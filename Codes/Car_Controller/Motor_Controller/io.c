/**
  ******************************************************************************
  * 电机驱动io控制
  * @Copyright Han ZHANG(haldak) | All rights reserved.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "io.h"
#include "Driver_IO_Conf.h"
#include "HanLib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void MotorDriver_Init (void)
{
	//Left motor driver
		//Control line
			/* nFAULT_L			PC0 - GPIO_EXTI0 */
			han_GPIO_Set (GPIOC, GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);	

			/* MODE1_L			PC6 */
			han_GPIO_Set (GPIOC, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

			/* MODE2_L			PC8 */
			han_GPIO_Set (GPIOC, GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);	
			
			/* nSLEEP_L			PB12 */
			han_GPIO_Set (GPIOB, GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
		
		//Signal line
			/* PHASE_L			PA11 */
			han_GPIO_Set (GPIOA, GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
			
			/* ENABLE_L			PA0 - TIM2_CH1 */
			han_GPIO_Set (GPIOA, GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
		
	//Right motor driver
		//Control line
			/* nFAULT_R			PC1 - GPIO_EXTI1 */
			han_GPIO_Set (GPIOC, GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);	

			/* MODE1_R			PC7 */
			han_GPIO_Set (GPIOC, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

			/* MODE2_R			PC9 */
			han_GPIO_Set (GPIOC, GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);	
			
			/* nSLEEP_R			PC12 */
			han_GPIO_Set (GPIOC, GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
		
		//Signal line
			/* PHASE_R			PA12 */
			han_GPIO_Set (GPIOA, GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
			
			/* ENABLE_R			PA1	- TIM2_CH2 */
			han_GPIO_Set (GPIOA, GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
}

void Encoder_Init (void)
{
	//Left Encoder
		/* A_L			PA6 - TIM3_CH1 */
		han_GPIO_Set (GPIOA, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
	
		/* B_L			PA7 - TIM3_CH2 */
		han_GPIO_Set (GPIOA, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
	
	//Right Encoder
		/* A_R			PB6 - TIM4_CH1 */
		han_GPIO_Set (GPIOB, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
	
		/* B_R			PB7 - TIM4_CH2 */
		han_GPIO_Set (GPIOB, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_AF_PP);
}

void PWM_Timer2_Init (void)
{
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE);	//Enable the clock for TIM2
	
}

void Encoder_L_Timer3_Init (void)
{
	
}

void Encoder_R_Timer4_Init (void)
{
	
}
