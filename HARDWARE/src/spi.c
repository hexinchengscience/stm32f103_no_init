/****************************************************************************************
* 文件名称: spi.cpp
* 
* 创建时间：2021/07/01
*
* 修改时间：2021/07/01
*
* 作    者：science
*
* 版    本：V1.0
*
* 文摘描述：SPI通信
*
* 说    明：
****************************************************************************************/ 
#include "spi.h"

/**
 * @brief  SPI2初始化
 **/
void SPI2_Init(void)
{
    RCC -> APB2ENR |= 1 << 3 ;                 //! PORTB时钟使能    
    RCC -> APB1ENR |= 1 << 14 ;                //! SPI2时钟使能 
  
    GPIO_Init(GPIOB , 13 , GPIO_Mode_AF_OD) ;  //! PB13 复用输出
    GPIO_Init(GPIOB , 14 , GPIO_Mode_AF_OD) ;  //! PB14 复用输出
    GPIO_Init(GPIOB , 15 , GPIO_Mode_AF_OD) ;  //! PB15 复用输出
  
    SPI2 -> CR1 |= 0 << 10 ;    //! 全双工模式  
    SPI2 -> CR1 |= 1 << 9 ;     //! 软件nss管理
    SPI2 -> CR1 |= 1 << 8 ;  

    SPI2 -> CR1 |= 1 << 2 ;     //! SPI主机
    SPI2 -> CR1 |= 0 << 11 ;    //! 8bit数据格式  
    SPI2 -> CR1 |= 1 << 1 ;     //! 空闲模式下SCK为1 CPOL=1
    SPI2 -> CR1 |= 1 << 0 ;     //! 数据采样从第二个时间边沿开始,CPHA=1  
  
    SPI2 -> CR1 |= 3 << 3 ;     //! Fsck=Fpclk1/256
    SPI2 -> CR1 |= 0 << 7 ;     //! MSBfirst   
    SPI2 -> CR1 |= 1 << 6 ;     //! SPI设备使能
  
    SPI2_ReadWriteByte(0xFF) ;  //! 启动传输     
}

/**
 * @brief  SPI2设置速度
 *
 * @param  SpeedSet 速度  0-7
 *
 * @note   SPI速度 = fAPB1 / 2 ^ (SpeedSet + 1)
 *         APB1时钟一般为36Mhz
 **/
void SPI2_SetSpeed(u8 SpeedSet)
{
    SpeedSet &= 0x07 ;              //! 限制范围
    SPI2 -> CR1 &= 0xFFC7 ; 
    SPI2 -> CR1 |= SpeedSet << 3 ;  //! 设置SPI2速度  
    SPI2 -> CR1 |= 1 << 6 ;         //! SPI设备使能    
} 

/**
 * @brief  SPI2 读写一个字节
 *
 * @param  TxData  要写入的字节
 *
 * @retval 读取到的字节
 **/
u8 SPI2_ReadWriteByte(u8 TxData)
{    
    u16 retry = 0 ;         
    while((SPI2 -> SR & 1 << 1) == 0)    //! 等待发送区空  
    {
        retry++;
        if(retry >= 0xFFFE) return 0 ;   //! 超时退出
    }        
    SPI2 -> DR = TxData ;                 //! 发送一个byte 
    retry = 0 ;
    while((SPI2 -> SR & 1 << 0) == 0)   //! 等待接收完一个byte  
    {
        retry++;
        if(retry >= 0xFFFE) return 0 ;  //! 超时退出
    }                    
    return SPI2 -> DR ;                  //! 返回收到的数据            
}
