/****************************************************************************************
* 文件名称: flash.cpp
* 
* 创建时间：2019/12/12
*
* 修改时间：2020/12/02
*
* 作    者：science
*
* 版    本：V1.1
*
* 文摘描述：FLASH操作文件
*
* 说    明：
*          1、增加FLASH_Read_N_Byte和FLASH_Write_N_Byte函数
****************************************************************************************/ 
#include "flash.h"

/**
 * @brief  FLASH 解锁
 **/
void FLASH_Unlock(void)
{
    FLASH -> KEYR = FLASH_KEY1 ;  //! 写入解锁序列.
    FLASH -> KEYR = FLASH_KEY2 ;
}

/**
 * @brief  FLASH 上锁
 **/
void FLASH_Lock(void)
{
    FLASH -> CR |= 1 << 7 ;       //! 上锁
}

/**
 * @brief  FLASH 擦除页
 * @param  pageAddress 页地址  每页1024字节
 **/
void FLASH_ErasePage(u32 pageAddress)
{
    while(FLASH ->SR & 0x01) ;   //! 等待操作完成
    FLASH -> CR |= 1 << 1 ;      //! 页擦除
    FLASH -> AR = pageAddress ;  //! 设置页地址 
    FLASH -> CR |= 1 << 6 ;      //! 开始擦除    
  
    while(FLASH ->SR & 0x01) ;   //! 等待操作完成
    FLASH -> CR &= ~(1 << 1) ;   //! 清除页擦除标志.
}

/**
 * @brief  FLASH 写数据
 * @param  addr   数据地址
 *         dat    数据
 **/
void FLASH_Write_Word(u32 addr , u16 dat)
{
    while(FLASH ->SR & 0x01) ;   //! 等待操作完成
    FLASH -> CR |= 1 << 0 ;       //! 编程使能
    *(vu16 *) addr = dat ;       //! 写入数据  
  
    while(FLASH ->SR & 0x01) ;   //! 等待操作完成
    FLASH -> CR &= ~(1 << 0) ;   //! 清除PG位.
}

/**
 * @brief  FLASH 写数据例子
 **/
void FLASH_Write_Practice(void)
{
    FLASH_Unlock()                        ;
    FLASH_ErasePage(0x08004000)           ;
    FLASH_Write_Word(0x08004000 , 0x1122) ;
    FLASH_Write_Word(0x08004002 , 0xCCDD) ;
    FLASH_Write_Word(0x08004004 , 0xEEFF) ;
    FLASH_Write_Word(0x08004006 , 0x7788) ;
    FLASH_Write_Word(0x08004008 , 0x5566) ;
    FLASH_Write_Word(0x0800400A , 0x3344) ;
    FLASH_Lock()                          ;
}

/**
 * @brief  FLASH 从某个地址读取len长度的数据保存在byte中
 * @param  addr  : 读取的地址
 *         byte  : 保存数组
 *         len   : 读取的长度
 **/
void FLASH_Read_N_Byte(u32 addr , u8 * byte , u16 len)
{
    u32 paramAddr = addr ; 
    for(int i = 0 ; i < len ; ++ i) byte[i] = *(vu8 *) paramAddr ++ ;
}

/**
 * @brief  FLASH 将数据保存在指定地址的FLASH中
 * @param  addr  : 读取的地址
 *         byte  : 保存数组
 *         len   : 读取的长度  必须是偶数
 **/
void FLASH_Write_N_Byte(u32 addr , u8 * byte , u16 len)
{
    FLASH_Unlock() ;                         //! 解锁
    FLASH_ErasePage(addr) ;                  //! 擦除数据
    
    for(int i = 0 ; i < len / 2 ; ++ i)      //! 写数据
    {
        FLASH_Write_Word(addr + 2 * i , byte[2*i+1] * 256 + byte[2*i]) ;
    }
    FLASH_Lock() ;                           //! 关锁
}

