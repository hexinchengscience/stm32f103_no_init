/**************************************************************************************************
* 文件名称: i2c.c
* 
* 创建时间：2021/06/28
*
* 修改时间：2021/06/28
*
* 作    者：hxc
*
* 版    本：V1.0
*
* 文摘描述：i2c 源文件
*
* 说    明：
***************************************************************************************************/ 
#include "i2c.h"


//! I2C驱动相关功能函数*****************************************************************************
#define def_I2C_Simulation_Function_Define(n)                                                      \
void I2C##n##_Init(void)                                                                           \
{                                                                                                  \
    I2C##n##_SCL_Pin_Init()  ; I2C##n##_SDA_Pin_Init()  ;                                          \
    I2C##n##_SCL_Pin_Out_H ; I2C##n##_SDA_Pin_Out_H ;                                              \
}                                                                                                  \
void I2C##n##_Pin_Test(void)                                                                       \
{                                                                                                  \
    I2C##n##_SDA_Pin_Out_H ; I2C##n##_SCL_Pin_Out_H ; I2C##n##_Delay_Time(20) ;                    \
    I2C##n##_SDA_Pin_Out_L ; I2C##n##_SCL_Pin_Out_L ; I2C##n##_Delay_Time(20) ;                    \
}                                                                                                  \
void I2C##n##_Start(void)                                                                          \
{                                                                                                  \
    I2C##n##_SDA_Output_Mode() ; I2C##n##_Delay_Time(20) ;                                         \
    I2C##n##_SDA_Pin_Out_H ; I2C##n##_SCL_Pin_Out_H ; I2C##n##_Delay_Time(10) ;                    \
    I2C##n##_SDA_Pin_Out_L ; I2C##n##_Delay_Time(10) ; I2C##n##_SCL_Pin_Out_L ;                    \
}                                                                                                  \
void I2C##n##_Stop(void)                                                                           \
{                                                                                                  \
    I2C##n##_SDA_Output_Mode() ;                                                                   \
    I2C##n##_SCL_Pin_Out_L ; I2C##n##_SDA_Pin_Out_L ; I2C##n##_Delay_Time(20) ;                    \
    I2C##n##_SCL_Pin_Out_H ; I2C##n##_Delay_Time(10) ;                                             \
    I2C##n##_SDA_Pin_Out_H ; I2C##n##_Delay_Time(10) ;                                             \
}                                                                                                  \
u8 I2C##n##_Wait_Ack(void)                                                                         \
{                                                                                                  \
    u32 ucErrTime = 0 ;                                                                            \
    I2C##n##_SDA_Pin_Out_H ; I2C##n##_SDA_Input_Mode() ; I2C##n##_Delay_Time(20) ;                 \
    I2C##n##_SCL_Pin_Out_H ; I2C##n##_Delay_Time(10) ;                                             \
    while(I2C##n##_SDA_Pin_In) { ucErrTime ++ ; if(ucErrTime > I2C_Wait_Ack_Count) { return 1 ; } }\
    I2C##n##_Delay_Time(10) ; I2C##n##_SCL_Pin_Out_L ;                                             \
    return 0 ;                                                                                     \
}                                                                                                  \
void I2C##n##_Is_Ack(u8 ack)                                                                       \
{                                                                                                  \
    I2C##n##_SCL_Pin_Out_L ;                                                                       \
    I2C##n##_SDA_Output_Mode() ;                                                                   \
    if(ack) I2C##n##_SDA_Pin_Out_L ;                                                               \
    else I2C##n##_SDA_Pin_Out_H ;                                                                  \
    I2C##n##_Delay_Time(20) ;                                                                      \
    I2C##n##_SCL_Pin_Out_H ;                                                                       \
    I2C##n##_Delay_Time(20) ;                                                                      \
    I2C##n##_SCL_Pin_Out_L ;                                                                       \
}                                                                                                  \
void I2C##n##_Send_Byte(u8 txd)                                                                    \
{                                                                                                  \
    u8 t ;                                                                                         \
    I2C##n##_SDA_Output_Mode() ;                                                                   \
    I2C##n##_SCL_Pin_Out_L ;                                                                       \
    for(t = 0 ; t < 8 ; t ++)                                                                      \
    {                                                                                              \
        I2C##n##_Delay_Time(10) ;                                                                  \
        if(txd & 0x80) I2C##n##_SDA_Pin_Out_H ;                                                    \
        else I2C##n##_SDA_Pin_Out_L ;                                                              \
        txd <<= 1 ;                                                                                \
        I2C##n##_Delay_Time(10) ;                                                                  \
        I2C##n##_SCL_Pin_Out_H ;                                                                   \
        I2C##n##_Delay_Time(20) ;                                                                  \
        I2C##n##_SCL_Pin_Out_L ;                                                                   \
    }                                                                                              \
}                                                                                                  \
u8 I2C##n##_Read_Byte(unsigned char ack)                                                           \
{                                                                                                  \
    u8 i , receive = 0 ;                                                                           \
    I2C##n##_SDA_Input_Mode() ;                                                                    \
    for(i = 0 ; i < 8 ; i ++)                                                                      \
    {                                                                                              \
        I2C##n##_SCL_Pin_Out_L ;                                                                   \
        I2C##n##_Delay_Time(20) ;                                                                  \
        I2C##n##_SCL_Pin_Out_H ;                                                                   \
        receive <<= 1 ;                                                                            \
        I2C##n##_Delay_Time(10) ;                                                                  \
        if(I2C##n##_SDA_Pin_In) receive ++ ;                                                       \
        I2C##n##_Delay_Time(10) ;                                                                  \
    }                                                                                              \
    I2C##n##_Is_Ack(ack) ;                                                                         \
    return receive ;                                                                               \
}                                                                                                  \
u8 I2C##n##_Read_One_Byte(u8 deviceAddr , u8 regAddr)                                              \
{                                                                                                  \
    u8 temp = 0 ;                                                                                  \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr) ;                                                               \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr) ;                                                                  \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr + 1) ;                                                           \
    I2C##n##_Wait_Ack() ;                                                                          \
    temp = I2C##n##_Read_Byte(0) ;                                                                 \
    I2C##n##_Stop() ;                                                                              \
    return temp ;                                                                                  \
}                                                                                                  \
void I2C##n##_Write_One_Byte(u8 deviceAddr , u8 regAddr , u8 dat)                                  \
{                                                                                                  \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr) ;                                                               \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr) ;                                                                  \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(dat) ;                                                                      \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Stop() ;                                                                              \
}                                                                                                  \
void I2C##n##_Read_N_Byte(u8 deviceAddr , u8 regAddr , u8 * dat , u8 len)                          \
{                                                                                                  \
    u8 i ;                                                                                         \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr) ;                                                               \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr) ;                                                                  \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr + 1) ;                                                           \
    I2C##n##_Wait_Ack() ;                                                                          \
    for(i = 0 ; i < len ; ++ i) { dat[i] = I2C##n##_Read_Byte(i == len-1 ? 0 : 1) ; }              \
    I2C##n##_Stop() ;                                                                              \
}                                                                                                  \
void I2C##n##_Write_N_Byte(u8 deviceAddr , u8 regAddr , u8 * dat , u8 len)                         \
{                                                                                                  \
    u8 i ;                                                                                         \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr) ;                                                               \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr) ;                                                                  \
    I2C##n##_Wait_Ack() ;                                                                          \
    for(i = 0 ; i < len ; ++ i) { I2C##n##_Send_Byte(dat[i]) ; I2C##n##_Wait_Ack() ; }             \
    I2C##n##_Stop() ;                                                                              \
}                                                                                                  \
u8 I2C##n##_Read_One_Byte16(u8 deviceAddr , u16 regAddr)                                           \
{                                                                                                  \
    u8 temp = 0 ;                                                                                  \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr) ;                                                               \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr / 256) ;                                                            \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr % 256) ;                                                            \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr + 1) ;                                                           \
    I2C##n##_Wait_Ack() ;                                                                          \
    temp = I2C##n##_Read_Byte(0) ;                                                                 \
    I2C##n##_Stop() ;                                                                              \
    return temp ;                                                                                  \
}                                                                                                  \
void I2C##n##_Write_One_Byte16(u8 deviceAddr , u16 regAddr , u8 dat)                               \
{                                                                                                  \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr) ;                                                               \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr / 256) ;                                                            \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr % 256) ;                                                            \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(dat) ;                                                                      \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Stop() ;                                                                              \
}                                                                                                  \
void I2C##n##_Read_N_Byte16(u8 deviceAddr , u16 regAddr , u8 * dat , u8 len)                       \
{                                                                                                  \
    u8 i ;                                                                                         \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr) ;                                                               \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr / 256) ;                                                            \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr % 256) ;                                                            \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr + 1) ;                                                           \
    I2C##n##_Wait_Ack() ;                                                                          \
    for(i = 0 ; i < len ; ++ i) { dat[i] = I2C##n##_Read_Byte(i == len-1 ? 0 : 1) ; }              \
    I2C##n##_Stop() ;                                                                              \
}                                                                                                  \
void I2C##n##_Write_N_Byte16(u8 deviceAddr , u16 regAddr , u8 * dat , u8 len)                      \
{                                                                                                  \
    u8 i ;                                                                                         \
    I2C##n##_Start() ;                                                                             \
    I2C##n##_Send_Byte(deviceAddr) ;                                                               \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr / 256) ;                                                            \
    I2C##n##_Wait_Ack() ;                                                                          \
    I2C##n##_Send_Byte(regAddr % 256) ;                                                            \
    I2C##n##_Wait_Ack() ;                                                                          \
    for(i = 0 ; i < len ; ++ i) { I2C##n##_Send_Byte(dat[i]) ; I2C##n##_Wait_Ack() ; }             \
    I2C##n##_Stop() ;                                                                              \
}

def_I2C_Simulation_Function_Define(1)

