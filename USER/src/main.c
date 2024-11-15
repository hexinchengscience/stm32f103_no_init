/****************************************************************************************
* 文件名称: main.c
* 
* 创建时间：2019/12/03
*
* 修改时间：2019/12/03
*
* 作    者：默先
*
* 版    本：V1.0
*
* 文摘描述：主函数文件
*
* 说    明：
****************************************************************************************/ 
#include "main.h"
#include "SEGGER_RTT.h"

#define __no_init attribute((zero_init))
//unsigned long num __attribute__(( section( "NO_INIT"),zero_init)) ;
unsigned long num __attribute__((at(0x20000000))) ;

uint32_t var = 0 ;

/**
 * @brief  主函数
 **/
int main(void)
{
    NVIC_Configuration() ;          //! 设置中断分组
    SysTick_Init() ;                //! SysTick定时器初始化
    TIM2_Init(99 , 35) ;            //! 定时器初始化 
    USART1_Init() ;                 //! 串口1初始化
    USART2_Init() ;                 //! 串口2初始化
    USART3_Init() ;                 //! 串口3初始化
    Device_Init() ;                 //! 外设输出初始化

	SEGGER_RTT_Init();
	
	SEGGER_RTT_printf(0, "program start !\r\n") ;
	
    while(1) 
    {
		    SEGGER_RTT_printf(0, "num = %u\r\n", num );
		var ++ ;
		if(var > 10) { num ++ ; System_Reset() ; }
//			
//			  SEGGER_RTT_Write(0 , byt , 10) ;
		
        LED0 = !LED0 ; Delay_N_ms(500) ; LED1 = !LED1 ; 
    }
}

