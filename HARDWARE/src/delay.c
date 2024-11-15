#include "delay.h"

/**
 * @brief 简单延时
 */
void Delay_N_us(int nus)
{
#ifdef SYSCLK_FREQ_36MHz
    #define TimeCount 50
#else 
    #define TimeCount 2
#endif
    int i  ;
    for( i = 0 ; i < (nus * TimeCount) ; i++) ;
#undef TimeCount
}

/**
 * @brief 简单延时
 */
void Delay_N_ms(int nms)
{
#ifdef SYSCLK_FREQ_36MHz
    #define TimeCount 6000
#else 
    #define TimeCount 2000
#endif
    int i , j ;
    for( i = 0 ; i < nms ; i++)
      for(j = 0 ; j < TimeCount ; j++) ;
#undef TimeCount
}
