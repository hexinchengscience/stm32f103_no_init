/****************************************************************************************
* 文件名称: STM32F103.h
* 
* 创建时间：2019/12/03
*
* 修改时间：2021/04/11
*
* 作    者：science
*
* 版    本：V1.3
*
* 文摘描述：STM32F103 寄存器结构体文件
*
* 说    明：2020/08/21  增加独立看门狗结构体
*           2021/04/11  增加CAN数据结构体
****************************************************************************************/ 
#ifndef __STM32F103_H__
#define __STM32F103_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"

#define FLASH_BASE            ((u32)0x08000000) /*!< FLASH base address in the alias region */
#define SRAM_BASE             ((u32)0x20000000) /*!< SRAM base address in the alias region */
#define PERIPH_BASE           ((u32)0x40000000) /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE          ((u32)0x22000000) /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE        ((u32)0x42000000) /*!< Peripheral base address in the bit-band region */

#define FSMC_R_BASE           ((u32)0xA0000000) /*!< FSMC registers base address */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)


/**
 * @brief STM32F10x Interrupt Number Definition, according to the selected device 
 *        in @ref Library_configuration_section 
 */
typedef enum IRQn
{
/******  Cortex-M3 Processor Exceptions Numbers *****************************************************/
    NonMaskableInt_IRQn         = -14,    /*!< 2 Non Maskable Interrupt                             */
    MemoryManagement_IRQn       = -12,    /*!< 4 Cortex-M3 Memory Management Interrupt              */
    BusFault_IRQn               = -11,    /*!< 5 Cortex-M3 Bus Fault Interrupt                      */
    UsageFault_IRQn             = -10,    /*!< 6 Cortex-M3 Usage Fault Interrupt                    */
    SVCall_IRQn                 = -5,     /*!< 11 Cortex-M3 SV Call Interrupt                       */
    DebugMonitor_IRQn           = -4,     /*!< 12 Cortex-M3 Debug Monitor Interrupt                 */
    PendSV_IRQn                 = -2,     /*!< 14 Cortex-M3 Pend SV Interrupt                       */
    SysTick_IRQn                = -1,     /*!< 15 Cortex-M3 System Tick Interrupt                   */

/******  STM32 specific Interrupt Numbers ***********************************************************/
    WWDG_IRQn                   = 0,      /*!< Window WatchDog Interrupt                            */
    PVD_IRQn                    = 1,      /*!< PVD through EXTI Line detection Interrupt            */
    TAMPER_IRQn                 = 2,      /*!< Tamper Interrupt                                     */
    RTC_IRQn                    = 3,      /*!< RTC global Interrupt                                 */
    FLASH_IRQn                  = 4,      /*!< FLASH global Interrupt                               */
    RCC_IRQn                    = 5,      /*!< RCC global Interrupt                                 */
    EXTI0_IRQn                  = 6,      /*!< EXTI Line0 Interrupt                                 */
    EXTI1_IRQn                  = 7,      /*!< EXTI Line1 Interrupt                                 */
    EXTI2_IRQn                  = 8,      /*!< EXTI Line2 Interrupt                                 */
    EXTI3_IRQn                  = 9,      /*!< EXTI Line3 Interrupt                                 */
    EXTI4_IRQn                  = 10,     /*!< EXTI Line4 Interrupt                                 */
    DMA1_Channel1_IRQn          = 11,     /*!< DMA1 Channel 1 global Interrupt                      */
    DMA1_Channel2_IRQn          = 12,     /*!< DMA1 Channel 2 global Interrupt                      */
    DMA1_Channel3_IRQn          = 13,     /*!< DMA1 Channel 3 global Interrupt                      */
    DMA1_Channel4_IRQn          = 14,     /*!< DMA1 Channel 4 global Interrupt                      */
    DMA1_Channel5_IRQn          = 15,     /*!< DMA1 Channel 5 global Interrupt                      */
    DMA1_Channel6_IRQn          = 16,     /*!< DMA1 Channel 6 global Interrupt                      */
    DMA1_Channel7_IRQn          = 17,     /*!< DMA1 Channel 7 global Interrupt                      */

    ADC1_2_IRQn                 = 18,     /*!< ADC1 and ADC2 global Interrupt                       */
    USB_HP_CAN1_TX_IRQn         = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts       */
    USB_LP_CAN1_RX0_IRQn        = 20,     /*!< USB Device Low Priority or CAN1 RX0 Interrupts       */
    CAN1_RX1_IRQn               = 21,     /*!< CAN1 RX1 Interrupt                                   */
    CAN1_SCE_IRQn               = 22,     /*!< CAN1 SCE Interrupt                                   */
    EXTI9_5_IRQn                = 23,     /*!< External Line[9:5] Interrupts                        */
    TIM1_BRK_IRQn               = 24,     /*!< TIM1 Break Interrupt                                 */
    TIM1_UP_IRQn                = 25,     /*!< TIM1 Update Interrupt                                */
    TIM1_TRG_COM_IRQn           = 26,     /*!< TIM1 Trigger and Commutation Interrupt               */
    TIM1_CC_IRQn                = 27,     /*!< TIM1 Capture Compare Interrupt                       */
    TIM2_IRQn                   = 28,     /*!< TIM2 global Interrupt                                */
    TIM3_IRQn                   = 29,     /*!< TIM3 global Interrupt                                */
    TIM4_IRQn                   = 30,     /*!< TIM4 global Interrupt                                */
    I2C1_EV_IRQn                = 31,     /*!< I2C1 Event Interrupt                                 */
    I2C1_ER_IRQn                = 32,     /*!< I2C1 Error Interrupt                                 */
    I2C2_EV_IRQn                = 33,     /*!< I2C2 Event Interrupt                                 */
    I2C2_ER_IRQn                = 34,     /*!< I2C2 Error Interrupt                                 */
    SPI1_IRQn                   = 35,     /*!< SPI1 global Interrupt                                */
    SPI2_IRQn                   = 36,     /*!< SPI2 global Interrupt                                */
    USART1_IRQn                 = 37,     /*!< USART1 global Interrupt                              */
    USART2_IRQn                 = 38,     /*!< USART2 global Interrupt                              */
    USART3_IRQn                 = 39,     /*!< USART3 global Interrupt                              */
    EXTI15_10_IRQn              = 40,     /*!< External Line[15:10] Interrupts                      */
    RTCAlarm_IRQn               = 41,     /*!< RTC Alarm through EXTI Line Interrupt                */
    USBWakeUp_IRQn              = 42,      /*!< USB Device WakeUp from suspend through EXTI Line Interrupt */  
    TIM8_BRK_IRQn               = 43,     /*!< TIM8 Break Interrupt                                 */
    TIM8_UP_IRQn                = 44,     /*!< TIM8 Update Interrupt                                */
    TIM8_TRG_COM_IRQn           = 45,     /*!< TIM8 Trigger and Commutation Interrupt               */
    TIM8_CC_IRQn                = 46,     /*!< TIM8 Capture Compare Interrupt                       */
    ADC3_IRQn                   = 47,     /*!< ADC3 global Interrupt                                */
    FSMC_IRQn                   = 48,     /*!< FSMC global Interrupt                                */
    SDIO_IRQn                   = 49,     /*!< SDIO global Interrupt                                */
    TIM5_IRQn                   = 50,     /*!< TIM5 global Interrupt                                */
    SPI3_IRQn                   = 51,     /*!< SPI3 global Interrupt                                */
    UART4_IRQn                  = 52,     /*!< UART4 global Interrupt                               */
    UART5_IRQn                  = 53,     /*!< UART5 global Interrupt                               */
    TIM6_IRQn                   = 54,     /*!< TIM6 global Interrupt                                */
    TIM7_IRQn                   = 55,     /*!< TIM7 global Interrupt                                */
    DMA2_Channel1_IRQn          = 56,     /*!< DMA2 Channel 1 global Interrupt                      */
    DMA2_Channel2_IRQn          = 57,     /*!< DMA2 Channel 2 global Interrupt                      */
    DMA2_Channel3_IRQn          = 58,     /*!< DMA2 Channel 3 global Interrupt                      */
    DMA2_Channel4_5_IRQn        = 59      /*!< DMA2 Channel 4 and Channel 5 global Interrupt        */
} IRQn_Type;

