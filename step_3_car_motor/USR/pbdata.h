#ifndef _pbdata_H
#define _pbdata_H

#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_usart.h"
# include "stm32f10x_spi.h"
#include "stdio.h"
#include "imu.h"
# include "step_motor.h"
# include "bsp_spi_nrf.h"
# include "bsp_car.h"

//定义变量

extern u8 dt;

//定义函数


void RCC_HSE_Configuration(void);
void delay(u32 nCount);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif
