/****************************************************************************************
* 文件名称: timer.c
* 
* 创建时间：2019/11/28
*
* 修改时间：2019/11/28
*
* 作    者：何鑫成
*
* 版    本：V1.0
*
* 文摘描述：定时器函数
*
* 说    明：
****************************************************************************************/ 
#include "timer.h"

/**
 * @brief  定时器2初始化
 **/
void TIM2_Init(u16 arr , u16 psc)
{
    RCC -> APB1ENR |= 1 << 0 ;      //! TIM2时钟使能    
  
    TIM2 -> PSC = psc ;             //! 设置预分频的值  
    TIM2 -> ARR = arr ;             //! 设置重装载的值 
  
    TIM2 -> DIER |= 1 << 0 ;        //! 允许更新中断    
    TIM2 -> CR1 |= 1 << 0 ;         //! 使能计数器      
  
    NVIC_Set_IRQn(TIM2_IRQn,0x1F) ; //! 设置中断优先级
}

/**
 * @brief  定时器1 CH1 PWM 初始化
 **/
void PWM_TIM1_CH1_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1时钟使能
      
    GPIO_Init(GPIOB , 15 , GPIO_Mode_AF_OD) ;  //! PB15 推挽复用输出

    TIM1->ARR = arr ;                //! 设定计数器自动重装值 
    TIM1->PSC = psc ;                //! 预分频器
  
    TIM1->CCMR1 |= 6<<4 ;            //! CH1 PWM2模式  
    TIM1->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     
    TIM1->CCER |= 1<<0 ;             //! OC1 输出使能      
  
    TIM1->CR1 = 0x80 ;               //! ARPE使能 
    TIM1->CR1 |= 0x01 ;              //! 使能定时器1      
    
    TIM1->BDTR |= 1 << 15 ;          //! MOE主输出使能，这是与普通定时器不同的地方
}

/**
 * @brief  定时器1 CH1N PWM 初始化
 **/
void PWM_TIM1_CH1N_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1时钟使能
    
    RCC -> APB2ENR |= 1 << 3 ;       //! 使能GPIOB时钟 
  
    GPIO_Init(GPIOB , 13 , GPIO_Mode_AF_OD) ;  //! PB13   复用推挽输出

    TIM1->ARR = arr ;                //! 设定计数器自动重装值 
    TIM1->PSC = psc ;                //! 预分频器
  
    TIM1->CCMR1 |= 6<<4 ;            //! CH1 PWM2模式  
    TIM1->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     
    TIM1->CCER |= 1<<2 ;             //! OC1 输出使能      

    TIM1->CR1 = 0x80 ;               //! ARPE使能 
    TIM1->CR1 |= 0x01 ;              //! 使能定时器3         
    
    TIM1->BDTR |= 1 << 15 ;          //! MOE主输出使能，这是与普通定时器不同的地方
}

/**
 * @brief  定时器1 CH1N PWM 初始化
 **/
void PWM_TIM1_CH2N_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1时钟使能
    
    RCC -> APB2ENR |= 1 << 3 ;       //! 使能GPIOB时钟 
  
    GPIO_Init(GPIOB , 14 , GPIO_Mode_AF_OD) ;  //! PB14   复用推挽输出

    TIM1->ARR = arr ;                //! 设定计数器自动重装值 
    TIM1->PSC = psc ;                //! 预分频器
  
    TIM1->CCMR1 |= 6<<12 ;           //! CH2 PWM2模式  
    TIM1->CCMR1 |= 1<<11 ;           //! CH2 预装载使能     
    TIM1->CCER |= 1<<6 ;             //! OC2 输出使能      

    TIM1->CR1 = 0x80 ;               //! ARPE使能 
    TIM1->CR1 |= 0x01 ;              //! 使能定时器3         
    
    TIM1->BDTR |= 1 << 15 ;          //! MOE主输出使能，这是与普通定时器不同的地方
}

/**
 * @brief  定时器1 CH3N PWM 初始化
 **/