/** 
  * @brief Reset and Clock Control
  */
typedef struct
{
    vu32 CR;
    vu32 CFGR;
    vu32 CIR;
    vu32 APB2RSTR;
    vu32 APB1RSTR;
    vu32 AHBENR;
    vu32 APB2ENR;
    vu32 APB1ENR;
    vu32 BDCR;
    vu32 CSR;
    vu32 AHBRSTR;
    vu32 CFGR2;
} RCC_TypeDef;

#define RCC  ((RCC_TypeDef *)0x40021000)

/** 
  * @brief General Purpose I/O   GPIO口数据结构
  */
typedef struct
{
    vu32  CRL;          /* 端口配置低寄存器，0-7引脚       */
    vu32  CRH;          /* 端口配置高寄存器，8-15引脚      */
    vuc32 IDR;          /* 端口输入数据寄存器，低位有效    */
    vu32  ODR;          /* 端口输出数据寄存器，低位有效    */
    vu32  BSRR;         /* 端口为设置/清除寄存器           */
    vu32  BRR;          /* 端口为清除寄存器                */
    vu32 LCKR;          /* 端口配置锁定寄存器              */
} GPIO_TypeDef;

/* 定义IO口地址      */
#define GPIOA               ((GPIO_TypeDef *) 0x40010800)
#define GPIOB               ((GPIO_TypeDef *) 0x40010C00)
#define GPIOC               ((GPIO_TypeDef *) 0x40011000)
#define GPIOD               ((GPIO_TypeDef *) 0x40011400)
#define GPIOE               ((GPIO_TypeDef *) 0x40011800)
#define GPIOF               ((GPIO_TypeDef *) 0x40011C00)
#define GPIOG               ((GPIO_TypeDef *) 0x40012000)

