/****************************************************************************************
* 文件名称: interrupt.cpp
* 
* 创建时间：2019/12/07
*
* 修改时间：2019/12/07
*
* 作    者：hxc
*
* 版    本：V1.0
*
* 文摘描述：中断函数文件
*
* 说    明：中断函数必须加  extern "C"
****************************************************************************************/ 
#include "Cortex-M3.h"
#include "STM32F103.h"
#include "usart.h"
#include "delay.h"
#include "adc.h"

u32 SystemHeartbeatCount = 0 ;     //! 系统心跳时钟

//! 当串口接收到数据时，时间累积，以此判断接收一帧完成
//! 串口发送处理  当发送为1 结束为1时 发送数据
#define USART_RenewalFlag(USART , Usart) \
    if(Usart.RxFlag) Usart.RxTime ++ ;   \
    if(Usart.TxFlag && Usart.TxEnd)      \
    {                                    \
        Usart.TxEnd = 0 ;                \
        USART -> DR = Usart.TxBuffer[Usart.TxHead] ;\
    }

/**
 * @brief  SysTick定时器中断 1ms 进入一次
 **/
void SysTick_Handler(void)  
{
    SystemHeartbeatCount ++ ;                   //! 更新心跳
    USART_RenewalFlag(USART1 , Usart1) ;        //! 更新串口1状态
    USART_RenewalFlag(USART2 , Usart2) ;        //! 更新串口2状态
    USART_RenewalFlag(USART3 , Usart3) ;        //! 更新串口3状态
  
}

/**
 * @brief  串口中断处理函数
 **/
#define USART_IRQHandler(USART , Usart)                 \
{                                                       \
    if(USART -> SR & (1 <<5 )) /*! 判断是否是接收中断 */\
    {                                                   \
        Usart.RxBuffer[Usart.RxTail] = USART -> DR ;    \
        USART_RenewalPointer(Usart.RxTail) ;            \
        Usart.RxFlag = 1 ; Usart.RxTime = 0 ;           \
    }                                                   \
    if(USART -> SR & (1 << 6)) /*! 判断是否是发送中断 */\
    {                                                   \
      USART -> SR &= ~(1 <<6) ; /*! 软件清除发送中断  */\
        USART_RenewalPointer(Usart.TxHead) ;            \
        if(Usart.TxHead != Usart.TxTail)                \
          USART -> DR = Usart.TxBuffer[Usart.TxHead] ;  \
        else {Usart.TxFlag = 0 ; Usart.TxEnd = 1 ; }    \
    }                                                   \
} 

/**
 * @brief  串口1中断处理函数
 **/
void USART1_IRQHandler(void)              
{
    USART_IRQHandler(USART1 , Usart1) ;
} 

/**
 * @brief  串口2中断处理函数
 **/
void USART2_IRQHandler(void)              
{
    USART_IRQHandler(USART2 , Usart2) ;
} 

/**
 * @brief  串口3中断处理函数
 **/
void USART3_IRQHandler(void)              
{
    USART_IRQHandler(USART3 , Usart3) ;
} 

/**
 * @brief  定时器2中断函数 0.1ms进一次中断
 **/
void TIM2_IRQHandler(void)
{                     
    if(TIM2->SR&0x0001)    /*  溢出中断        */
    {
        
    }           
    TIM2->SR&=~(1<<0);     /* 清除中断标志位    */   
}

