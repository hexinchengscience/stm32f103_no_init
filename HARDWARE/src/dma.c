/****************************************************************************************
* 文件名称: dma.cpp
* 
* 创建时间：2019/12/11
*
* 修改时间：2019/12/11
*
* 作    者：何鑫成
*
* 版    本：V1.0
*
* 文摘描述：DMA相关函数
*
* 说    明：
****************************************************************************************/ 
#include "dma.h" 

/**
 * @brief  DMA channel 1初始化
 **/
void DMA_Channel1_Init(void)
{
    RCC -> AHBENR |= 1 << 0 ;                 //! 开启DMA1时钟
    
    DMA1_Channel1 -> CPAR = (u32)&ADC1->DR ; //! DMA1 外设地址 
    DMA1_Channel1 -> CMAR = (u32)AdcValue ;  //! DMA1,存储器地址
  
    DMA1_Channel1 -> CNDTR = 2 ;             //! DMA1,传输数据量
    DMA1_Channel1 -> CCR = 0x00 ;             //! 复位
    DMA1_Channel1 -> CCR |= 1 << 1 ;         //! 允许传输完成中断
    DMA1_Channel1 -> CCR |= 0 << 4 ;         //! 从外设读
    DMA1_Channel1 -> CCR |= 1 << 5 ;         //! 循环模式
    DMA1_Channel1 -> CCR |= 0 << 6 ;          //! 外设地址非增量模式
    DMA1_Channel1 -> CCR |= 1 << 7 ;           //! 存储器增量模式
    DMA1_Channel1 -> CCR |= 1 << 8 ;           //! 外设数据宽度为8位
    DMA1_Channel1 -> CCR |= 1 << 10 ;        //! 存储器数据宽度8位
    DMA1_Channel1 -> CCR |= 1 << 12 ;        //! 中等优先级
    DMA1_Channel1 -> CCR |= 0 << 14 ;        //! 非存储器到存储器模式        
  
    NVIC->IP[DMA1_Channel1_IRQn]=0X1F;       //! 设置中断优先级       
    NVIC->ISER[DMA1_Channel1_IRQn >> 0x05] =(u32)0x01 << (DMA1_Channel1_IRQn & (u8)0x1F);
    
    DMA1_Channel1 -> CCR |= 1 << 0 ;         //! 开启DMA传输
}