void PWM_TIM1_CH3N_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1时钟使能
      
    GPIO_Init(GPIOA , 8 , GPIO_Mode_AF_OD) ;   //! PA8  推挽复用输出

    TIM1->ARR = arr ;                //! 设定计数器自动重装值 
    TIM1->PSC = psc ;                //! 预分频器
  
    TIM1->CCMR2 |= 6<<4 ;            //! CH3 PWM2模式  
    TIM1->CCMR2 |= 1<<3 ;            //! CH3 预装载使能     
    TIM1->CCER |= 1<<10 ;            //! OC3 输出使能   
  
    TIM1->CR1 = 0x80 ;               //! ARPE使能 
    TIM1->CR1 |= 0x01 ;              //! 使能定时器1      
    
    TIM1->BDTR |= 1 << 15 ;          //! MOE主输出使能，这是与普通定时器不同的地方
}

/**
 * @brief  定时器1 CH4 PWM 初始化
 **/
void PWM_TIM1_CH4_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1时钟使能
      
    GPIO_Init(GPIOA , 11 , GPIO_Mode_AF_OD) ;  //! PA11   推挽输出

    TIM1->ARR = arr ;                //! 设定计数器自动重装值 
    TIM1->PSC = psc ;                //! 预分频器
  
    TIM1->CCMR2 |= 6 << 12 ;         //! CH4 PWM2模式  
    TIM1->CCMR2 |= 1 << 11 ;         //! CH4 预装载使能     
    TIM1->CCER |= 1 << 12 ;          //! OC4 输出使能      
  
    TIM1->CR1 = 0x80 ;               //! ARPE使能 
    TIM1->CR1 |= 0x01 ;              //! 使能定时器1      
    
    TIM1->BDTR |= 1 << 15 ;          //! MOE主输出使能，这是与普通定时器不同的地方
}

/**
 * @brief  定时器1 CH1 CH3N CH4 PWM 初始化
 **/
void PWM_TIM1_CH1_CH3_CH4_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1时钟使能
      
    GPIO_Init(GPIOB , 15 , GPIO_Mode_AF_OD) ;  //! PB15 推挽复用输出
    GPIO_Init(GPIOA , 8 , GPIO_Mode_AF_OD) ;   //! PA8  推挽复用输出
    GPIO_Init(GPIOA , 11 , GPIO_Mode_AF_OD) ;  //! PA11   推挽输出

    TIM1->ARR = arr ;                //! 设定计数器自动重装值 
    TIM1->PSC = psc ;                //! 预分频器
  
    TIM1->CCMR1 |= 6<<4 ;            //! CH1 PWM2模式  
    TIM1->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     
    TIM1->CCER |= 1<<0 ;             //! OC1 输出使能      
  
    TIM1->CCMR2 |= 6<<4 ;            //! CH3 PWM2模式  
    TIM1->CCMR2 |= 1<<3 ;            //! CH3 预装载使能     
    TIM1->CCER |= 1<<10 ;            //! OC3 输出使能   

    TIM1->CCMR2 |= 6 << 12 ;         //! CH4 PWM2模式  
    TIM1->CCMR2 |= 1 << 11 ;         //! CH4 预装载使能     
    TIM1->CCER |= 1 << 12 ;          //! OC4 输出使能      
  
    TIM1->CR1 = 0x80 ;               //! ARPE使能 
    TIM1->CR1 |= 0x01 ;              //! 使能定时器1      
    
    TIM1->BDTR |= 1 << 15 ;          //! MOE主输出使能，这是与普通定时器不同的地方
}

/**
 * @brief  定时器3 All CH PWM 初始化
 **/
void PWM_TIM1_All_CH_Init(u16 arr , u16 psc)
{
    RCC->APB2ENR |= 1 << 11 ;        //! TIM1时钟使能
    
    RCC -> APB2ENR |= 1 << 2 ;       //! 使能GPIOA时钟 
    RCC -> APB2ENR |= 1 << 3 ;       //! 使能GPIOB时钟 
  
    GPIO_Init(GPIOA , 11 , GPIO_Mode_AF_OD) ;  //! PA11   复用推挽输出
    GPIO_Init(GPIOB , 13 , GPIO_Mode_AF_OD) ;  //! PB13   复用推挽输出
    GPIO_Init(GPIOB , 14 , GPIO_Mode_AF_OD) ;  //! PB14   复用推挽输出
    GPIO_Init(GPIOB , 15 , GPIO_Mode_AF_OD) ;  //! PB15   复用推挽输出

    TIM1->ARR = arr ;                //! 设定计数器自动重装值 
    TIM1->PSC = psc ;                //! 预分频器
  
    TIM1->CCMR1 |= 6<<4 ;            //! CH1 PWM2模式  
    TIM1->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     
    TIM1->CCER |= 1<<2 ;             //! OC1 输出使能      
  
    TIM1->CCMR1 |= 6<<12 ;           //! CH2 PWM2模式  
    TIM1->CCMR1 |= 1<<11 ;           //! CH2 预装载使能     
    TIM1->CCER |= 1<<6 ;             //! OC2 输出使能      
  
    TIM1->CCMR2 |= 6<<4 ;            //! CH3 PWM2模式  
    TIM1->CCMR2 |= 1<<3 ;            //! CH3 预装载使能     
    TIM1->CCER |= 1<<10 ;             //! OC3 输出使能      
  
    TIM1->CCMR2 |= 6<<12 ;           //! CH4 PWM2模式  
    TIM1->CCMR2 |= 1<<11 ;           //! CH4 预装载使能     
    TIM1->CCER |= 1<<12 ;            //! OC4 输出使能      

    TIM1->CR1 = 0x80 ;               //! ARPE使能 
    TIM1->CR1 |= 0x01 ;              //! 使能定时器3         
    
    TIM1->BDTR |= 1 << 15 ;          //! MOE主输出使能，这是与普通定时器不同的地方
}

