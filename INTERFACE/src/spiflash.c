/*******************************************************************************************************************
* @file    : spiflash.c
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
#include "spiflash.h"

/**
 * @brief  SPI Flash 硬件初始化
 */
void SPI_Flash_Init(void)
{
    SPI_Flash_Chip_Select_Pin_Init() ; //! CS引脚初始化-----------------------------------------------------------------

    SPI_Flash_Chip_Select_High() ; //! CS不选中------------------------------------------------------------------------

    SPI_Flash_SPI_Init() ; //! SPI硬件初始化----------------------------------------------------------------------------
}

/**
 * @brief  读取状态寄存器的值
 * 
 * @return 状态值结果 
 */
uint8_t SPI_Flash_Read_SR(void)
{
    uint8_t val ;

    SPI_Flash_Chip_Select_Low() ; 

    SPI_Flash_Send_Byte(FLASH_READ_STATUS_REG) ;

    val = SPI_Flash_Send_Byte(DUMMY_BYTE) ;

    SPI_Flash_Chip_Select_High() ;

    return val ;
}

/**
 * @brief  向状态寄存器写入参数
 * 
 * @param  val : 需要写入的值 
 */
void SPI_Flash_Write_SR(uint8_t val)
{
    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_WRITE_STATUS_REG) ;

    SPI_Flash_Send_Byte(val) ;

    SPI_Flash_Chip_Select_High() ;
}

/**
 * @brief  使能写操作
 */
void SPI_Flash_Write_Enable(void)
{
    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_WRITE_ENABLE) ;

    SPI_Flash_Chip_Select_High() ;
}

/**
 * @brief  禁能写操作
 */
void SPI_Flash_Write_Disable(void)
{
    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_WRITE_DISABLE) ;

    SPI_Flash_Chip_Select_High() ;
}

/**
 * @brief  SPI Flash 等待芯片繁忙结束
 */
void SPI_Flash_Wait_Busy(void)
{
    //while((SPI_Flash_Read_SR() & 0x01) == 0x01) ;

    SPI_Flash_Chip_Select_Low() ; 

    SPI_Flash_Send_Byte(FLASH_READ_STATUS_REG) ;

    while(1)
    {
        uint8_t val = SPI_Flash_Send_Byte(DUMMY_BYTE) ;

        if((val & 0x01) == 0x00) { break ; }
    }

    SPI_Flash_Chip_Select_High() ;
}

/**
 * @brief  擦除选择的片
 * 
 * @param  addr : 擦除地址
 */
void SPI_Flash_Sector_Erase(uint32_t addr)
{
    SPI_Flash_Write_Enable() ;

    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_SECTOR_ERASE) ;

    SPI_Flash_Send_Byte((addr >> 16) & 0xFF) ;

    SPI_Flash_Send_Byte((addr >> 8) & 0xFF) ;

    SPI_Flash_Send_Byte(addr & 0xFF) ;

    SPI_Flash_Chip_Select_High() ;

    SPI_Flash_Wait_Busy() ;
}

/**
 * @brief  擦除选择的块
 * 
 * @param  addr : 擦除地址
 */
void SPI_Flash_Block_Erase(uint32_t addr)
{
    SPI_Flash_Write_Enable() ;

    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_BLOCK_ERASE) ;

    SPI_Flash_Send_Byte((addr >> 16) & 0xFF) ;

    SPI_Flash_Send_Byte((addr >> 8) & 0xFF) ;

    SPI_Flash_Send_Byte(addr & 0xFF) ;

    SPI_Flash_Chip_Select_High() ;

    SPI_Flash_Wait_Busy() ;
}

/**
 * @brief  擦除整个芯片
 */
void SPI_Flash_Chip_Erase(void)
{
    SPI_Flash_Write_Enable() ;

    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_CHIP_ERASE) ;

    SPI_Flash_Chip_Select_High() ;

    SPI_Flash_Wait_Busy() ;
}

/**
 * @brief  读取芯片ID
 * 
 * @return ID值 
 */
