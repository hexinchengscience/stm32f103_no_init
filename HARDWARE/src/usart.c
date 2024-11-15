/****************************************************************************************
* 文件名称: uart.c
* 
* 创建时间：2019/11/27
*
* 修改时间：2019/12/19
*
* 作    者：science
*
* 版    本：V1.5
*
* 文摘描述：STM32F103 串口函数
*
* 说    明：20191128 : 串口发送中断配置好后会自动进入一次中断，原因未知，影响不大，待解决
*           20191219 : 重新整理串口初始化，发送函数
*           20210105 : 整理串口函数
*           20210225 : 串口发送函数，当数据发送数组满之后，会出现串口死机情况，增加等待判断解决问题，会增加等待时间
*           20210318 : 增加串口透传函数
*           20210515 : 增加串口发送字符串函数，字符串必须以 /0 结尾
*           20210516 : 增加串口发送数字函数  整理串口发送接收函数
****************************************************************************************/ 
#include "usart.h"

UsartDataTypeDef Usart1 ;             //! 定义串口1数据结构体
UsartDataTypeDef Usart2 ;             //! 定义串口2数据结构体
UsartDataTypeDef Usart3 ;             //! 定义串口3数据结构体

/**
 * @brief  串口初始化
 **/
#define USART_Init(USART , Usart)                                \
    USART -> BRR = USART##_BaudRate ;    /*! 设置波特率        */\
    USART -> CR1 &= ~(1 << 6) ;          /*! 清发送中断使能    */\
    USART -> CR1 |= 1 << 2 ;             /*! 接收使能          */\
    USART -> CR1 |= 1 << 3 ;             /*! 发送使能          */\
    USART -> CR1 |= 1 << 5 ;             /*! 接收中断          */\
    USART -> CR1 |= 1 << 6 ;             /*! 发送中断          */\
    USART -> CR1 |= 1 << 13 ;            /*! 串口使能          */\
    USART -> SR &= ~(1 << 6) ;           /*! 清发送中断        */\
    Usart.RxHead = 0 ; Usart.RxTail = 0 ;/*! 设置初始值        */\
    Usart.TxHead = 0 ; Usart.TxTail = 1 ;/*! 设置初始值        */\
    Usart.TxFlag = 0 ; Usart.TxEnd  = 1 ;/*! 设置初始值        */\
    Usart.RxFlag = 0 ; Usart.RxTime = 6 ;/*! 设置初始值        */\
    NVIC -> IP[USART##_IRQn] = 0x1F ;    /*! 设置中断优先级    */\
    NVIC->ISER[USART##_IRQn >> 0x05] =(u32)0x01 << (USART##_IRQn & (u8)0x1F);


/**
 * @brief  串口1初始化
 **/
void USART1_Init(void)
{
    RCC -> APB2ENR |= 1<< 14 ;                //! 使能串口1时钟    
    RCC -> APB2ENR |= 1 << 2 ;                //! 打开A口时钟
  
    GPIO_Init(GPIOA , 9 , GPIO_Mode_AF_OD) ;  //! PA9  TX 推挽输出
    GPIO_Init(GPIOA , 10 , GPIO_Mode_IPD) ;   //! PA10 RX 上拉输入
    
    RCC -> APB2RSTR |= 1 << 14 ;              //! 复位串口1   
    RCC -> APB2RSTR &= ~( 1 << 14);           //! 停止复位    
  
    USART_Init(USART1 , Usart1) ;             //! 串口初始化
}

/**
 * @brief  串口2初始化
 **/
void USART2_Init(void)
{
    RCC -> APB1ENR |= 1<< 17 ;                //! 使能串口1时钟    
    RCC -> APB2ENR |= 1 << 2 ;                //! 打开A口时钟
  
    GPIO_Init(GPIOA , 2 , GPIO_Mode_AF_OD) ;  //! PA2  TX 推挽输出
    GPIO_Init(GPIOA , 3 , GPIO_Mode_IPD) ;    //! PA3  RX 上拉输入
    
    RCC -> APB1RSTR |= 1 << 17 ;              //! 复位串口2
    RCC -> APB1RSTR &= ~( 1 << 17);           //! 停止复位    
  
    USART_Init(USART2 , Usart2) ;             //! 串口初始化 
}

/**
 * @brief  串口3初始化
 **/
void USART3_Init(void)
{
    RCC -> APB1ENR |= 1 << 18;                //! 使能串口3时钟   
    RCC -> APB2ENR |= 1 << 3 ;                //! 打开B口时钟
  
    GPIO_Init(GPIOB , 10 , GPIO_Mode_AF_OD) ; //! PB10 TX 推挽输出
    GPIO_Init(GPIOB , 11 , GPIO_Mode_IPD) ;   //! PB11 RX 上拉输入
  
    RCC -> APB1RSTR |= 1 << 18 ;              //! 复位串口3       
    RCC -> APB1RSTR &= ~(1 << 18) ;           //! 停止复位        
  
    USART_Init(USART3 , Usart3) ;             //! 串口初始化
}

/**
 * @brief  串口发送N个字节数据
 * @param  Usart: 串口结构体
 *         byte : 需要发送的数据
 *         len  : 数据长度 
 *
 * @note   串口发送函数，当数据发送数组满之后，会出现串口死机情况
 *         增加等待判断 while(Usart.TxTail == Usart.TxHead) 解决问题，会增加等待时间
 *         在while循环中还可以加上 Usart.TxFlag = 1 ; 语句，预防第一次调用函数就超数组
 *         理论上不会出现这种情况，这个地方没有加。
 **/
#define USART_Send_N_Byte(Usart , byte , len)      \
{                                                  \
    for(int i = 0 ; i < len ; ++ i)                \
    {                                              \
        Usart.TxBuffer[Usart.TxTail] = byte[i] ;   \
        USART_RenewalPointer(Usart.TxTail) ;       \
        while(Usart.TxTail == Usart.TxHead) ;      \
    }                                              \
    Usart.TxFlag = 1 ;                             \
}

/**
 * @brief  串口发送N个字节字符串
 * @param  Usart: 串口结构体
 *         chr  : 需要发送的字符串
 *
 * @note   字符串末尾必须是以 /0 结束
 **/
#define USART_Send_String(Usart , chr)             \
{                                                  \
    for(int i = 0 ; chr[i] ; ++ i)                 \
    {                                              \
        Usart.TxBuffer[Usart.TxTail] = chr[i] ;    \
        USART_RenewalPointer(Usart.TxTail) ;       \
        while(Usart.TxTail == Usart.TxHead) ;      \
    }                                              \
    Usart.TxFlag = 1 ;                             \
}

/**
 * @brief  串口发送数字
 * @param  number  : 需要发送的数字
 **/
#define USART_Send_Number(Usart , number)      \
{                                              \
    char chr[12] = {0,0,0,0,0,0,0,0,0,0,0,0} ; \
    NumberToChar(number , chr) ;               \
    USART_Send_String(Usart , chr) ;           \
}

/**
* @brief  串口1中断处理函数 ，测试使用，发送接收到的书
 **/
#define USART_RxBufferDeal(USART , Usart)                \
{                                                        \
    u8 RxBuffer[128] ;                                   \
    if(Usart.RxFlag && Usart.RxTime > defRxOverTime)     \
    {                                                    \
        int i = 0 ;                                      \
        Usart.RxFlag = 0 ;                               \
        for( ; Usart.RxHead != Usart.RxTail ; ++ i)      \
        {                                                \
            RxBuffer[i] = Usart.RxBuffer[Usart.RxHead] ; \
            USART_RenewalPointer(Usart.RxHead) ;         \
        }                                                \
        USART##_Send_N_Byte(RxBuffer , i) ;              \
    }                                                    \
}

/**
* @brief  串口发送和接收相关函数
 **/
#define Usart_TxRx_Function(n)                       \
void USART##n##_Send_N_Byte(u8 *byte , uint32_t len) \
{                                                    \
    USART_Send_N_Byte(Usart##n , byte , len) ;       \
}                                                    \
void USART##n##_Send_String(char * chr)              \
{                                                    \
    USART_Send_String(Usart##n , chr) ;              \
}                                                    \
void USART##n##_Send_Number(int number)              \
{                                                    \
    USART_Send_Number(Usart##n , number) ;           \
}                                                    \
void USART##n##_RxBufferDeal(void)                   \
{                                                    \
    USART_RxBufferDeal(USART##n , Usart##n) ;        \
}

Usart_TxRx_Function(1) Usart_TxRx_Function(2) Usart_TxRx_Function(3) 

/**
 * @brief  串口n1收到数据后，将数据通过串口2发送出去
 **/
#define USART_Transmission_RxBuffer(n1 , n2)                           \
{                                                                      \
    if(Usart##n1.RxFlag && Usart##n1.RxTime > defRxOverTime)           \
    {                                                                  \
        Usart##n1.RxFlag = 0 ; Usart##n2.TxHead = Usart##n1.RxHead ;   \
        Usart##n2.TxTail = Usart##n1.RxHead ;                          \
        for( ; Usart##n1.RxHead != Usart##n1.RxTail ; )                \
        {                                                              \
            Usart##n2.TxBuffer[Usart##n2.TxTail] = Usart##n1.RxBuffer[Usart##n1.RxHead] ;  \
            USART_RenewalPointer(Usart##n1.RxHead) ;                   \
            USART_RenewalPointer(Usart##n2.TxTail) ;                   \
        }                                                              \
        Usart##n2.TxFlag = 1 ;                                         \
    }                                                                  \
}

/**
 * @brief  串口透传测试 有 defRxOverTime * 2 时间延迟
 **/
void USART_Transmission_Deal(void)
{
    USART_Transmission_RxBuffer(1 , 2) ;
    USART_Transmission_RxBuffer(2 , 1) ;
}


//! 若串口使用printf函数，又不使用 Micro LIB ,加入以下代码*******************************************************
#ifdef __CC_ARM                      //! MDK 重写函数，供printf使用-------------------------------------------
struct __FILE { int handle; }; 
FILE __stdout ;                      /*! FILE is typedef’ d in stdio.h.             */ 
void _sys_exit(int x) { x = x ; }    /*! 定义_sys_exit()以避免使用半主机模式        */
void _ttywrch(int ch) { ch = ch ; }
int fputc(int ch , FILE *f)          /*! 重新定义 fputc ,就是发送一个字节数据函数   */
{
    u8 chr = ch ;
    USART1_Send_N_Byte(&chr , 1) ;
    return ch ;
}           
#endif

#ifdef __ICCARM                      //! IAR 重写函数，供printf使用------------------------------------------
int putchar(int c)
{
    USART1_Send_N_Byte(&c , 1) ;
    return c ;
}
#endif

#ifdef __GNUC__                      //! GCC 重写write函数，供printf使用-------------------------------------
int _write (int fd, char *pBuffer, int size)  
{  
    USART1_Send_N_Byte((uint8_t *)pBuffer , size) ;
    return size;  
}
#endif

//! 若串口使用printf函数，又不使用 Micro LIB ,加入以上代码*******************************************************
