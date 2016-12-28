/*
	@Copyright Han ZHANG(haldak) | All rights reserved.
	@Last Modified Time Nov.13, 2016
*/

/* Includes ------------------------------------------------------------------*/
#include "mpr121.h"
#include "i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
void mpr121_Write(uint8_t regAddress, uint8_t regData)
{
	static uint8_t pData[2];
	pData[0] = regAddress;
	pData[1] = regData;
  while(HAL_I2C_Master_Transmit(&hi2c1, TOUCH_SHELD,(uint8_t*)pData, 2, 1000) != HAL_OK)
  {
		if(HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF)
		{
			Error_Handler();
		}
	}
}

void mpr121_Init(void)
{
	// Section A
  // This group controls filtering when data is > baseline.
  mpr121_Write(MHD_R, 0x01);
  mpr121_Write(NHD_R, 0x01);
  mpr121_Write(NCL_R, 0x00);
  mpr121_Write(FDL_R, 0x00);

  // Section B
  // This group controls filtering when data is < baseline.
  mpr121_Write(MHD_F, 0x01);
  mpr121_Write(NHD_F, 0x01);
  mpr121_Write(NCL_F, 0xFF);
  mpr121_Write(FDL_F, 0x02);
  
  // Section C
  // This group sets touch and release thresholds for each electrode
  mpr121_Write(ELE0_T, TOU_THRESH);
  mpr121_Write(ELE0_R, REL_THRESH);
  mpr121_Write(ELE1_T, TOU_THRESH);
  mpr121_Write(ELE1_R, REL_THRESH);
  mpr121_Write(ELE2_T, TOU_THRESH);
  mpr121_Write(ELE2_R, REL_THRESH);
  mpr121_Write(ELE3_T, TOU_THRESH);
  mpr121_Write(ELE3_R, REL_THRESH);
  mpr121_Write(ELE4_T, TOU_THRESH);
  mpr121_Write(ELE4_R, REL_THRESH);
  mpr121_Write(ELE5_T, TOU_THRESH);
  mpr121_Write(ELE5_R, REL_THRESH);
  mpr121_Write(ELE6_T, TOU_THRESH);
  mpr121_Write(ELE6_R, REL_THRESH);
  mpr121_Write(ELE7_T, TOU_THRESH);
  mpr121_Write(ELE7_R, REL_THRESH);
  mpr121_Write(ELE8_T, TOU_THRESH);
  mpr121_Write(ELE8_R, REL_THRESH);
  mpr121_Write(ELE9_T, TOU_THRESH);
  mpr121_Write(ELE9_R, REL_THRESH);
  mpr121_Write(ELE10_T, TOU_THRESH);
  mpr121_Write(ELE10_R, REL_THRESH);
  mpr121_Write(ELE11_T, TOU_THRESH);
  mpr121_Write(ELE11_R, REL_THRESH);
  
  // Section D
  // Set the Filter Configuration
  // Set ESI2
  mpr121_Write(FIL_CFG, 0x04);
  
  // Section E
  // Electrode Configuration
  // Enable 6 Electrodes and set to run mode
  // Set ELE_CFG to 0x00 to return to standby mode
  mpr121_Write(ELE_CFG, 0x0C);	// Enables all 12 Electrodes
  //mpr121_Write(ELE_CFG, 0x06);		// Enable first 6 electrodes
  
  // Section F
  // Enable Auto Config and auto Reconfig
  /*mpr121_Write(ATO_CFG0, 0x0B);
  mpr121_Write(ATO_CFGU, 0xC9);	// USL = (Vdd-0.7)/vdd*256 = 0xC9 @3.3V   write_i2c(touch_shield,ATO_CFGL, 0x82);	// LSL = 0.65*USL = 0x82 @3.3V
  mpr121_Write(ATO_CFGT, 0xB5);*/	// Target = 0.9*USL = 0xB5 @3.3V
}
