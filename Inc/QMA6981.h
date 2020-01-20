
#ifndef __QMA6981_H__
#define __QMA6981_H__

#include "stdint.h"

enum QMA6981MODE
{
    QMA6981MODE_ACTIVE=0x80,
    QMA6981MODE_STANDBY=0x00
};

void QMA6981I2C_init(void);
void QMA6981Write(char reg, char val);
void QMA6981Read(uint8_t reg,uint8_t* buf,uint8_t len);
void QMA6981SetMode(enum QMA6981MODE mode);
void QMA6981SoftReset(void);

uint16_t QMA6981ReadStep(void);
void QMA6981Init(void);

void QMA6981_IIC_GPIO_Init(void);
void QMA6981_IIC_GPIO_DeInit(void);
void QMA6981_INTHandle(void);

void qma6981_int_enable(void);
void qma6981_int_disable(void);

int get_qma6981_int_count(void);
void clear_qma6981_int_count(void);

void test_init(void);

#endif

