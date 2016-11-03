# Driver Board V2
## Requirement
- Include two dc motor driver and a power controlling module
- Use the XH2.54 connectors for DC motors with encoders. (For protocal, see https://item.taobao.com/item.htm?spm=a230r.1.14.55.Ggn03E&id=526888119369&ns=1&abbucket=10#detail)
- Use the DG/KF128 -2.54 -2P connectors for DC motors without encoders.
- Power supply: Li-on battery, 3s(11.1V), (XT60 or T-shape connector) for motor
								2s(7.4V), (XT60 or T-shape connector) for logic electronic device
## IC
- TI DRV8801 * 2
- STM32F103 as main controller.
- MPU9250 / JY61p (We can choose which to be used on board.)
- TP4056 for on board charging.
- LM1117-3.3
- Wireless communication
	HC-05 for ble
	NRF24L01+ for nrf
	ESP8266 for wifi
	Use a 3p1t swich to select the wireless communication mode.
- ST-Link(STM32F103C8T6)
- USB to UART(PL2303)
Use jumper or dpdt switch to choose the AFIO function.