/**
 * @brief  定时器2 CH1 PWM 初始化
 * @note   PA15 做为普通IO口时，需要设置特殊引脚配置AFIO寄存器，另外要打开AFIO时钟
 **/
void PWM_TIM2_CH1_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 0 ;         //! TIM2时钟使能
    RCC->APB2ENR |= 1 << 0 ;         //! AFIO时钟使能
    RCC->APB2ENR |= 1 << 2 ;         //! 使能GPIOA时钟 
    
    AFIO -> MAPR |= (2 << 24) ;      //! PA15 关闭JTAG仿真功能
    AFIO -> MAPR |= (1 << 8) ;       //! TIM2 CH1 选择PA15
    
    GPIO_Init(GPIOA , 15 , GPIO_Mode_AF_OD) ;  //! PA15 推挽复用输出

    TIM2->ARR = arr ;                //! 设定计数器自动重装值  
    TIM2->PSC = psc ;                //! 预分频器
  
    TIM2->CCMR1 |= 7<<4 ;            //! CH1 PWM2模式  
    TIM2->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     

    TIM2->CCER |= 1<<0 ;             //! OC1 输出使能      

    TIM2->CR1 = 0x80 ;               //! ARPE使能 
    TIM2->CR1 |= 0x01 ;              //! 使能定时器3          
}

/**
 * @brief  定时器2 CH2 PWM 初始化
 **/
void PWM_TIM2_CH2_Init(u16 arr , u16 psc)
{
    RCC -> APB1ENR |= 1 << 0 ;       //! TIM2时钟使能
    RCC -> APB2ENR |= 1 << 3 ;       //! 使能GPIOB时钟 
  
    RCC -> APB2ENR |= 1 << 0 ;       //! AFIO时钟使能
  
    AFIO -> MAPR &= ~(3 << 24) ;     //! 关闭JTAG-DP，启用SW-DP；
    AFIO -> MAPR |= (2 << 24) ;
  
    AFIO -> MAPR &= ~(3 << 8) ;      //! PB3作为TIM2_CH2通道
    AFIO -> MAPR |= (1 << 8) ;
    
    GPIO_Init(GPIOB , 3 , GPIO_Mode_AF_OD) ;  //! PB3   推挽输出

    TIM2->ARR = arr ;                //! 设定计数器自动重装值 
    TIM2->PSC = psc ;                //! 预分频器
  
    TIM2->CCMR1 |= 7<<12 ;           //! CH2 PWM2模式  
    TIM2->CCMR1 |= 1<<11 ;           //! CH2 预装载使能     
    TIM2->CCER |= 1<<4 ;             //! OC2 输出使能      

    TIM2->CR1 = 0x80 ;               //! ARPE使能 
    TIM2->CR1 |= 0x01 ;              //! 使能定时器2    
}

/**
 * @brief  定时器3 CH1 PWM 初始化
 **/
