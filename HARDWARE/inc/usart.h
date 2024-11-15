#ifndef _USART_H_
#define _USART_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "DataType.h"
#include "Cortex-M3.h"
#include "STM32F103.h"
#include "system.h"
#include "gpio.h"

#define defRxOverTime  5                     //! 接收超时时间 ms
#define BufferLength   1024                  //! 串口数据长度
#define USART_RenewalPointer(p) p = (p + 1) % BufferLength  //! 更新串口指针

#define USART1_BaudRate  BaudRate115200      //! 串口1波特率115200
#define USART2_BaudRate  BaudRate9600      //! 串口2波特率115200
#define USART3_BaudRate  BaudRate115200      //! 串口3波特率115200

/*********************串口处理结构体****************************************************/
typedef struct 
{
    u16 RxHead ;                   //! 串口数据接收头
    u16 RxTail ;                   //! 串口数据接收尾
    u16 TxHead ;                   //! 串口数据发送头
    u16 TxTail ;                   //! 串口数据发送尾
  
    u8 RxBuffer[BufferLength] ;    //! 串口数据接收缓冲区
    u8 TxBuffer[BufferLength] ;    //! 串口数据发送缓冲区
  
    u8 TxFlag:1 ;                  //! 发送标志    
    u8 TxEnd:1 ;                   //! 发送结束  
    u8 RxFlag:1 ;                  //! 接收标志   
    u8 RxTime:5 ;                  //! 接收超时时间                             
}UsartDataTypeDef ;

/**
 * @brief   通用串口协议处理函数
 * @note    处理逻辑如下：
 *          1，首先判断接收时间是否超时。
 *          2，判断数据帧头是否正确，如果不正确，处理指针+1
 *          3，判断数据长度是否够，如果不够，直接扔掉当前接收数据
 *          4，读取数据，调用一次指令处理函数。
 *          5，判断是否还有多余数据没有处理，若有，重复上面的步骤。
 *
 * @note    5A A5 len dat1 dat2 .......
**/ 
#define UsartRxBuffer_Deal(USART) void USART##_Read_RxBuffer(void)                                    \
{                                                                                                     \
    if(USART##Usart.RxFlag && USART##Usart.RxTime > defRxOverTime)                                    \
    {                                                                                                 \
        u8 i ; USART##Usart.RxFlag = 0 ;  /*! 清接收状态位     */                                     \
        if(USART##Usart.RxHead == USART##Usart.RxTail) return ; /*! 头尾相等不处理*/                  \
        Read_RxBuffer_Start:              /*! 判断帧头是否正确 */                                     \
        if(USART##Usart.RxBuffer[USART##Usart.RxHead] == Frame_H && USART##Usart.RxBuffer[(USART##Usart.RxHead + 1) % BufferLength] == Frame_L)\
        {                                                                                             \
            /*! 判断数据长度是否够                                                              */    \
            u8 length = (USART##Usart.RxBuffer[(USART##Usart.RxHead + 2) % BufferLength] + 3) ;       \
            if((USART##Usart.RxTail - USART##Usart.RxHead + BufferLength) % BufferLength >= length)   \
            {                                                                                         \
                for(i = 0 ; i < length ; ++ i)               /*! 保存串口数据                   */    \
                {                                                                                     \
                    USART##RxBuffer[i] = USART##Usart.RxBuffer[USART##Usart.RxHead] ;                 \
                    USART_RenewalPointer(USART##Usart.RxHead) ;                                       \
                }                                                                                     \
                USART##_RxBuffer_Deal() ;                    /*! 串口数据处理*/                       \
                if(USART##Usart.RxFlag) return ;             /*! 重新收到数据，退出等待接收完毕 */    \
                if(USART##Usart.RxHead != USART##Usart.RxTail) goto Read_RxBuffer_Start ;             \
            }                                                                                         \
            else USART##Usart.RxHead = USART##Usart.RxTail ; /*! 更新指针                       */    \
        }                                                                                             \
        else if((USART##Usart.RxHead + 1) % BufferLength != USART##Usart.RxTail)                      \
        {                                                                                             \
            USART_RenewalPointer(USART##Usart.RxHead) ;                                               \
            goto Read_RxBuffer_Start ;                       /*! 更新指针从新判断               */    \
        }                                                                                             \
        else USART##Usart.RxHead = USART##Usart.RxTail ;     /*! 更新指针                       */    \
    }                                                                                                 \
}

extern UsartDataTypeDef Usart1 , Usart2 , Usart3 ;    //! 定义串口数据结构体

void USART1_Init(void) ;                     //! 串口1初始化
void USART2_Init(void) ;                     //! 串口2初始化
void USART3_Init(void) ;                     //! 串口3初始化
void USART1_Send_N_Byte(u8 *byte , uint32_t len); //! 串口1发送N个字节数据
void USART2_Send_N_Byte(u8 *byte , uint32_t len); //! 串口2发送N个字节数据
void USART3_Send_N_Byte(u8 *byte , uint32_t len); //! 串口3发送N个字节数据
void USART1_Send_String(char * chr) ;        //! 串口1发送字符串
void USART2_Send_String(char * chr) ;        //! 串口2发送字符串
void USART3_Send_String(char * chr) ;        //! 串口3发送字符串
void USART1_Send_Number(int number) ;        //! 串口1发送数据
void USART2_Send_Number(int number) ;        //! 串口2发送数据
void USART3_Send_Number(int number) ;        //! 串口3发送数据
void USART1_RxBufferDeal(void);              //! 串口1中断处理函数 测试用
void USART2_RxBufferDeal(void);              //! 串口2中断处理函数 测试用
void USART3_RxBufferDeal(void);              //! 串口3中断处理函数 测试用
void USART_Transmission_Deal(void) ;         //! 透传测试

#ifdef __cplusplus
}
#endif

#endif //! _USART_H_

