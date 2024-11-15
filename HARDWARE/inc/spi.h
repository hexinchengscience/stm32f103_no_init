#ifndef __SPI_H__
#define __SPI_H__

#include "DataType.h"
#include "STM32F103.h"
#include "system.h"
#include "gpio.h"
#include "delay.h"

//! SPI总线速度设置 
#define SPI_SPEED_2       0
#define SPI_SPEED_4       1
#define SPI_SPEED_8       2
#define SPI_SPEED_16      3
#define SPI_SPEED_32       4
#define SPI_SPEED_64       5
#define SPI_SPEED_128     6
#define SPI_SPEED_256     7

void SPI2_Init(void) ;               //! SPI2初始化
void SPI2_SetSpeed(u8 SpeedSet) ;    //! SPI2设置速度
u8 SPI2_ReadWriteByte(u8 TxData) ;   //! SPI2 读写一个字节

#endif /*  __SPI_H__  */