uint32_t SPI_Flash_Read_ID(void)
{
    uint32_t temp , temp0 , temp1 , temp2 ;

    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_READ_ID) ;

    temp0 = SPI_Flash_Send_Byte(DUMMY_BYTE) ;

    temp1 = SPI_Flash_Send_Byte(DUMMY_BYTE) ;

    temp2 = SPI_Flash_Send_Byte(DUMMY_BYTE) ;

    SPI_Flash_Chip_Select_High() ;

    temp = (temp0 << 16) | (temp1 << 8) | temp2 ;

    return temp ; 
}

/**
 * @brief  从某个地址开始擦除一定长度区域
 * 
 * @param  addr : 擦除首地址
 * @param  len  : 需要擦除的长度 
 */
void SPI_Flash_Erase_N_Byte(uint32_t addr , uint32_t len)
{
    uint32_t mod = addr % FLASH_SECTOR_SIZE ; 

    if(mod) { addr -= mod ; len += mod ; } 

    uint32_t erPage = (len + FLASH_SECTOR_SIZE - 1) / FLASH_SECTOR_SIZE ;

    for(int i = 0 ; i < erPage ; ++ i)
    {
        SPI_Flash_Sector_Erase(addr) ;

        addr += FLASH_SECTOR_SIZE ;
    }
}

/**
 * @brief  读取 N Byte 数据
 * 
 * @param  addr : 数据读取首地址
 * @param  buf  : 数据保存地址
 * @param  len  : 数据长度
 */
void SPI_Flash_Read_N_Byte(uint32_t addr , uint8_t * buf , uint32_t len)
{
    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_READ_DATA) ;

    SPI_Flash_Send_Byte((addr >> 16) & 0xFF) ;

    SPI_Flash_Send_Byte((addr >> 8) & 0xFF) ;

    SPI_Flash_Send_Byte(addr & 0xFF) ;

    while(len --) { * buf ++ = SPI_Flash_Send_Byte(DUMMY_BYTE) ; }

    SPI_Flash_Chip_Select_High() ;
}

/**
 * @brief  向指定地址页面写入数据
 * 
 * @param  addr : 数据写首地址
 * @param  buf  : 数据保存地址
 * @param  len  : 数据长度
 * 
 * @note   一页数据最多256个，若长度为256，则地址低字节为0 ， 另外，若地址不是整页首地址，则长度应小于等于页剩余长度。
 */
void SPI_Flash_Write_Page(uint32_t addr , uint8_t * buf , uint32_t len)
{
    SPI_Flash_Write_Enable() ;

    SPI_Flash_Chip_Select_Low() ;

    SPI_Flash_Send_Byte(FLASH_PAGE_PROGRAM) ;

    SPI_Flash_Send_Byte((addr >> 16) & 0xFF) ;

    SPI_Flash_Send_Byte((addr >> 8) & 0xFF) ;

    SPI_Flash_Send_Byte(addr & 0xFF) ;

    while(len --) { SPI_Flash_Send_Byte(* buf ++) ; }

    SPI_Flash_Chip_Select_High() ;

    SPI_Flash_Wait_Busy() ;
}

/**
 * @brief   SPI FLASH从指定位置写数据
 *
 * @param   addr : 读取数据的地址
 * @param   buf  : 数据保存位置
 * @param   len  : 读取数据长读
 *
 * @note    必须确保所写的地址范围内的数据全部为0xFF,否则在非0xFF处写入的数据将失败!
 *          具有自动换页功能，在指定地址开始写入指定长度的数据,但是要确保地址不越界!
 **/
void SPI_Flash_Write_N_Byte(uint32_t addr , uint8_t * buf , uint32_t len)
{
    if(addr % FLASH_PAGE_SIZE)
    {
        uint32_t sur = FLASH_PAGE_SIZE - (addr % FLASH_PAGE_SIZE) ;

        if(len <= sur)
        {
            SPI_Flash_Write_Page(addr , buf , len) ; return ;
        }
        else
        {
            SPI_Flash_Write_Page(addr , buf , sur) ;

            addr += sur ; buf += sur ; len -= sur ;
        }
    }

    while(len)
    {
        if(len <= FLASH_PAGE_SIZE)
        {
            SPI_Flash_Write_Page(addr , buf , len) ;

            break ;
        }
        else
        {
            SPI_Flash_Write_Page(addr , buf , FLASH_PAGE_SIZE) ;

            addr += FLASH_PAGE_SIZE ; buf += FLASH_PAGE_SIZE ; len -= FLASH_PAGE_SIZE ;
        }
    }
}

