/**
******************************************************************************
* 电机驱动io控制
* @Copyright Han ZHANG(haldak) | All rights reserved.
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "io.h"
#include "HanLib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint16_t PWM_Period = 1000; //PWM Max Value

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
//Motor Driver
void MotorDriver_Init(void)
{
	//Left motor driver
	//Control line
	/* nFAULT_L			PC0 - GPIO_EXTI0 */
	han_GPIO_Set(GPIOC, GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_IPU);

	/* MODE1_L			PC6 */
	han_GPIO_Set(GPIOC, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	/* MODE2_L			PC8 */
	han_GPIO_Set(GPIOC, GPIO_Pin_8, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	/* nSLEEP_L			PB12 */
	han_GPIO_Set(GPIOB, GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	//Signal line
	/* PHASE_L			PA11 */
	han_GPIO_Set(GPIOA, GPIO_Pin_11, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	/* ENABLE_L			PA0 - TIM2_CH1 */
	han_GPIO_Set(GPIOA, GPIO_Pin_0, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	//Right motor driver
	//Control line
	/* nFAULT_R			PC1 - GPIO_EXTI1 */
	han_GPIO_Set(GPIOC, GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_IPU);

	/* MODE1_R			PC7 */
	han_GPIO_Set(GPIOC, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	/* MODE2_R			PC9 */
	han_GPIO_Set(GPIOC, GPIO_Pin_9, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	/* nSLEEP_R			PC12 */
	han_GPIO_Set(GPIOC, GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	//Signal line
	/* PHASE_R			PA12 */
	han_GPIO_Set(GPIOA, GPIO_Pin_12, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);

	/* ENABLE_R			PA1	- TIM2_CH2 */
	han_GPIO_Set(GPIOA, GPIO_Pin_1, GPIO_Speed_50MHz, GPIO_Mode_Out_PP);
}

void PWM_Timer2_Init(void)
{
	//Initialize TIM2_CH1 & TIM2_CH2
	u8 Channel_slc[2] = { 1, 2 };
	han_Timer_PWM_Opt(TIM2, PWM_Period, 2, Channel_slc);
}

void nFAULT_EXTI_Init(void)
{
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource1);

	han_EXTI_Set(GPIO_PinSource0, EXTI_Mode_Interrupt, EXTI_Trigger_Falling, ENABLE);
	han_EXTI_Set(GPIO_PinSource1, EXTI_Mode_Interrupt, EXTI_Trigger_Falling, ENABLE);

	han_NVIC_Set(EXTI0_IRQn, 3, 3);
	han_NVIC_Set(EXTI1_IRQn, 3, 3);
}

//Encoder
void Encoder_Init(void)
{
	//Left Encoder
	/* A_L			PA6 - TIM3_CH1 */
	han_GPIO_Set(GPIOA, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);

	/* B_L			PA7 - TIM3_CH2 */
	han_GPIO_Set(GPIOA, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);

	//Right Encoder
	/* A_R			PB6 - TIM4_CH1 */
	han_GPIO_Set(GPIOB, GPIO_Pin_6, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);

	/* B_R			PB7 - TIM4_CH2 */
	han_GPIO_Set(GPIOB, GPIO_Pin_7, GPIO_Speed_50MHz, GPIO_Mode_IN_FLOATING);
}

void Encoder_L_Timer3_Init(void)
{
	han_NVIC_Set(TIM4_IRQn, 2, 3);
	han_Timer_Encoder(TIM3, 390, 30);
}

void Encoder_R_Timer4_Init(void)
{
	han_NVIC_Set(TIM4_IRQn, 2, 3);
	han_Timer_Encoder(TIM4, 390, 30); 	
}

void TIM3_IRQHDL(void)
{
	u16 arr_calc = (u16)((double)390 * (double)30 / 360.0);
	//TIM_GetCounter(TIM3);
	//han_Get_Counter_Direction(TIM3);
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		TIM_SetCounter(TIM3, arr_calc * 4 - 1);//Reset counter to middle position

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}

void TIM4_IRQHDL(void)
{
	u16 arr_calc = (u16)((double)390 * (double)30 / 360.0);
	//TIM_GetCounter(TIM4);
	//han_Get_Counter_Direction(TIM4);
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	{
		TIM_SetCounter(TIM4, arr_calc * 4 - 1);//Reset counter to middle position

		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
	}
}

void IO_Init(void)
{
	MotorDriver_Init();
	PWM_Timer2_Init();
	/*nFAULT_EXTI_Init();*/

	Encoder_Init();
	Encoder_L_Timer3_Init();
	Encoder_R_Timer4_Init();
}
