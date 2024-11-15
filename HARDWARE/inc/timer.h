#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"

#include "Cortex-M3.h"
#include "STM32F103.h"
#include "system.h"
#include "gpio.h"

#define PWM_TIM1_CH1_Set_Duty(duty)     TIM1->CCR1 = duty 
#define PWM_TIM1_CH1N_Set_Duty(duty)    TIM1->CCR1 = duty 
#define PWM_TIM1_CH2N_Set_Duty(duty)    TIM1->CCR2 = duty 
#define PWM_TIM1_CH3N_Set_Duty(duty)    TIM1->CCR3 = duty 
#define PWM_TIM1_CH4_Set_Duty(duty)     TIM1->CCR4 = duty 

#define PWM_TIM2_CH2_Set_Duty(duty)     TIM2->CCR2 = duty 

#define PWM_TIM3_CH1_Set_Duty(duty)     TIM3->CCR1 = duty 
#define PWM_TIM3_CH2_Set_Duty(duty)     TIM3->CCR2 = duty 
#define PWM_TIM3_CH3_Set_Duty(duty)     TIM3->CCR3 = duty 
#define PWM_TIM3_CH4_Set_Duty(duty)     TIM3->CCR4 = duty 

#define PWM_TIM4_CH1_Set_Duty(duty)     TIM4->CCR1 = duty 

void TIM2_Init(u16 arr , u16 psc) ;                  //! 定时器2中断

void PWM_TIM1_CH1_Init(u16 arr , u16 psc) ;          //! 定时器1 CH1 初始化
void PWM_TIM1_CH1N_Init(u16 arr , u16 psc) ;         //! 定时器1 CH1N 初始化
void PWM_TIM1_CH2N_Init(u16 arr , u16 psc) ;         //! 定时器1 CH2N 初始化
void PWM_TIM1_CH3N_Init(u16 arr , u16 psc) ;         //! 定时器1 CH3N 初始化
void PWM_TIM1_CH4_Init(u16 arr , u16 psc) ;          //! 定时器1 CH4 初始化
void PWM_TIM1_CH1_CH3_CH4_Init(u16 arr , u16 psc) ;  //! 定时器1 CH1 CH3N CH4初始化
void PWM_TIM1_All_CH_Init(u16 arr , u16 psc) ;       //! 定时器3 All CH PWM 初始化

void PWM_TIM2_CH1_Init(u16 arr , u16 psc) ;          //! 定时器2 CH1 初始化
void PWM_TIM2_CH2_Init(u16 arr , u16 psc) ;          //! 定时器2 CH2 初始化

void PWM_TIM3_CH1_Init(u16 arr , u16 psc) ;          //! 定时器3 CH1 初始化
void PWM_TIM3_CH2_Init(u16 arr , u16 psc) ;          //! 定时器3 CH2 初始化
void PWM_TIM3_CH3_Init(u16 arr , u16 psc) ;          //! 定时器3 CH3 初始化
void PWM_TIM3_CH4_Init(u16 arr , u16 psc) ;          //! 定时器3 CH4 初始化

void PWM_TIM4_CH1_Init(u16 arr , u16 psc) ;          //! 定时器4 CH1 初始化

#ifdef __cplusplus
}
#endif

#endif /*  __TIMER_H__  */