void PWM_TIM3_CH1_Init(u16 arr , u16 psc)
{
    RCC -> APB1ENR |= 1 << 1 ;       //! TIM3时钟使能
    RCC -> APB2ENR |= 1 << 3 ;       //! 使能GPIOB时钟 
  
    RCC -> APB2ENR |= 1 << 0 ;       //! AFIO时钟使能
  
    AFIO -> MAPR &= ~(3 << 24) ;     //! 关闭JTAG-DP，启用SW-DP；
    AFIO -> MAPR |= (2 << 24) ;
  
    AFIO -> MAPR &= ~(3 << 10) ;     //! PB4作为TIM3_CH1通道
    AFIO -> MAPR |= (2 << 10) ;
    
    GPIO_Init(GPIOB , 4 , GPIO_Mode_AF_OD) ;  //! PB4   推挽输出
   
    TIM3->ARR = arr ;                //! 设定计数器自动重装值 
    TIM3->PSC = psc ;                //! 预分频器
  
    TIM3->CCMR1 |= 6<<4 ;            //! CH1 PWM2模式  
    TIM3->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     
    TIM3->CCER |= 1<<0 ;             //! OC1 输出使能      

    TIM3->CR1 = 0x80 ;               //! ARPE使能 
    TIM3->CR1 |= 0x01 ;              //! 使能定时器3         
}

/**
 * @brief  定时器3 CH2 PWM 初始化
 **/
void PWM_TIM3_CH2_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 1 ;         //! TIM3时钟使能
    
    GPIO_Init(GPIOA , 7 , GPIO_Mode_AF_OD) ;  //! PA7   推挽输出

    TIM3->ARR = arr ;                //! 设定计数器自动重装值 
    TIM3->PSC = psc ;                //! 预分频器
  
    TIM3->CCMR1 |= 6<<12 ;           //! CH2 PWM2模式  
    TIM3->CCMR1 |= 1<<11 ;           //! CH2 预装载使能     
    TIM3->CCER |= 1<<4 ;             //! OC2 输出使能      

    TIM3->CR1 = 0x80 ;               //! ARPE使能 
    TIM3->CR1 |= 0x01 ;              //! 使能定时器3         
}

/**
 * @brief  定时器3 CH3 PWM 初始化
 **/
void PWM_TIM3_CH3_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 1 ;         //! TIM3时钟使能
    
    GPIO_Init(GPIOB , 0 , GPIO_Mode_AF_OD) ;  //! PB0   推挽输出
    
    TIM3->ARR = arr ;                //! 设定计数器自动重装值 
    TIM3->PSC = psc ;                //! 预分频器
  
    TIM3->CCMR2 |= 6<<4 ;            //! CH3 PWM2模式  
    TIM3->CCMR2 |= 1<<3 ;            //! CH3 预装载使能     
    TIM3->CCER |= 1<<8 ;             //! OC3 输出使能      

    TIM3->CR1 = 0x80 ;               //! ARPE使能 
    TIM3->CR1 |= 0x01 ;              //! 使能定时器3         
}

/**
 * @brief  定时器3 CH4 PWM 初始化
 **/
void PWM_TIM3_CH4_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 1 ;         //! TIM3时钟使能
    
    GPIO_Init(GPIOB , 1 , GPIO_Mode_AF_OD) ;  //! PB1   推挽输出
    
    TIM3->ARR = arr ;                //! 设定计数器自动重装值 
    TIM3->PSC = psc ;                //! 预分频器
  
    TIM3->CCMR2 |= 6 << 12 ;         //! CH4 PWM2模式  
    TIM3->CCMR2 |= 1 << 11 ;         //! CH4 预装载使能     
    TIM3->CCER |= 1 << 12 ;          //! OC4 输出使能      

    TIM3->CR1 = 0x80 ;               //! ARPE使能 
    TIM3->CR1 |= 0x01 ;              //! 使能定时器3         
}

/**
 * @brief  定时器3 All CH PWM 初始化
 **/
