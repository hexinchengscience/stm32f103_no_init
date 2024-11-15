#ifndef __WDG_H__
#define __WDG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"

#include "STM32F103.h"

//!若defWdgPR=4  defWdgRLR=625 则喂狗时间为64(4对应分频数)*625/40K=1S
#define defWdgPR4      0       //! 4分频
#define defWdgPR8      1       //! 8分频
#define defWdgPR16     2       //! 16分频
#define defWdgPR32     3       //! 32分频
#define defWdgPR64     4       //! 64分频
#define defWdgPR128    5       //! 128分频
#define defWdgPR256    6       //! 256分频


#define defWdgPR    defWdgPR128 //! 预分频
#define defWdgRLR   625        //! 重装载数

void IWDG_Init(void) ;         //! 初始化
void IWDG_Feed(void) ;         //! 独立看门狗喂狗

#ifdef __cplusplus
}
#endif

#endif /*  __WDG_H__  */
