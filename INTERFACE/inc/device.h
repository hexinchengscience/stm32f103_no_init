#ifndef __DEVICE_H__
#define __DEVICE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"
#include "systemdefine.h"          //! 系统宏定义头文件
#include "gpio.h"
#include "timer.h"

#define LED0 PBout(5)  // DS0
#define LED1 PEout(5)  // DS1  

void Device_Init(void) ;                //! 外设初始化
void Device_Output_Close(void) ;        //! 关闭外设输出
void Device_Output(void) ;              //! 外设输出控制

#ifdef __cplusplus
}
#endif

#endif  //! __DEVICE_H__
