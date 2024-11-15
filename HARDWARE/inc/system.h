/****************************************************************************************
* 文件名称: system.h
* 
* 创建时间：2019/11/27
*
* 修改时间：2019/12/09
*
* 作    者：science
*
* 版    本：V1.0
*
* 文摘描述：STM32F103 系统函数，中断分组  嘀嗒时钟函数
****************************************************************************************/ 
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"

#include "Cortex-M3.h"
#include "STM32F103.h"
#include "usart.h"
#include "arithmetic.h" 

//! 断言处理*******************************************************************************************
#define USE_FULL_ASSERT    1   //! 是否使用断言，如果不使用，注释掉这行代码
#if (USE_FULL_ASSERT == 1)
  #define Assert_Send_N_Byte   USART1_Send_N_Byte   //! 断言串口打印数据串口号
  #define Assert_Param(expr) ((expr) ? (void)0 : Assert_Failed((u8 *)__FILE__, __LINE__))
  void Assert_Failed(u8 * file , u32 line) ; //! 断言错误处理，一般打印文件名和行号
#else
  #define Assert_Param(expr) ((void)0)       //! 这里使用大写为了和一些库的断言进行区分
#endif  //! USE_FULL_ASSERT 
//! ***************************************************************************************************

#define SYSCLK_FREQ_36MHz 36000000           //! 是否使用系统时钟36M，屏蔽时系统时钟为8M

#define SysclkFrequency  SYSCLK_FREQ_36MHz   //! 定义系统时钟

//! 定义串口波特率****************************************************************************************
#define BaudRate9600    SysclkFrequency / 9600
#define BaudRate14400   SysclkFrequency / 14400
#define BaudRate19600   SysclkFrequency / 19600
#define BaudRate38400   SysclkFrequency / 38400
#define BaudRate56000   SysclkFrequency / 56000
#define BaudRate57600   SysclkFrequency / 57600
#define BaudRate115200  SysclkFrequency / 115200
#define BaudRate194000  SysclkFrequency / 194000

//! 定义中断优先级，这里只是一个简单的定义******************************************************************
//    NVIC -> IP[USB_LP_CAN1_RX0_IRQn] = 0x1F ;    /*! 设置中断优先级    */
//    NVIC->ISER[USB_LP_CAN1_RX0_IRQn >> 0x05] =(u32)0x01 << (USB_LP_CAN1_RX0_IRQn & (u8)0x1F);
#define NVIC_Set_IRQn(IRQn,Priority) NVIC->IP[IRQn]=Priority;NVIC->ISER[IRQn>>0x05]=(u32)0x01<<(IRQn&(u8)0x1F);

extern u32 SystemHeartbeatCount ;   //! 系统心跳时钟
extern u16 MicroElectricCount ;     //! 微电心跳变量

void System_Init(void) ;            //! 系统时钟初始化
void System_Reset(void) ;           //! 系统软件复位
void NVIC_Configuration(void) ;     //! 设置NVIC中断分组
void SysTick_Init(void) ;           //! SysTick定时器初始化

#ifdef __cplusplus
}
#endif

#endif //! _SYSTEM_H_

