/****************************************************************************************
* 文件名称: WDG.c
* 
* 创建时间：2019/11/27
*
* 修改时间：2019/12/09
*
* 作    者：默先
*
* 版    本：V1.0
*
* 文摘描述：STM32F103 看门狗
*
* 说    明：
****************************************************************************************/ 
#include "wdg.h"

/**
 * @brief 独立看门狗初始化
 */
void IWDG_Init(void)
{
    IWDG -> KR = 0x5555 ;       //! 允许访问IWDG_PR和IWDG_RLR寄存器
    IWDG -> PR = defWdgPR ;     //! 预分频寄存器
    IWDG -> RLR = defWdgRLR ;   //! 重装载寄存器
    IWDG -> KR = 0xAAAA ;       //! 喂狗寄存器值
    IWDG -> KR = 0xCCCC ;       //! 启动看门狗
}

/**
 * @brief 独立看门狗喂狗
 */
void IWDG_Feed(void)
{
    IWDG -> KR = 0xAAAA ;       //! 喂狗寄存器值
}