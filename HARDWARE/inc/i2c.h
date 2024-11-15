/****************************************************************************************
* 文件名称: i2c.h
* 
* 创建时间：2021/06/28
*
* 修改时间：2021/06/28
*
* 作    者：hxc
*
* 版    本：V1.0
*
* 文摘描述：i2c 头文件
*
* 说    明：
****************************************************************************************/ 
#ifndef __I2C_H__
#define __I2C_H__

#include "Cortex-M3.h"
#include "STM32F103.h"
#include "gpio.h"


//! 直接IO口模拟I2C硬件引脚定义*********************************************************************
#define I2C_Delay_us(nus) { int i = 0 ; for(i = 0 ; i < (nus * 4 + 4) ; i ++) ; }
#define I2C_Wait_Ack_Count        5000       //! 等待响应最大计数值

#define defI2cGpioIoOutInit(port , n)  GPIO_Init(port , n , GPIO_Mode_Out_OD)

#define defGpioInputMode(port , n)     GPIO_Init(port , n , GPIO_Mode_IPU)
#define defGpioOutputMode(port , n)    GPIO_Init(port , n , GPIO_Mode_Out_OD)


#define I2C1_SCL_Pin_Init()            defI2cGpioIoOutInit(GPIOB , 6)
#define I2C1_SCL_Pin_Out_H             PBout(6) = 1
#define I2C1_SCL_Pin_Out_L             PBout(6) = 0
#define I2C1_SDA_Pin_Init()            defI2cGpioIoOutInit(GPIOB , 7)
#define I2C1_SDA_Input_Mode()          defGpioInputMode(GPIOB , 7)
#define I2C1_SDA_Output_Mode()         defGpioOutputMode(GPIOB , 7)
#define I2C1_SDA_Pin_Out_H             PBout(7) = 1
#define I2C1_SDA_Pin_Out_L             PBout(7) = 0
#define I2C1_SDA_Pin_In                PBin(7)
#define I2C1_Delay_Time                I2C_Delay_us

//! 直接IO口模拟I2C硬件引脚定义*********************************************************************

//! I2C函数声明*************************************************************************************
#define def_I2C_Simulation_Function_Declare(n)                                                     \
void I2C##n##_Init(void) ;                                                                         \
void I2C##n##_Pin_Test(void) ;                                                                     \
void I2C##n##_Write_One_Byte(u8 deviceAddr , u8 regAddr , u8 dat);                                 \
u8 I2C##n##_Read_One_Byte(u8 deviceAddr , u8 regAddr) ;                                            \
void I2C##n##_Read_N_Byte(u8 deviceAddr , u8 regAddr , u8 * dat , u8 len) ;                        \
void I2C##n##_Write_N_Byte(u8 deviceAddr , u8 regAddr , u8 * dat , u8 len) ;                       \
void I2C##n##_Write_One_Byte16(u8 deviceAddr , u16 regAddr , u8 dat);                              \
u8 I2C##n##_Read_One_Byte16(u8 deviceAddr , u16 regAddr) ;                                         \
void I2C##n##_Read_N_Byte16(u8 deviceAddr , u16 regAddr , u8 * dat , u8 len) ;                     \
void I2C##n##_Write_N_Byte16(u8 deviceAddr , u16 regAddr , u8 * dat , u8 len) ;

def_I2C_Simulation_Function_Declare(1)


#endif /* __I2C_H__ */
