# Test Code I - Basic functions
- Devide all functions into small pieces.
## Systick Frequency Test
Systick Test Pass

Systick act with 1ms frequency.


## Basic I/O Voltage Low/High Test
Auto Pass with setting D2 as high voltage output.
 
 
## USART-DMA Sendback Test
Test Pass

For receive mode, enable Circular to receive data at any time.

For send mode, disable Circular to avoid send data over and over again.


## Get Encoder Value Test
Test Pass

Remember to call HAL_TIM_Encoder_Start();


## PWM Generate Test
Test Pass

Remember to call HAL_TIM_PWM_Start();


## EXTI Test
I don't want to test this function today...
