#ifndef __BSP_UART
#define __BSP_UART
/* USER CODE BEGIN Private defines */
#include "cmsis_os.h"
#include "stm32l4xx_hal.h"
#define LORAWAN_APP_DATA_BUFF_SIZE 250 //242
#define RECEIVELEN (LORAWAN_APP_DATA_BUFF_SIZE * 2)
#define SENDLEN 128
#define USART_DMA_SENDING 1//发送未完成
#define USART_DMA_SENDOVER 0//发送完成
#define DIV_PAKET 2

typedef struct
{
	uint8_t receive_flag;//空闲接收标记
	uint8_t uart_no;//串口号
	uint16_t rx_len;//接收长度
	uint8_t usartDMA_rxBuf[RECEIVELEN];//DMA接收缓存
}USART_RECEIVETYPE;

typedef struct
{
	uint8_t receive_flag;//空闲接收标记
	uint8_t uart_no;//串口号
	uint16_t rx_len;//接收长度
	uint8_t usartDMA_rxBuf[RECEIVELEN/DIV_PAKET];//DMA接收缓存
}USART_RECEIVETYPE2;

typedef struct
{
	uint8_t dmaSend_flag;//发送完成标记
	uint8_t uart_no;//串口号
	uint16_t tx_len;//接收长度
	uint8_t usartDMA_txBuf[SENDLEN];//DMA接收缓存
}USART_SENDTYPE;

extern QueueHandle_t xRS232SendQueue3;

void uart_init(void);
void uart_queue_init(void);
void Usart1SendData_DMA(UART_HandleTypeDef *huart,uint8_t *pdata, uint16_t Length);
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
void UsartReceive_IDLE(UART_HandleTypeDef *huart);
#endif