void PWM_TIM3_All_CH_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 1 ;         //! TIM3时钟使能
  
    RCC -> APB2ENR |= 1 << 2 ;                //! 打开A口时钟
    RCC -> APB2ENR |= 1 << 3 ;                //! 打开B口时钟
  
    GPIO_Init(GPIOA , 6 , GPIO_Mode_AF_OD) ;  //! PA6   推挽输出
    GPIO_Init(GPIOA , 7 , GPIO_Mode_AF_OD) ;  //! PA7   推挽输出
    GPIO_Init(GPIOB , 0 , GPIO_Mode_AF_OD) ;  //! PB0   推挽输出
    GPIO_Init(GPIOB , 1 , GPIO_Mode_AF_OD) ;  //! PB1   推挽输出

    TIM3->ARR = arr ;                //! 设定计数器自动重装值 
    TIM3->PSC = psc ;                //! 预分频器
  
    TIM3->CCMR1 |= 6<<4 ;            //! CH1 PWM2模式  
    TIM3->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     
    TIM3->CCER |= 1<<0 ;             //! OC1 输出使能      
  
    TIM3->CCMR1 |= 6<<12 ;           //! CH2 PWM2模式  
    TIM3->CCMR1 |= 1<<11 ;           //! CH2 预装载使能     
    TIM3->CCER |= 1<<4 ;             //! OC2 输出使能      
  
    TIM3->CCMR2 |= 6<<4 ;            //! CH3 PWM2模式  
    TIM3->CCMR2 |= 1<<3 ;            //! CH3 预装载使能     
    TIM3->CCER |= 1<<8 ;             //! OC3 输出使能      
  
    TIM3->CCMR2 |= 6<<12 ;           //! CH4 PWM2模式  
    TIM3->CCMR2 |= 1<<11 ;           //! CH4 预装载使能     
    TIM3->CCER |= 1<<12 ;            //! OC4 输出使能      

    TIM3->CR1 = 0x80 ;               //! ARPE使能 
    TIM3->CR1 |= 0x01 ;              //! 使能定时器3         
}

/**
 * @brief  定时器3 CH1 PWM 初始化
 **/
void PWM_TIM4_CH1_Init(u16 arr , u16 psc)
{
    RCC -> APB1ENR |= 1 << 2 ;       //! TIM4时钟使能
    RCC -> APB2ENR |= 1 << 3 ;       //! 使能GPIOB时钟 
    
    GPIO_Init(GPIOB , 6 , GPIO_Mode_AF_OD) ;  //! PB6   推挽输出
   
    TIM4->ARR = arr ;                //! 设定计数器自动重装值 
    TIM4->PSC = psc ;                //! 预分频器
  
    TIM4->CCMR1 |= 6<<4 ;            //! CH1 PWM2模式  
    TIM4->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     
    TIM4->CCER |= 1<<0 ;             //! OC1 输出使能      

    TIM4->CR1 = 0x80 ;               //! ARPE使能 
    TIM4->CR1 |= 0x01 ;              //! 使能定时器4        
}

/**
 * @brief  定时器4 All CH PWM 初始化
 **/
void PWM_TIM4_All_CH_Init(u16 arr , u16 psc)
{
    RCC->APB1ENR |= 1 << 2 ;         //! TIM4时钟使能
    
    GPIO_Init(GPIOB , 6 , GPIO_Mode_AF_OD) ;  //! PB6   推挽输出
    GPIO_Init(GPIOB , 7 , GPIO_Mode_AF_OD) ;  //! PB7   推挽输出
    GPIO_Init(GPIOB , 8 , GPIO_Mode_AF_OD) ;  //! PB8   推挽输出
    GPIO_Init(GPIOB , 9 , GPIO_Mode_AF_OD) ;  //! PB9   推挽输出

    TIM4->ARR = arr ;                //! 设定计数器自动重装值 
    TIM4->PSC = psc ;                //! 预分频器
  
    TIM4->CCMR1 |= 6<<4 ;            //! CH1 PWM2模式  
    TIM4->CCMR1 |= 1<<3 ;            //! CH1 预装载使能     
    TIM4->CCER |= 1<<0 ;             //! OC1 输出使能    
  
    TIM4->CCMR1 |= 6<<12 ;           //! CH2 PWM2模式  
    TIM4->CCMR1 |= 1<<11 ;           //! CH2 预装载使能     
    TIM4->CCER |= 1<<4 ;             //! OC2 输出使能      
  
    TIM4->CCMR2 |= 6<<4 ;            //! CH3 PWM2模式  
    TIM4->CCMR2 |= 1<<3 ;            //! CH3 预装载使能     
    TIM4->CCER |= 1<<8 ;             //! OC3 输出使能      
  
    TIM4->CCMR2 |= 6<<12 ;           //! CH4 PWM2模式  
    TIM4->CCMR2 |= 1<<11 ;           //! CH4 预装载使能     
    TIM4->CCER |= 1<<12 ;            //! OC4 输出使能      

    TIM4->CR1 = 0x80 ;               //! ARPE使能 
    TIM4->CR1 |= 0x01 ;              //! 使能定时器3         
}