//! IO口位操作
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 


#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define GPIOF_BASE            (APB2PERIPH_BASE + 0x1C00)
#define GPIOG_BASE            (APB2PERIPH_BASE + 0x2000)
//! IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 
#define GPIOC_ODR_Addr    (GPIOC_BASE+12) //0x4001100C 
#define GPIOD_ODR_Addr    (GPIOD_BASE+12) //0x4001140C 
#define GPIOE_ODR_Addr    (GPIOE_BASE+12) //0x4001180C 
#define GPIOF_ODR_Addr    (GPIOF_BASE+12) //0x40011A0C    
#define GPIOG_ODR_Addr    (GPIOG_BASE+12) //0x40011E0C    

#define GPIOA_IDR_Addr    (GPIOA_BASE+8) //0x40010808 
#define GPIOB_IDR_Addr    (GPIOB_BASE+8) //0x40010C08 
#define GPIOC_IDR_Addr    (GPIOC_BASE+8) //0x40011008 
#define GPIOD_IDR_Addr    (GPIOD_BASE+8) //0x40011408 
#define GPIOE_IDR_Addr    (GPIOE_BASE+8) //0x40011808 
#define GPIOF_IDR_Addr    (GPIOF_BASE+8) //0x40011A08 
#define GPIOG_IDR_Addr    (GPIOG_BASE+8) //0x40011E08 
 
//! IO口操作,只对单一的IO口!
//! 确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PAin(n)    BIT_ADDR(GPIOA_IDR_Addr,n)  //输入 

#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 
#define PBin(n)    BIT_ADDR(GPIOB_IDR_Addr,n)  //输入 

#define PCout(n)   BIT_ADDR(GPIOC_ODR_Addr,n)  //输出 
#define PCin(n)    BIT_ADDR(GPIOC_IDR_Addr,n)  //输入 

#define PDout(n)   BIT_ADDR(GPIOD_ODR_Addr,n)  //输出 
#define PDin(n)    BIT_ADDR(GPIOD_IDR_Addr,n)  //输入 

#define PEout(n)   BIT_ADDR(GPIOE_ODR_Addr,n)  //输出 
#define PEin(n)    BIT_ADDR(GPIOE_IDR_Addr,n)  //输入

