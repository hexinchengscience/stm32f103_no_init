/*******************************************************************************************************************
* @file    : sd.h
* 
* @date    : 2023/11/02
*
* @author  : science
*
* @version : V1.0
*
* @brief   : SPI SD
*
* @note    : 
**********************************************************************************************************************/ 
#ifndef _SD_H_
#define _SD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>

#include "DataType.h"
#include "STM32F103.h"
#include "system.h"
#include "gpio.h"
#include "delay.h"

//! 跟底层引脚相关函数开始-------------------------------------------------------------------------------------------------

#define SD_SPI_Init()                GPIO_Init(GPIOB , 12 , GPIO_Mode_Out_OD) ;\
                                     GPIO_Init(GPIOB , 13 , GPIO_Mode_Out_OD) ;\
                                     GPIO_Init(GPIOB , 15 , GPIO_Mode_Out_OD) ;\
                                     GPIO_Init(GPIOB , 14 , GPIO_Mode_IPU) ;   \
                                     SD_SPI_CS_High()

#define SD_SPI_CS_Low()              PBout(12) = 0 
#define SD_SPI_CS_High()             PBout(12) = 1

#define SD_SPI_SCK_LOW()             PBout(13) = 0
#define SD_SPI_SCK_HIGH()            PBout(13) = 1

#define SD_SPI_MOSI_LOW()            PBout(15) = 0
#define SD_SPI_MOSI_HIGH()           PBout(15) = 1

#define SD_SPI_MISO_DAT()            PBin(14)

static uint8_t SD_SPI_Read_Write_Byte(uint8_t byt)
{
    uint8_t dat = 0 ; 

    for(int i = 0 ; i < 8 ; ++ i)
    {
        SD_SPI_SCK_LOW() ; dat <<= 1 ; 

        if(byt & 0x80) { SD_SPI_MOSI_HIGH() ; }
        else           { SD_SPI_MOSI_LOW() ;  }

        SD_SPI_SCK_HIGH() ; byt <<= 1 ; 

        if(SD_SPI_MISO_DAT()) { dat |= 0x01 ; }
    }

    return dat ;
}
//! 跟底层引脚相关函数结束-------------------------------------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

#endif //! _SD_H_

