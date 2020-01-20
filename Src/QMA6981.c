
#include "main.h"
#include "QMA6981.h"
//#include "debug_log.h"
#include "qst_sw_i2c.h"
#include "stdio.h"

#define QMA6981ADDR             		0x24
#define QMA6981REGADDR_CHIPID           0x00
#define QMA6981REGADDR_DXL              0x01
#define QMA6981REGADDR_DXM            	0x02
#define QMA6981REGADDR_STEPCNT          0x07
#define QMA6981REGADDR_RANGE            0x0f
#define QMA6981REGADDR_BW               0x10
#define QMA6981REGADDR_POWER            0x11
#define QMA6981REGADDR_STEP_CONF0       0x12
#define QMA6981REGADDR_STEP_CONF1       0x13
#define QMA6981REGADDR_STEP_CONF2       0x14
#define QMA6981REGADDR_STEP_CONF3       0x15
#define QMA6981REGADDR_INT_EN0          0x16
#define QMA6981REGADDR_INT_MAP0         0x19
#define QMA6981REGADDR_INT_INTPIN_CFG   0x20
#define QMA6981REGADDR_OS_CUST_X   		0x27
#define QMA6981REGADDR_OS_CUST_Y   		0x28
#define QMA6981REGADDR_OS_CUST_Z   		0x29

#define QMA6981REGADDR_TAP_CONF0        0x2a
#define QMA6981REGADDR_TAP_CONF1        0x2b
#define QMA6981REGADDR_ST_CONF       	0x32

#define QMA6981REGADDR_SR               0x36

#define true 1
#define bool uint8_t
static uint8_t g_sensor_open = true;

//#define USE_SW_IIC

uint16_t qma6981_int_flag = 0;
uint16_t qma6981_int_count = 0;

uint8_t aTxBuffer[4] = {0};
uint8_t aRxBuffer[4] = {0};

extern I2C_HandleTypeDef hi2c2;

void QMA6981I2C_init(void)
{
// #if defined(USE_SW_IIC)
// 	i2c_sw_gpio_config();
// #else
// 	  hi2c2.Instance			  = I2C1;
// 	  hi2c2.Init.Timing 		  = 0x20302e37;
// 	  hi2c2.Init.OwnAddress1	  = 0;
// 	  hi2c2.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
// 	  hi2c2.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
// 	  hi2c2.Init.OwnAddress2	  = 0;
// 	  hi2c2.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
// 	  hi2c2.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
// 	  hi2c2.Init.NoStretchMode	  = I2C_NOSTRETCH_DISABLE;

// 	 if (HAL_I2C_Init(&hi2c2) != HAL_OK)
// 	  {
// 	    Error_Handler();
// 	  }

// 	  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c2, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
// 	  {
// 	    Error_Handler();
// 	  }

// 	  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c2, 0) != HAL_OK)
// 	  {
// 	    Error_Handler();
// 	  }
// #endif
}

void QMA6981Write(char reg, char val)
{
#if defined(USE_SW_IIC)
	qst_sw_writereg(QMA6981ADDR,(uint8_t)reg,(uint8_t)val);
#else
	uint8_t buf[2];
	buf[0] = reg;
	buf[1] = val;
  do
  {
    if(HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)QMA6981ADDR, (uint8_t*)buf, 2,10000)!= HAL_OK)
    {
      Error_Handler();
    }
    while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY)
    {
    }

  }
  while(HAL_I2C_GetError(&hi2c2) == HAL_I2C_ERROR_AF);
#endif
}

void QMA6981Read(uint8_t reg,uint8_t* buf,uint8_t len)
{
#if defined(USE_SW_IIC)
	qst_sw_readreg(QMA6981ADDR,reg, buf,len);
#else
	do
	 {
	   if(HAL_I2C_Master_Transmit(&hi2c2, (uint16_t)QMA6981ADDR, &reg, 1,5000)!= HAL_OK)
	   {
		 Error_Handler();
	   }
	   while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY)
	   {
	   }

	 }
	 while(HAL_I2C_GetError(&hi2c2) == HAL_I2C_ERROR_AF);

	 HAL_Delay(100);
	 do
	 {
	   if(HAL_I2C_Master_Receive(&hi2c2, (uint16_t)QMA6981ADDR, (uint8_t *)buf, len,5000) != HAL_OK)
	   {
		 Error_Handler();
	   }

	   while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY)
	   {
	   }

	 }
	 while(HAL_I2C_GetError(&hi2c2) == HAL_I2C_ERROR_AF);

	 while (HAL_I2C_GetState(&hi2c2) != HAL_I2C_STATE_READY)
	 {
	 }
#endif
}

void QMA6981SetMode(enum QMA6981MODE mode)
{
    QMA6981Write(QMA6981REGADDR_POWER,mode);
}

void QMA6981SoftReset(void)
{
    char  ret_val=0xb6;//reset cmd
    QMA6981Write(QMA6981REGADDR_SR,ret_val);
    HAL_Delay(100);
    ret_val = 0x00;//default value
    QMA6981Write(QMA6981REGADDR_SR,ret_val);
}

