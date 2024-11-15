/****************************************************************************************
* 文件名称: device.c
* 
* 创建时间：2020/09/13
*
* 修改时间：2020/09/13
*
* 作    者：默先
*
* 版    本：V1.0
*
* 文摘描述：主控板外设程序
*
* 说    明：
****************************************************************************************/ 
#include "device.h"

/**
 * @brief  关闭外设输出
 **/
void Device_Output_Close(void)
{
   
}

/**
 * @brief  外设初始化
 **/
void Device_Init(void)
{
    RCC->APB2ENR|=1<<3;    //使能PORTB时钟      
    RCC->APB2ENR|=1<<4;    //使能PORTC时钟        
    RCC->APB2ENR|=1<<6;    //使能PORTE时钟  
        
    
    GPIO_Init(GPIOB , 5 , GPIO_Mode_Out_OD) ;
    GPIO_Init(GPIOE , 5 , GPIO_Mode_Out_OD) ;
}


/**
 * @brief  外设输出控制
 **/
void Device_Output(void)
{
  
}
