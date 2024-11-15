#ifndef __CORTEX_M3_H__
#define __CORTEX_M3_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"

typedef struct
{
    vu32 ISER[8];                      /*!< Offset: 0x000  Interrupt Set Enable Register           */
    u32 RESERVED0[24];                                   
    vu32 ICER[8];                      /*!< Offset: 0x080  Interrupt Clear Enable Register         */
    u32 RSERVED1[24];                                    
    vu32 ISPR[8];                      /*!< Offset: 0x100  Interrupt Set Pending Register          */
    u32 RESERVED2[24];                                   
    vu32 ICPR[8];                      /*!< Offset: 0x180  Interrupt Clear Pending Register        */
    u32 RESERVED3[24];                                   
    vu32 IABR[8];                      /*!< Offset: 0x200  Interrupt Active bit Register           */
    u32 RESERVED4[56];                                   
    vu8  IP[240];                      /*!< Offset: 0x300  Interrupt Priority Register (8Bit wide) */
    u32 RESERVED5[644];                                  
    vu32 STIR;                         /*!< Offset: 0xE00  Software Trigger Interrupt Register     */
}  NVIC_Type;          

#define NVIC   ((NVIC_Type *) 0XE000E100)        /*!< NVIC configuration struct                    */

typedef struct
{
    vuc32 CPUID;                        /*!< Offset: 0x00  CPU ID Base Register                                  */
    vu32 ICSR;                          /*!< Offset: 0x04  Interrupt Control State Register                      */
    vu32 VTOR;                          /*!< Offset: 0x08  Vector Table Offset Register                          */
    vu32 AIRCR;                         /*!< Offset: 0x0C  Application Interrupt / Reset Control Register        */
    vu32 SCR;                           /*!< Offset: 0x10  System Control Register                               */
    vu32 CCR;                           /*!< Offset: 0x14  Configuration Control Register                        */
    vu32  SHP[12];                      /*!< Offset: 0x18  System Handlers Priority Registers (4-7, 8-11, 12-15) */
    vu32 SHCSR;                         /*!< Offset: 0x24  System Handler Control and State Register             */
    vu32 CFSR;                          /*!< Offset: 0x28  Configurable Fault Status Register                    */
    vu32 HFSR;                          /*!< Offset: 0x2C  Hard Fault Status Register                            */
    vu32 DFSR;                          /*!< Offset: 0x30  Debug Fault Status Register                           */
    vu32 MMFAR;                         /*!< Offset: 0x34  Mem Manage Address Register                           */
    vu32 BFAR;                          /*!< Offset: 0x38  Bus Fault Address Register                            */
    vu32 AFSR;                          /*!< Offset: 0x3C  Auxiliary Fault Status Register                       */
    vuc32 PFR[2];                       /*!< Offset: 0x40  Processor Feature Register                            */
    vuc32 DFR;                          /*!< Offset: 0x48  Debug Feature Register                                */
    vuc32 ADR;                          /*!< Offset: 0x4C  Auxiliary Feature Register                            */
    vuc32 MMFR[4];                      /*!< Offset: 0x50  Memory Model Feature Register                         */
    vuc32 ISAR[5];                      /*!< Offset: 0x60  ISA Feature Register                                  */
} SCB_Type;                 

#define SCB  ((SCB_Type *)0XE000ED00)   /*!< SCB configuration struct                         */

typedef struct
{
    vu32 CTRL;                         /*!< Offset: 0x00  SysTick Control and Status Register */
    vu32 LOAD;                         /*!< Offset: 0x04  SysTick Reload Value Register       */
    vu32 VAL;                          /*!< Offset: 0x08  SysTick Current Value Register      */
    vuc32 CALIB;                       /*!< Offset: 0x0C  SysTick Calibration Register        */
} SysTick_Type;

#define SysTick   ((SysTick_Type *)0XE000E010) /*!< SysTick configuration struct              */