//中断寄存器配置
#define DUMU_REG_LEN	30
uint8_t reg_dump[DUMU_REG_LEN] = {0};
int16_t raw_data[3] = {0};

void QMA6981_INT_Register_config()
{
  uint8_t chipid = 0;

	QMA6981SetMode(QMA6981MODE_ACTIVE);
	HAL_Delay(100);
    QMA6981SoftReset();
    QMA6981SetMode(QMA6981MODE_ACTIVE);
	HAL_Delay(100);

	QMA6981Read(0x00,&chipid,1);

	if(chipid == 0xb0)
	{
		//设置传感器测量范围
		QMA6981Write(0x0f,0x01);
		//输出率
		QMA6981Write(0x10,0x05);
		//设置震动中断g值
		QMA6981Write(0x2b,0x01);
		//开启单点震动中断
		QMA6981Write(0x16,0x20);
		//将单点震动中断映射到INT1 pin
		QMA6981Write(0x19,0x20);

		//中断PIN脚默认为高电平
		QMA6981Write(0x20,0x00);

		QMA6981Write(0x11,0x80);
	}
	else
	{
		QMA6981Write(0x0f, 0x02);        // range  +-4g
		QMA6981Write(0x10, 0xe2);        // odr 130hz
		QMA6981Write(0x18, 0x07);        // any motion enable xyz
		QMA6981Write(0x1a, 0x01);        // any motion interrupt map to int 1
		QMA6981Write(0x2c, 0x00);
		QMA6981Write(0x2e, 0x0a);  		// 0.488*16*10 = 78.08 mg
		QMA6981Write(0x20, 0x00);    	// INT LEVEL default high
		QMA6981Write(0x11, 0x82);    	// entry active mode
		QMA6981Write(0x5f, 0x80);
		QMA6981Write(0x5f, 0x00);
	}
#if 0
	while(1)
	{
		int i;
		for(i= 0; i<DUMU_REG_LEN; i++)
		{
			reg_dump[i] = 0;
		}
		HAL_Delay(500);
		QMA6981Read(0x01,reg_dump,DUMU_REG_LEN-1);
		raw_data[0] = (int16_t)((reg_dump[1]<<8)|reg_dump[0]);
		raw_data[1] = (int16_t)((reg_dump[3]<<8)|reg_dump[2]);
		raw_data[2] = (int16_t)((reg_dump[5]<<8)|reg_dump[4]);
		raw_data[0] = raw_data[0] >> 6;
		raw_data[1] = raw_data[1] >> 6;
		raw_data[2] = raw_data[2] >> 6;
		HAL_Delay(500);
	}
#endif
}

uint16_t QMA6981ReadStep(void)
{
    uint8_t dat[2] = {0};
    QMA6981Read(QMA6981REGADDR_STEPCNT,dat,2);
   	return ((dat[0]>>0)+(dat[1]<<8));
}

void QMA6981_power_off()
{
	char val;

    QMA6981SetMode(QMA6981MODE_ACTIVE);
    QMA6981SoftReset();
    HAL_Delay(100);
    QMA6981SetMode(QMA6981MODE_ACTIVE);

    val = 0x00;
    QMA6981Write(QMA6981REGADDR_INT_INTPIN_CFG,val);
    QMA6981Write(QMA6981REGADDR_POWER,0x40);
}

void QMA6981Init(void)
{
	//QMA6981I2C_init();
	if(g_sensor_open)
	{
		QMA6981_INT_Register_config();
		qma6981_int_enable();
		printf("qma6981 init success : g_sensor function open\r\n");
		return ;
	}

//	QMA6981_power_off();
//	qma6981_int_disable();
	printf("qma6981 power off\r\n");
}


void QMA6981_IIC_GPIO_Init()
{
 	// GPIO_InitTypeDef GPIO_InitStruct = {0};

    // __HAL_RCC_GPIOB_CLK_ENABLE();

    // GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    // GPIO_InitStruct.Pull = GPIO_PULLUP;
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // GPIO_InitStruct.Alternate = GPIO_AF1_I2C1;
    // HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // __HAL_RCC_I2C1_CLK_ENABLE();

}

void QMA6981_IIC_GPIO_DeInit()
{
	// __HAL_RCC_I2C1_CLK_DISABLE();
	// HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6|GPIO_PIN_7);
	// HAL_GPIO_DeInit(GPIOA, GPIO_PIN_11);
}

void qma6981_int_enable()
{
	// GPIO_InitTypeDef GPIO_InitStruct = {0};

	// __HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO_InitStruct.Pin = GPIO_PIN_11;
	// GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	// GPIO_InitStruct.Pull = GPIO_NOPULL;

	// HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	// HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
	// HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

void qma6981_int_disable()
{
	// GPIO_InitTypeDef GPIO_InitStruct = {0};

	// __HAL_RCC_GPIOA_CLK_ENABLE();

	// GPIO_InitStruct.Pin = GPIO_PIN_11;
	// GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	// GPIO_InitStruct.Pull = GPIO_NOPULL;

	// HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void QMA6981_INTHandle()
{
	qma6981_int_flag = 1;
	qma6981_int_count++;
}
