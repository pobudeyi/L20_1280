/**
  ******************************************************************************
  * @file    bma2x2_hal.c 
  * @author  HF
  * @brief   BMA253驱动
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 Rinlink.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>

#include "i2c.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ---------------------------------------------------------*/
void Gsensor_Itf_Init(void)
{
	MX_I2C2_Init();
}

bool Gsensor_Itf_Write(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (HAL_I2C_Mem_Write(&hi2c2 , (uint16_t)DevAddress, MemAddress,I2C_MEMADD_SIZE_8BIT,  pData, Size,Timeout)!= HAL_OK)
    {
//      	if (HAL_I2C_GetError(&hi2c2) != HAL_I2C_ERROR_AF)
//      	{
//          /* Writing process Error */
//          Error_Handler();
//        }
		return false;
    }

    return true;
}

bool Gsensor_Itf_Read(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	if (HAL_I2C_Mem_Read(&hi2c2 , (uint16_t)DevAddress, MemAddress,I2C_MEMADD_SIZE_8BIT,  pData, Size,Timeout)!= HAL_OK)
    {
//      	if (HAL_I2C_GetError(&hi2c2) != HAL_I2C_ERROR_AF)
//      	{
//          /* Writing process Error */
//          Error_Handler();
//        }
		return false;
    }

    return true;
}


/************************ (C) COPYRIGHT Rinlink *****END OF FILE****/

