#ifndef _FLASH_H_
#define _FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"
#include "Cortex-M3.h"
#include "STM32F103.h"

//! FLASH解锁键值
#define FLASH_KEY1               0X45670123
#define FLASH_KEY2               0XCDEF89AB

/**
 * @brief  FLASH 解锁
 **/
void FLASH_Unlock(void) ;

/**
 * @brief  FLASH 上锁
 **/
void FLASH_Lock(void) ;

/**
 * @brief  FLASH 擦除页
 * @param  pageAddress 页地址  每页1024字节
 **/
void FLASH_ErasePage(u32 pageAddress) ;

/**
 * @brief  FLASH 写数据
 * @param  addr   数据地址
 *         dat    数据
 **/
void FLASH_Write_Word(u32 addr , u16 dat) ;

void FLASH_Read_N_Byte(u32 addr , u8 * byte , u16 len) ;   //! FLASH 读
void FLASH_Write_N_Byte(u32 addr , u8 * byte , u16 len) ;  //! FLASH 写

#ifdef __cplusplus
}
#endif
  
#endif //! _FLASH_H_