#if USE_ERASE_WRITE_FLAG == 1

uint8_t SpiFlashBuf[FLASH_SECTOR_SIZE] ;

/**
 * @brief  数组数据是否全是FF
 * 
 * @param  buf : 需要判断的数组
 * @param  len : 需要判断的长度
 * 
 * @return 0 : 数组中含非FF数据    1 : 数组中所有数据全为FF
 */
uint8_t SPI_Flash_Is_All_FF(uint8_t * buf , uint32_t len)
{
    for(uint32_t i = 0 ; i < len ; ++ i)
    {
        if(buf[i] != 0xFF) { return 0 ; }
    } return 1 ;
}

/**
 * @brief  SPI FLASH 随意写数据
 * 
 * @param  addr : 需要写的地址
 * @param  buf  : 需要写的数组指针
 * @param  len  : 需要写的长度
 */
void SPI_Flash_Erase_Write_N_Byte(uint32_t addr , uint8_t * buf , uint32_t len)
{
    uint32_t mod = addr % FLASH_SECTOR_SIZE , ct = FLASH_SECTOR_SIZE / FLASH_PAGE_SIZE ;

    if(mod)
    {
        uint32_t sur = FLASH_SECTOR_SIZE - mod , adr = addr - mod;

        SPI_Flash_Read_N_Byte(adr , SpiFlashBuf , FLASH_SECTOR_SIZE) ;

        if(SPI_Flash_Is_All_FF(SpiFlashBuf , FLASH_SECTOR_SIZE) == 0)
        {
            SPI_Flash_Sector_Erase(adr) ;
        }        

        if(len <= sur) { sur = len ; }
        
        for(uint32_t i = 0 ; i < sur ; ++ i) { SpiFlashBuf[i+mod] = buf[i] ; }

        for(int i = 0 ; i < ct ; ++ i) 
        { 
            SPI_Flash_Write_Page(adr + i * FLASH_PAGE_SIZE , &SpiFlashBuf[i * FLASH_PAGE_SIZE] , FLASH_PAGE_SIZE) ; 
        }

        if(len <= sur) { return ; }

        addr += sur ; buf += sur ; len -= sur ;
    }

    while(len)
    {
        if(len <= FLASH_SECTOR_SIZE)
        {
            SPI_Flash_Read_N_Byte(addr , SpiFlashBuf , FLASH_SECTOR_SIZE) ;

            if(SPI_Flash_Is_All_FF(SpiFlashBuf , FLASH_SECTOR_SIZE) == 0)
            {
                SPI_Flash_Sector_Erase(addr) ;
            }

            for(int i = 0 ; i < len ; ++ i) { SpiFlashBuf[i] = buf[i] ; }

            for(int i = 0 ; i < ct ; ++ i) 
            { 
                SPI_Flash_Write_Page(addr + i * FLASH_PAGE_SIZE , &SpiFlashBuf[i * FLASH_PAGE_SIZE] , FLASH_PAGE_SIZE) ; 
            }

            break ;
        }
        else
        {
            SPI_Flash_Read_N_Byte(addr , SpiFlashBuf , FLASH_SECTOR_SIZE) ;

            if(SPI_Flash_Is_All_FF(SpiFlashBuf , FLASH_SECTOR_SIZE) == 0)
            {
                SPI_Flash_Sector_Erase(addr) ;
            }

            for(int i = 0 ; i < FLASH_SECTOR_SIZE ; ++ i) { SpiFlashBuf[i] = buf[i] ; }

            for(int i = 0 ; i < ct ; ++ i) 
            { 
                SPI_Flash_Write_Page(addr + i * FLASH_PAGE_SIZE , &SpiFlashBuf[i * FLASH_PAGE_SIZE] , FLASH_PAGE_SIZE) ; 
            }

            addr += FLASH_SECTOR_SIZE ; buf += FLASH_SECTOR_SIZE ; len -= FLASH_SECTOR_SIZE ;
        }
    }
}

#endif
