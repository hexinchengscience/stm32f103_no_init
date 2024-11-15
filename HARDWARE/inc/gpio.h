#ifndef _GPIO_H_
#define _GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "Cortex-M3.h"
#include "STM32F103.h"

/** 
  * @brief  Configuration Mode enumeration  
  */
typedef enum
{ 
    GPIO_Mode_AIN         = 0x00,     //! 模拟输入模式
    GPIO_Mode_IN_FLOATING = 0x04,     //! 浮空输入
    GPIO_Mode_IPD         = 0x08,     //! 下拉输入
    GPIO_Mode_IPU         = 0x08,     //! 上拉输入
    GPIO_Mode_Out_OD      = 0x03,     //! 通用推挽输出
    GPIO_Mode_Out_PP      = 0x07,     //! 通用开漏输出
    GPIO_Mode_AF_OD       = 0x0B,     //! 复用推挽输出
    GPIO_Mode_AF_PP       = 0x0F      //! 复用开漏输出
}GPIOMode_TypeDef;

//! 一些特殊引脚初始化**********************************************************************************************************
#define defPBout3Init()       {RCC->APB2ENR |= 1 << 0 ; AFIO -> MAPR |= (1 << 8) ; GPIO_Init(GPIOB , 3 , GPIO_Mode_Out_OD) ; }  //! PB3推挽输出

#define defPAout15Init()      {RCC->APB2ENR |= 1 << 0 ; AFIO -> MAPR |= (2 << 24) ; GPIO_Init(GPIOA , 15 , GPIO_Mode_Out_OD) ;} //! PA15推挽输出

void GPIO_Init(GPIO_TypeDef * gpio , u8 pin , GPIOMode_TypeDef mode) ;  //! IO口初始化

#ifdef __cplusplus
}
#endif

#endif //! _GPIO_H_
