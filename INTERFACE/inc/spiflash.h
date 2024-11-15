/*******************************************************************************************************************
* @file    : spiflash.h
* 
* @date    : 2023/10/17
*
* @author  : science
*
* @version : V1.0
*
* @brief   : SPI FLASH操作
*
* @note    : 
**********************************************************************************************************************/ 
#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include "spi.h"

//! 跟底层引脚相关函数开始-------------------------------------------------------------------------------------------------

//! SPI flash CS引脚初始化
#define SPI_Flash_Chip_Select_Pin_Init()    GPIO_Init(GPIOB , 12 , GPIO_Mode_Out_OD) 

#define SPI_Flash_Chip_Select_Low()         PBout(12) = 0 
#define SPI_Flash_Chip_Select_High()        PBout(12) = 1

//! SPI硬件初始化
// #define SPI_Flash_SPI_Init()                SPI2_Init() ; SPI2_SetSpeed(7)
// #define SPI_Flash_Send_Byte                 SPI2_ReadWriteByte


#define SPI_Flash_SPI_Init()                GPIO_Init(GPIOB , 13 , GPIO_Mode_Out_OD) ;\
                                            GPIO_Init(GPIOB , 15 , GPIO_Mode_Out_OD) ;\
                                            GPIO_Init(GPIOB , 14 , GPIO_Mode_IPU)

#define SPI_Flash_Send_Byte                 SPI_Read_Write_Byte

#define SPI_SCK_LOW()     PBout(13) = 0
#define SPI_SCK_HIGH()    PBout(13) = 1

#define SPI_MOSI_LOW()    PBout(15) = 0
#define SPI_MOSI_HIGH()   PBout(15) = 1

#define SPI_MISO_DAT()    PBin(14)

static uint8_t SPI_Read_Write_Byte(uint8_t byt)
{
    uint8_t dat = 0 ; 

    for(int i = 0 ; i < 8 ; ++ i)
    {
        SPI_SCK_LOW() ; dat <<= 1 ; 

        if(byt & 0x80) { SPI_MOSI_HIGH() ; }
        else           { SPI_MOSI_LOW() ;  }

        SPI_SCK_HIGH() ; byt <<= 1 ; 

        if(SPI_MISO_DAT()) { dat |= 0x01 ; }
    }

    return dat ;
}
//! 跟底层引脚相关函数结束-------------------------------------------------------------------------------------------------


//! SPI Flash 芯片操作常用命令开始-----------------------------------------------------------------------------------------
#define FLASH_WRITE_ENABLE                  0x06
#define FLASH_WRITE_DISABLE                 0x04
#define FLASH_WRITE_STATUS_REG              0x01
#define FLASH_READ_STATUS_REG               0x05
#define FLASH_PAGE_PROGRAM                  0x02
#define FLASH_READ_DATA                     0x03
#define FLASH_SECTOR_ERASE                  0x20
#define FLASH_BLOCK_ERASE                   0xD8
#define FLASH_CHIP_ERASE                    0xC7
#define FLASH_READ_ID                       0x9F
//! SPI Flash 芯片操作常用命令结束-----------------------------------------------------------------------------------------

#define DUMMY_BYTE                          0xA5  //! 无关紧要数值--------------------------------------------------------

#define FLASH_PAGE_SIZE                     256   //! 一页FLASH数量------------------------------------------------------

#define FLASH_SECTOR_SIZE                   4096  //! 一个扇区大小--------------------------------------------------------

#define USE_ERASE_WRITE_FLAG                1     //! 是否使用连擦带写-----------------------------------------------------

/**
 * @brief  SPI Flash 硬件初始化
 */
void SPI_Flash_Init(void) ;

/**
 * @brief  读取状态寄存器的值
 * 
 * @return 状态值结果 
 */
uint8_t SPI_Flash_Read_SR(void) ;

/**
 * @brief  向状态寄存器写入参数
 * 
 * @param  val : 需要写入的值 
 */
void SPI_Flash_Write_SR(uint8_t val) ;

/**
 * @brief  使能写操作
 */
void SPI_Flash_Write_Enable(void) ;

/**
 * @brief  禁能写操作
 */
void SPI_Flash_Write_Disable(void) ;

/**
 * @brief  SPI Flash 等待芯片繁忙结束
 */
void SPI_Flash_Wait_Busy(void) ;

/**
 * @brief  擦除选择的片
 * 
 * @param  addr : 擦除地址
 */
void SPI_Flash_Sector_Erase(uint32_t addr) ;

/**
 * @brief  擦除选择的块
 * 
 * @param  addr : 擦除地址
 */
void SPI_Flash_Block_Erase(uint32_t addr) ;

/**
 * @brief  擦除整个芯片
 */
void SPI_Flash_Chip_Erase(void) ;

/**
 * @brief  读取芯片ID
 * 
 * @return ID值 
 */
uint32_t SPI_Flash_Read_ID(void) ;

/**
 * @brief  从某个地址开始擦除一定长度区域
 * 
 * @param  addr : 擦除首地址，必须是扇区的整数倍 
 * @param  len  : 需要擦除的长度 
 */
void SPI_Flash_Erase_N_Byte(uint32_t addr , uint32_t len) ;

/**
 * @brief  读取 N Byte 数据
 * 
 * @param  addr : 数据读取首地址
 * @param  buf  : 数据保存地址
 * @param  len  : 数据长度
 */
void SPI_Flash_Read_N_Byte(uint32_t addr , uint8_t * buf , uint32_t len) ;

/**
 * @brief  向指定地址页面写入数据
 * 
 * @param  addr : 数据写首地址
 * @param  buf  : 数据保存地址
 * @param  len  : 数据长度
 * 
 * @note   一页数据最多256个，若长度为256，则地址低字节为0 ， 另外，若地址不是整叶首地址，则长度应小于等于页剩余长度。
 */
void SPI_Flash_Write_Page(uint32_t addr , uint8_t * buf , uint32_t len) ;

/**
 * @brief   SPI FLASH从指定位置写数据
 *
 * @param   addr : 读取数据的地址
 * @param   buf  : 数据保存位置
 * @param   len  : 读取数据长读
 *
 * @note    必须确保所写的地址范围内的数据全部为0xFF,否则在非0XFF处写入的数据将失败!
 *          具有自动换页功能，在指定地址开始写入指定长度的数据,但是要确保地址不越界!
 **/
void SPI_Flash_Write_N_Byte(uint32_t addr , uint8_t * buf , uint32_t len) ;

/**
 * @brief  SPI FLASH 随意写数据
 * 
 * @param  addr : 需要写的地址
 * @param  buf  : 需要写的数组指针
 * @param  len  : 需要写的长度
 */
void SPI_Flash_Erase_Write_N_Byte(uint32_t addr , uint8_t * buf , uint32_t len) ;


#ifdef __cplusplus
}
#endif

#endif //! _SPI_FLASH_H_