#define PFout(n)   BIT_ADDR(GPIOF_ODR_Addr,n)  //输出 
#define PFin(n)    BIT_ADDR(GPIOF_IDR_Addr,n)  //输入

#define PGout(n)   BIT_ADDR(GPIOG_ODR_Addr,n)  //输出 
#define PGin(n)    BIT_ADDR(GPIOG_IDR_Addr,n)  //输入


/** 
  * @brief External Interrupt/Event Controller
  */
typedef struct
{
    vu32 IMR;
    vu32 EMR;
    vu32 RTSR;
    vu32 FTSR;
    vu32 SWIER;
    vu32 PR;
} EXTI_TypeDef;

#define EXTI  ((EXTI_TypeDef *) 0X40010400)

/** 
  * @brief Alternate Function I/O
  */
typedef struct
{
    vu32 EVCR;
    vu32 MAPR;
    vu32 EXTICR[4];
    u32 RESERVED0;
    vu32 MAPR2; 
} AFIO_TypeDef;

#define AFIO ((AFIO_TypeDef *)0X40010000)

/** 
  * @brief Universal Synchronous Asynchronous Receiver Transmitter
  */
typedef struct
{
    vu16 SR;
    u16  RESERVED0;
    vu16 DR;
    u16  RESERVED1;
    vu16 BRR;
    u16  RESERVED2;
    vu16 CR1;
    u16  RESERVED3;
    vu16 CR2;
    u16  RESERVED4;
    vu16 CR3;
    u16  RESERVED5;
    vu16 GTPR;
    u16  RESERVED6;
} USART_TypeDef;

#define USART1  ((USART_TypeDef *)0X40013800)
#define USART2  ((USART_TypeDef *)0X40004400)
#define USART3  ((USART_TypeDef *)0X40004800)

/** 
  * @brief TIM
  */
typedef struct
{
  vu16 CR1;
  u16  RESERVED0;
  vu16 CR2;
  u16  RESERVED1;
  vu16 SMCR;
  u16  RESERVED2;
  vu16 DIER;
  u16  RESERVED3;
  vu16 SR;
  u16  RESERVED4;
  vu16 EGR;
  u16  RESERVED5;
  vu16 CCMR1;
  u16  RESERVED6;
  vu16 CCMR2;
  u16  RESERVED7;
  vu16 CCER;
  u16  RESERVED8;
  vu16 CNT;
  u16  RESERVED9;
  vu16 PSC;
  u16  RESERVED10;
  vu16 ARR;
  u16  RESERVED11;
  vu16 RCR;
  u16  RESERVED12;
  vu16 CCR1;
  u16  RESERVED13;
  vu16 CCR2;
  u16  RESERVED14;
  vu16 CCR3;
  u16  RESERVED15;
  vu16 CCR4;
  u16  RESERVED16;
  vu16 BDTR;
  u16  RESERVED17;
  vu16 DCR;
  u16  RESERVED18;
  vu16 DMAR;
  u16  RESERVED19;
} TIM_TypeDef;

#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00)

#define TIM1  ((TIM_TypeDef *) TIM1_BASE)
#define TIM2  ((TIM_TypeDef *)0X40000000)
#define TIM3  ((TIM_TypeDef *)0X40000400)
#define TIM4  ((TIM_TypeDef *)0X40000800)
#define TIM5  ((TIM_TypeDef *)0X40000C00)
#define TIM6  ((TIM_TypeDef *)0X40001000)
#define TIM7  ((TIM_TypeDef *)0X40001400)

/*------------------------ Analog to Digital Converter -----------------------*/
typedef struct
{
  vu32 SR;
  vu32 CR1;
  vu32 CR2;
  vu32 SMPR1;
  vu32 SMPR2;
  vu32 JOFR1;
  vu32 JOFR2;
  vu32 JOFR3;
  vu32 JOFR4;
  vu32 HTR;
  vu32 LTR;
  vu32 SQR1;
  vu32 SQR2;
  vu32 SQR3;
  vu32 JSQR;
  vu32 JDR1;
  vu32 JDR2;
  vu32 JDR3;
  vu32 JDR4;
  vu32 DR;
} ADC_TypeDef;


#define ADC1   ((ADC_TypeDef *)0x40012400)
#define ADC2   ((ADC_TypeDef *)0x40012800)


