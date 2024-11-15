#ifndef _DMA_H_
#define _DMA_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"

#include "Cortex-M3.h"
#include "STM32F103.h"
#include "adc.h"

void DMA_Channel1_Init(void) ;   //! DMA channel 1初始化

#ifdef __cplusplus
}
#endif
  
#endif //! _DMA_H_

