#ifndef _ADC_H_
#define _ADC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"
#include "Cortex-M3.h"
#include "STM32F103.h"
#include "gpio.h"

extern u16 AdcValue[3] , AdcAverage[3] ;

void ADC_Init(void) ;          //! ADC 初始化
void ADC_Init2(void) ;
void ADC_Inject_Init(void) ;       //! ADC 注入通道初始化
u16 ADC_Read_CH0_Value(void);  //! ADC 读取通道0的值
void Calculate_Adc_Average(void) ; //! 计算ADC平均值 

#ifdef __cplusplus
}
#endif
  
#endif //! _ADC_H_