/** 
  * @brief Digital to Analog Converter
  */

typedef struct
{
  vu32 CR;
  vu32 SWTRIGR;
  vu32 DHR12R1;
  vu32 DHR12L1;
  vu32 DHR8R1;
  vu32 DHR12R2;
  vu32 DHR12L2;
  vu32 DHR8R2;
  vu32 DHR12RD;
  vu32 DHR12LD;
  vu32 DHR8RD;
  vu32 DOR1;
  vu32 DOR2;
} DAC_TypeDef;

#define DAC   ((DAC_TypeDef *)0x40007400)

/** 
  * @brief DMA Controller
  */
typedef struct
{
  vu32 CCR;
  vu32 CNDTR;
  vu32 CPAR;
  vu32 CMAR;
} DMA_Channel_TypeDef;


typedef struct
{
  vu32 ISR;
  vu32 IFCR;
} DMA_TypeDef ;

#define DMA1_BASE             (AHBPERIPH_BASE + 0x0000)
#define DMA2_BASE             (AHBPERIPH_BASE + 0x0400)
#define DMA1_Channel1_BASE    (AHBPERIPH_BASE + 0x0008)
#define DMA1_Channel2_BASE    (AHBPERIPH_BASE + 0x001C)
#define DMA1_Channel3_BASE    (AHBPERIPH_BASE + 0x0030)
#define DMA1_Channel4_BASE    (AHBPERIPH_BASE + 0x0044)
#define DMA1_Channel5_BASE    (AHBPERIPH_BASE + 0x0058)
#define DMA1_Channel6_BASE    (AHBPERIPH_BASE + 0x006C)
#define DMA1_Channel7_BASE    (AHBPERIPH_BASE + 0x0080)
#define DMA2_Channel1_BASE    (AHBPERIPH_BASE + 0x0408)
#define DMA2_Channel2_BASE    (AHBPERIPH_BASE + 0x041C)
#define DMA2_Channel3_BASE    (AHBPERIPH_BASE + 0x0430)
#define DMA2_Channel4_BASE    (AHBPERIPH_BASE + 0x0444)
#define DMA2_Channel5_BASE    (AHBPERIPH_BASE + 0x0458)

#define DMA1                ((DMA_TypeDef *) DMA1_BASE)
#define DMA2                ((DMA_TypeDef *) DMA2_BASE)
#define DMA1_Channel1       ((DMA_Channel_TypeDef *) DMA1_Channel1_BASE)
#define DMA1_Channel2       ((DMA_Channel_TypeDef *) DMA1_Channel2_BASE)
#define DMA1_Channel3       ((DMA_Channel_TypeDef *) DMA1_Channel3_BASE)
#define DMA1_Channel4       ((DMA_Channel_TypeDef *) DMA1_Channel4_BASE)
#define DMA1_Channel5       ((DMA_Channel_TypeDef *) DMA1_Channel5_BASE)
#define DMA1_Channel6       ((DMA_Channel_TypeDef *) DMA1_Channel6_BASE)
#define DMA1_Channel7       ((DMA_Channel_TypeDef *) DMA1_Channel7_BASE)
#define DMA2_Channel1       ((DMA_Channel_TypeDef *) DMA2_Channel1_BASE)
#define DMA2_Channel2       ((DMA_Channel_TypeDef *) DMA2_Channel2_BASE)
#define DMA2_Channel3       ((DMA_Channel_TypeDef *) DMA2_Channel3_BASE)
#define DMA2_Channel4       ((DMA_Channel_TypeDef *) DMA2_Channel4_BASE)
#define DMA2_Channel5       ((DMA_Channel_TypeDef *) DMA2_Channel5_BASE)


typedef struct
{
  vu32 ACR;
  vu32 KEYR;
  vu32 OPTKEYR;
  vu32 SR;
  vu32 CR;
  vu32 AR;
  vu32 RESERVED;
  vu32 OBR;
  vu32 WRPR;
} FLASH_TypeDef;

#define FLASH_R_BASE        (AHBPERIPH_BASE + 0x2000) /*!< Flash registers base address */
#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)


