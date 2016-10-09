/**
******************************************************************************
* This is Han's private STM32-F1 developping lib.
* Including the functions Han needs.
* @Version 1.0 - STM32F1Lib
* @Copyright Han ZHANG(haldak) | All rights reserved.
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "HanLib.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void han_GPIO_Set(GPIO_TypeDef* GPIOx, \
	u16 GPIO_Pin, \
	GPIOSpeed_TypeDef GPIO_Speed, \
	GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode;

	GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void han_Timer_PWM_Opt(TIM_TypeDef* TIMx, u16 PWM_Period, u8 Channel_Number, u8* Channel_Ptr)
{
	//Set TIMx as PWM output timer for motor controlling - ENABLE
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	RCC_ClocksTypeDef RCC_Clocks;
	uint32_t Periph_Clock = 0;
	u8 i;

	TIM_DeInit(TIMx);

	if (TIMx == TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
		Periph_Clock = RCC_Clocks.PCLK2_Frequency;
	}
	else if (TIMx == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
		Periph_Clock = RCC_Clocks.PCLK1_Frequency;
	}
	else if (TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
		Periph_Clock = RCC_Clocks.PCLK1_Frequency;
	}
	else if (TIMx == TIM4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		Periph_Clock = RCC_Clocks.PCLK1_Frequency;
	}
	else if (TIMx == TIM5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
		Periph_Clock = RCC_Clocks.PCLK1_Frequency;
	}
	else if (TIMx == TIM8)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
		Periph_Clock = RCC_Clocks.PCLK2_Frequency;
	}
	Periph_Clock = Periph_Clock / 1000000; //Represent TIMx clock by MHz.

	//定时器初始化
	TIM_TimeBaseStructure.TIM_Prescaler = Periph_Clock - 1; 				//定时器预分频 APBx /(TIM_Prescaler + 1) = 1M
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;				//向上计数模式
	TIM_TimeBaseStructure.TIM_Period = PWM_Period - 1; 						//自动重装值 (TIM_Period + 1) = 1k
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 							//设置时钟分割: TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	//计时输出
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;						//选择模式PWM1，小于比较值时有效

	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;			//TIMxCH1-TIMxCH4使能
	TIM_OCInitStructure.TIM_Pulse = PWM_Period;								//每次捕获的比较值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;				//有效电平为高电平
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;				//TIM1CH1-TIM1CH4输出状态

	for (i = 0; i < Channel_Number; i++)
	{
		switch (Channel_Ptr[i])
		{
			case 1: TIM_OC1Init(TIMx, &TIM_OCInitStructure); //CH1
					TIM_OC1PreloadConfig(TIMx, TIM_OCPreload_Enable);
					break;
			case 2: TIM_OC2Init(TIMx, &TIM_OCInitStructure); //CH2
					TIM_OC2PreloadConfig(TIMx, TIM_OCPreload_Enable);
					break;
			case 3: TIM_OC3Init(TIMx, &TIM_OCInitStructure); //CH3
					TIM_OC3PreloadConfig(TIMx, TIM_OCPreload_Enable);
					break;
			case 4: TIM_OC4Init(TIMx, &TIM_OCInitStructure); //CH4
					TIM_OC4PreloadConfig(TIMx, TIM_OCPreload_Enable);
					break;
		}
	}

	TIM_ARRPreloadConfig(TIMx, ENABLE);

	TIM_Cmd(TIMx, ENABLE);
	TIM_CtrlPWMOutputs(TIMx, ENABLE);
}

void han_NVIC_Set(IRQn_Type IRQn, u8 Preeption, u8 Sub)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Preeption;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = Sub;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);
}

void han_Timer_Encoder(TIM_TypeDef* TIMx, u16 LineNumber, u16 CatchAngle)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	u16 arr_calc = 0;

	TIM_DeInit(TIMx);

	if (TIMx == TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	}
	else if (TIMx == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	else if (TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if (TIMx == TIM4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
	else if (TIMx == TIM5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	}
	else if (TIMx == TIM8)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	}

	arr_calc = (u16)((double)LineNumber * (double)CatchAngle / 360.0);

	TIM_TimeBaseStructure.TIM_Period = arr_calc * 4 * 2 - 1;		//设定计数器重装值   TIMx_ARR = arr_calc * 4 * 2 - 1
																	//LineNumber线编码器，倍频*4，中间往两边计数*2
																	//每CatchAngle溢出，更新中断
	TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure);

	TIM_EncoderInterfaceConfig(TIMx, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);//使用编码器模式3，上升下降都计数

	TIM_ICInitStructure.TIM_ICFilter = 6;							//选择输入比较滤波器 
	TIM_ICInit(TIMx, &TIM_ICInitStructure);

	TIM_ClearFlag(TIMx, TIM_FLAG_Update);							//清除TIMx的更新标志位
	TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);						//运行更新中断
											
	TIM_SetCounter(TIMx, arr_calc * 4 - 1);							//Reset counter to middle position
	TIM_Cmd(TIMx, ENABLE);											//启动TIMx定时器
}

void han_EXTI_Set(uint32_t EXTI_Line, \
	EXTIMode_TypeDef EXTI_Mode, \
	EXTITrigger_TypeDef EXTI_Trigger, \
	FunctionalState EXTI_LineCmd)

{
	EXTI_InitTypeDef EXTI_InitStructure;

	EXTI_InitStructure.EXTI_Line = EXTI_Line;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger;
	EXTI_InitStructure.EXTI_LineCmd = EXTI_LineCmd;

	EXTI_Init(&EXTI_InitStructure);
}

u8 han_Get_Counter_Direction(TIM_TypeDef* TIMx)
{
	if (TIMx->CR1 & TIM_CR1_DIR)
		return 1;
	return 0;
}
