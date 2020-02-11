#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_dma.h"
#include "bsp_uart.h"
#include "usart.h"
#include "cmsis_os.h"
#include "string.h"
#include "stdio.h"

#define MAX_QUEUE_NUM 30
static USART_SENDTYPE RS232SendType3;

static USART_RECEIVETYPE RS232RecvType3[MAX_QUEUE_NUM];

static USART_RECEIVETYPE *p_RS232RecvType3=&RS232RecvType3[0];

QueueHandle_t xRS232SendQueue3 = NULL;

extern SemaphoreHandle_t  xLoraRecSemaphore;

///* USER CODE BEGIN 1 */
#if 0
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart1 , (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}
#endif
#if 1
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1 , (unsigned char *)&ch, 1, 0xFFFF);
    return ch;
}
int _write(int file,char *ptr,int len)
{
    int DataIdx;
    for(DataIdx=0;DataIdx<len;DataIdx++)
    {
        __io_putchar(*ptr++);
    }
    return len;
}
#endif
void uart_init(void)
{
    memset(&RS232RecvType3,0,sizeof(RS232RecvType3));
    p_RS232RecvType3->receive_flag=1;
	HAL_UART_Receive_DMA(&huart1, (uint8_t*)p_RS232RecvType3->usartDMA_rxBuf, RECEIVELEN);
	__HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
}

void uart_queue_init(void)
{
	xRS232SendQueue3 = xQueueCreate( MAX_QUEUE_NUM,  4);//sizeof(USART_RECEIVETYPE)
}
static uint8_t shake_cnt=0;
uint16_t tmp_cnt=0;
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    if(GPIO_PIN_4==GPIO_Pin)
    {
        printf("this is pin4 %d\r\n",shake_cnt++);
    }
    if(GPIO_PIN_1==GPIO_Pin)
    {
        tmp_cnt++;
    }
    if(GPIO_PIN_6==GPIO_Pin)
    {
        xSemaphoreGiveFromISR(xLoraRecSemaphore,&xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }
}
//DMA发送完成中断回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
     __HAL_DMA_DISABLE(huart->hdmatx);
	if(huart->Instance==USART1)
		RS232SendType3.dmaSend_flag = USART_DMA_SENDOVER;
}

//串口接收空闲中断
void UsartReceive_IDLE(UART_HandleTypeDef *huart)
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint8_t i;
    if((__HAL_UART_GET_FLAG(huart,UART_FLAG_IDLE) != RESET))
    {
        __HAL_UART_CLEAR_IDLEFLAG(huart);
        HAL_UART_DMAStop(huart);
		if(huart->Instance==USART1)
        {
            if(RECEIVELEN - __HAL_DMA_GET_COUNTER(huart->hdmarx)<=RECEIVELEN)
            {
                p_RS232RecvType3->rx_len =  RECEIVELEN - __HAL_DMA_GET_COUNTER(huart->hdmarx); //取接收长度
                p_RS232RecvType3->uart_no=3;
                if(p_RS232RecvType3->rx_len>0)
                {
                    xQueueSendFromISR(xRS232SendQueue3,(void *)&p_RS232RecvType3,&xHigherPriorityTaskWoken);
                }
            }
            if(p_RS232RecvType3->rx_len>1)
                for(i=0;i<MAX_QUEUE_NUM;i++)
                    if(RS232RecvType3[i].receive_flag==0)
                    {
                        p_RS232RecvType3=&RS232RecvType3[i];
                        p_RS232RecvType3->receive_flag=i+1;
                        break;
                    }
            HAL_UART_Receive_DMA(huart,p_RS232RecvType3->usartDMA_rxBuf,RECEIVELEN);
        }
    }
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
