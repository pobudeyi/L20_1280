/**
  ******************************************************************************
  * @file    bma2x2_hal.h 
  * @author  HF
  * @brief   BMA253驱动 头文件
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 Rinlink.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
#ifndef __BMA2X2_HAL_H
#define __BMA2X2_HAL_H
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
#include <stdint.h>
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ---------------------------------------------------------*/

extern void Gsensor_Itf_Init(void);
extern bool Gsensor_Itf_Write(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
extern bool Gsensor_Itf_Read(uint16_t DevAddress, uint16_t MemAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

#endif //__BMA2X2_HAL_H
/************************ (C) COPYRIGHT Rinlink *****END OF FILE****/