typedef struct
{
    volatile  union  
    {
        vu8    uint8;                  /*!< Offset:       ITM Stimulus Port 8-bit                   */
        vu16   uint16;                 /*!< Offset:       ITM Stimulus Port 16-bit                  */
        vu32   uint32;                 /*!< Offset:       ITM Stimulus Port 32-bit                  */
    }  PORT [32];                      /*!< Offset: 0x00  ITM Stimulus Port Registers               */
    u32 RESERVED0[864];                                 
    vu32 TER;                          /*!< Offset:       ITM Trace Enable Register                 */
    u32 RESERVED1[15];                                  
    vu32 TPR;                          /*!< Offset:       ITM Trace Privilege Register              */
    u32 RESERVED2[15];                                  
    vu32 TCR;                          /*!< Offset:       ITM Trace Control Register                */
    u32 RESERVED3[29];                                  
    vu32 IWR;                          /*!< Offset:       ITM Integration Write Register            */
    vu32 IRR;                          /*!< Offset:       ITM Integration Read Register             */
    vu32 IMCR;                         /*!< Offset:       ITM Integration Mode Control Register     */
    u32 RESERVED4[43];                                  
    vu32 LAR;                          /*!< Offset:       ITM Lock Access Register                  */
    vu32 LSR;                          /*!< Offset:       ITM Lock Status Register                  */
    u32 RESERVED5[6];                                   
    vuc32 PID4;                        /*!< Offset:       ITM Peripheral Identification Register #4 */
    vuc32 PID5;                        /*!< Offset:       ITM Peripheral Identification Register #5 */
    vuc32 PID6;                        /*!< Offset:       ITM Peripheral Identification Register #6 */
    vuc32 PID7;                        /*!< Offset:       ITM Peripheral Identification Register #7 */
    vuc32 PID0;                        /*!< Offset:       ITM Peripheral Identification Register #0 */
    vuc32 PID1;                        /*!< Offset:       ITM Peripheral Identification Register #1 */
    vuc32 PID2;                        /*!< Offset:       ITM Peripheral Identification Register #2 */
    vuc32 PID3;                        /*!< Offset:       ITM Peripheral Identification Register #3 */
    vuc32 CID0;                        /*!< Offset:       ITM Component  Identification Register #0 */
    vuc32 CID1;                        /*!< Offset:       ITM Component  Identification Register #1 */
    vuc32 CID2;                        /*!< Offset:       ITM Component  Identification Register #2 */
    vuc32 CID3;                        /*!< Offset:       ITM Component  Identification Register #3 */
} ITM_Type;                                                

#define ITM  ((ITM_Type *)0xE0000000)  /*!< ITM configuration struct                                */

typedef struct
{
    u32 RESERVED0;
    vu32 ICTR;                         /*!< Offset: 0x04  Interrupt Control Type Register */
    vu32 ACTLR;                        /*!< Offset: 0x08  Auxiliary Control Register      */
} InterruptType_Type;

#define InterruptType ((InterruptType_Type *)0xE000E000)/*!< Interrupt Type Register      */

typedef struct
{
    vuc32 TYPE;                         /*!< Offset: 0x00  MPU Type Register                              */
    vu32  CTRL;                         /*!< Offset: 0x04  MPU Control Register                           */
    vu32  RNR;                          /*!< Offset: 0x08  MPU Region RNRber Register                     */
    vu32  RBAR;                         /*!< Offset: 0x0C  MPU Region Base Address Register               */
    vu32  RASR;                         /*!< Offset: 0x10  MPU Region Attribute and Size Register         */
    vu32  RBAR_A1;                      /*!< Offset: 0x14  MPU Alias 1 Region Base Address Register       */
    vu32  RASR_A1;                      /*!< Offset: 0x18  MPU Alias 1 Region Attribute and Size Register */
    vu32  RBAR_A2;                      /*!< Offset: 0x1C  MPU Alias 2 Region Base Address Register       */
    vu32  RASR_A2;                      /*!< Offset: 0x20  MPU Alias 2 Region Attribute and Size Register */
    vu32  RBAR_A3;                      /*!< Offset: 0x24  MPU Alias 3 Region Base Address Register       */
    vu32  RASR_A3;                      /*!< Offset: 0x28  MPU Alias 3 Region Attribute and Size Register */
} MPU_Type;     

