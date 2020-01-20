/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define RESET_2G4_Pin GPIO_PIN_0
#define RESET_2G4_GPIO_Port GPIOA
#define BUSY_2G4_Pin GPIO_PIN_3
#define BUSY_2G4_GPIO_Port GPIOA
#define DIO1_2G4_Pin GPIO_PIN_6
#define DIO1_2G4_GPIO_Port GPIOA
#define RX_EN_2G4_Pin GPIO_PIN_7
#define RX_EN_2G4_GPIO_Port GPIOA
#define SPI2_NSS_Pin GPIO_PIN_12
#define SPI2_NSS_GPIO_Port GPIOB
#define TX_EN_2G4_Pin GPIO_PIN_11
#define TX_EN_2G4_GPIO_Port GPIOA
#define DIO3_2G4_Pin GPIO_PIN_3
#define DIO3_2G4_GPIO_Port GPIOB
#define DIO2_2G4_Pin GPIO_PIN_4
#define DIO2_2G4_GPIO_Port GPIOB
#define CLK_EN_Pin GPIO_PIN_5
#define CLK_EN_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
