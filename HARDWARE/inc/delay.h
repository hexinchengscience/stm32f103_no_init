#ifndef __DELAY_H__
#define __DELAY_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"
#include "system.h"

void Delay_N_us(int nus);
void Delay_N_ms(int nms);
  
#ifdef __cplusplus
}
#endif

#endif //__DELAY_H__