#define MPU   ((MPU_Type*)0xE000ED90)   /*!< Memory Protection Unit                                       */

typedef struct
{
    vu32  DHCSR;                        /*!< Offset: 0x00  Debug Halting Control and Status Register    */
    vuc32 DCRSR;                        /*!< Offset: 0x04  Debug Core Register Selector Register        */
    vu32  DCRDR;                        /*!< Offset: 0x08  Debug Core Register Data Register            */
    vu32  DEMCR;                        /*!< Offset: 0x0C  Debug Exception and Monitor Control Register */
} CoreDebug_Type;

#define CoreDebug  ((CoreDebug_Type *)0XE000EDF0)   /*!< Core Debug configuration struct                */

/* IRQ Channels ----------------------------------------------------------------------------------------*/
#define WWDG_IRQChannel              ((u8)0x00)  /* Window WatchDog Interrupt                           */
#define PVD_IRQChannel               ((u8)0x01)  /* PVD through EXTI Line detection Interrupt           */
#define TAMPER_IRQChannel            ((u8)0x02)  /* Tamper Interrupt                                    */
#define RTC_IRQChannel               ((u8)0x03)  /* RTC global Interrupt                                */
#define FLASH_IRQChannel             ((u8)0x04)  /* FLASH global Interrupt                              */
#define RCC_IRQChannel               ((u8)0x05)  /* RCC global Interrupt                                */
#define EXTI0_IRQChannel             ((u8)0x06)  /* EXTI Line0 Interrupt                                */
#define EXTI1_IRQChannel             ((u8)0x07)  /* EXTI Line1 Interrupt                                */
#define EXTI2_IRQChannel             ((u8)0x08)  /* EXTI Line2 Interrupt                                */
#define EXTI3_IRQChannel             ((u8)0x09)  /* EXTI Line3 Interrupt                                */
#define EXTI4_IRQChannel             ((u8)0x0A)  /* EXTI Line4 Interrupt                                */
#define DMA1_Channel1_IRQChannel     ((u8)0x0B)  /* DMA1 Channel 1 global Interrupt                     */
#define DMA1_Channel2_IRQChannel     ((u8)0x0C)  /* DMA1 Channel 2 global Interrupt                     */
#define DMA1_Channel3_IRQChannel     ((u8)0x0D)  /* DMA1 Channel 3 global Interrupt                     */
#define DMA1_Channel4_IRQChannel     ((u8)0x0E)  /* DMA1 Channel 4 global Interrupt                     */
#define DMA1_Channel5_IRQChannel     ((u8)0x0F)  /* DMA1 Channel 5 global Interrupt                     */
#define DMA1_Channel6_IRQChannel     ((u8)0x10)  /* DMA1 Channel 6 global Interrupt                     */
#define DMA1_Channel7_IRQChannel     ((u8)0x11)  /* DMA1 Channel 7 global Interrupt                     */
#define ADC1_2_IRQChannel            ((u8)0x12)  /* ADC1 et ADC2 global Interrupt                       */
#define USB_HP_CAN_TX_IRQChannel     ((u8)0x13)  /* USB High Priority or CAN TX Interrupts              */
#define USB_LP_CAN_RX0_IRQChannel    ((u8)0x14)  /* USB Low Priority or CAN RX0 Interrupts              */
#define CAN_RX1_IRQChannel           ((u8)0x15)  /* CAN RX1 Interrupt                                   */
#define CAN_SCE_IRQChannel           ((u8)0x16)  /* CAN SCE Interrupt                                   */
#define EXTI9_5_IRQChannel           ((u8)0x17)  /* External Line[9:5] Interrupts                       */
#define TIM1_BRK_IRQChannel          ((u8)0x18)  /* TIM1 Break Interrupt                                */
#define TIM1_UP_IRQChannel           ((u8)0x19)  /* TIM1 Update Interrupt                               */
#define TIM1_TRG_COM_IRQChannel      ((u8)0x1A)  /* TIM1 Trigger and Commutation Interrupt              */
#define TIM1_CC_IRQChannel           ((u8)0x1B)  /* TIM1 Capture Compare Interrupt                      */
#define TIM2_IRQChannel              ((u8)0x1C)  /* TIM2 global Interrupt                               */
#define TIM3_IRQChannel              ((u8)0x1D)  /* TIM3 global Interrupt                               */
#define TIM4_IRQChannel              ((u8)0x1E)  /* TIM4 global Interrupt                               */
#define I2C1_EV_IRQChannel           ((u8)0x1F)  /* I2C1 Event Interrupt                                */
#define I2C1_ER_IRQChannel           ((u8)0x20)  /* I2C1 Error Interrupt                                */
#define I2C2_EV_IRQChannel           ((u8)0x21)  /* I2C2 Event Interrupt                                */
#define I2C2_ER_IRQChannel           ((u8)0x22)  /* I2C2 Error Interrupt                                */
#define SPI1_IRQChannel              ((u8)0x23)  /* SPI1 global Interrupt                               */
#define SPI2_IRQChannel              ((u8)0x24)  /* SPI2 global Interrupt                               */
#define USART1_IRQChannel            ((u8)0x25)  /* USART1 global Interrupt                             */
#define USART2_IRQChannel            ((u8)0x26)  /* USART2 global Interrupt                             */
#define USART3_IRQChannel            ((u8)0x27)  /* USART3 global Interrupt                             */
#define EXTI15_10_IRQChannel         ((u8)0x28)  /* External Line[15:10] Interrupts                     */
#define RTCAlarm_IRQChannel          ((u8)0x29)  /* RTC Alarm through EXTI Line Interrupt               */
#define USBWakeUp_IRQChannel         ((u8)0x2A)  /* USB WakeUp from suspend through EXTI Line Interrupt */
#define TIM8_BRK_IRQChannel          ((u8)0x2B)  /* TIM8 Break Interrupt                                */
#define TIM8_UP_IRQChannel           ((u8)0x2C)  /* TIM8 Update Interrupt                               */
#define TIM8_TRG_COM_IRQChannel      ((u8)0x2D)  /* TIM8 Trigger and Commutation Interrupt              */
#define TIM8_CC_IRQChannel           ((u8)0x2E)  /* TIM8 Capture Compare Interrupt                      */
#define ADC3_IRQChannel              ((u8)0x2F)  /* ADC3 global Interrupt                               */
#define FSMC_IRQChannel              ((u8)0x30)  /* FSMC global Interrupt                               */
#define SDIO_IRQChannel              ((u8)0x31)  /* SDIO global Interrupt                               */
#define TIM5_IRQChannel              ((u8)0x32)  /* TIM5 global Interrupt                               */
#define SPI3_IRQChannel              ((u8)0x33)  /* SPI3 global Interrupt                               */
#define UART4_IRQChannel             ((u8)0x34)  /* UART4 global Interrupt                              */
#define UART5_IRQChannel             ((u8)0x35)  /* UART5 global Interrupt                              */
#define TIM6_IRQChannel              ((u8)0x36)  /* TIM6 global Interrupt                               */
#define TIM7_IRQChannel              ((u8)0x37)  /* TIM7 global Interrupt                               */
#define DMA2_Channel1_IRQChannel     ((u8)0x38)  /* DMA2 Channel 1 global Interrupt                     */
#define DMA2_Channel2_IRQChannel     ((u8)0x39)  /* DMA2 Channel 2 global Interrupt                     */
#define DMA2_Channel3_IRQChannel     ((u8)0x3A)  /* DMA2 Channel 3 global Interrupt                     */
#define DMA2_Channel4_5_IRQChannel   ((u8)0x3B)  /* DMA2 Channel 4 and DMA2 Channel 5 global Interrupt  */

#ifdef __cplusplus
}
#endif

#endif /*  __CORTEX_M3_H__  */