typedef struct
{
  vu32 KR;
  vu32 PR;
  vu32 RLR;
  vu32 SR;
} IWDG_TypeDef;

#define IWDG_BASE           (APB1PERIPH_BASE + 0x3000)
#define IWDG                ((IWDG_TypeDef *) IWDG_BASE)


/** 
  * @brief Controller Area Network TxMailBox 
***/
typedef struct
{
  vu32 TIR;
  vu32 TDTR;
  vu32 TDLR;
  vu32 TDHR;
} CAN_TxMailBox_TypeDef ;

/** 
  * @brief Controller Area Network FIFOMailBox 
***/
typedef struct
{
  vu32 RIR;
  vu32 RDTR;
  vu32 RDLR;
  vu32 RDHR;
} CAN_FIFOMailBox_TypeDef;

/** 
  * @brief Controller Area Network FilterRegister 
  */
  
typedef struct
{
  vu32 FR1;
  vu32 FR2;
} CAN_FilterRegister_TypeDef;
/** 
  * @brief Controller Area Network 
***/
typedef struct
{
  vu32 MCR;
  vu32 MSR;
  vu32 TSR;
  vu32 RF0R;
  vu32 RF1R;
  vu32 IER;
  vu32 ESR;
  vu32 BTR;
  u32  RESERVED0[88];
  CAN_TxMailBox_TypeDef sTxMailBox[3];
  CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
  u32  RESERVED1[12];
  vu32 FMR;
  vu32 FM1R;
  u32  RESERVED2;
  vu32 FS1R;
  u32  RESERVED3;
  vu32 FFA1R;
  u32  RESERVED4;
  vu32 FA1R;
  u32  RESERVED5[8];
#ifndef STM32F10X_CL
  CAN_FilterRegister_TypeDef sFilterRegister[14];
#else
  CAN_FilterRegister_TypeDef sFilterRegister[28];
#endif /* STM32F10X_CL */  
} CAN_TypeDef ;

#define CAN1_BASE           (APB1PERIPH_BASE + 0x6400)
#define CAN2_BASE           (APB1PERIPH_BASE + 0x6800)

#define CAN1                ((CAN_TypeDef *) CAN1_BASE)
#define CAN2                ((CAN_TypeDef *) CAN2_BASE)

/** 
  * @brief SD host Interface
  */

typedef struct
{
  vu32 POWER;
  vu32 CLKCR;
  vu32 ARG;
  vu32 CMD;
  vuc32 RESPCMD;
  vuc32 RESP1;
  vuc32 RESP2;
  vuc32 RESP3;
  vuc32 RESP4;
  vu32 DTIMER;
  vu32 DLEN;
  vu32 DCTRL;
  vuc32 DCOUNT;
  vuc32 STA;
  vu32 ICR;
  vu32 MASK;
  u32  RESERVED0[2];
  vuc32 FIFOCNT;
  u32  RESERVED1[13];
  vu32 FIFO;
} SDIO_TypeDef;

#define SDIO_BASE           (PERIPH_BASE + 0x18000)

#define SDIO                ((SDIO_TypeDef *) SDIO_BASE)

/** 
  * @brief Serial Peripheral Interface
  */

typedef struct
{
  vu16 CR1;
  u16  RESERVED0;
  vu16 CR2;
  u16  RESERVED1;
  vu16 SR;
  u16  RESERVED2;
  vu16 DR;
  u16  RESERVED3;
  vu16 CRCPR;
  u16  RESERVED4;
  vu16 RXCRCR;
  u16  RESERVED5;
  vu16 TXCRCR;
  u16  RESERVED6;
  vu16 I2SCFGR;
  u16  RESERVED7;
  vu16 I2SPR;
  u16  RESERVED8;  
} SPI_TypeDef;

#define SPI2_BASE             (APB1PERIPH_BASE + 0x3800)
#define SPI3_BASE             (APB1PERIPH_BASE + 0x3C00)

#define SPI2                ((SPI_TypeDef *) SPI2_BASE)
#define SPI3                ((SPI_TypeDef *) SPI3_BASE)

#ifdef __cplusplus
}
#endif

#endif /*  __STM32F103_H__  */


