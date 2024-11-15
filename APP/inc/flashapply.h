/****************************************************************************************
* 文件名称: flashapply.cpp
* 
* 创建时间：2019/12/20
*
* 修改时间：2019/12/20
*
* 作    者：默先
*
* 版    本：V1.0
*
* 文摘描述：手柄通信
*
* 说    明：
****************************************************************************************/ 
#ifndef _FLASHAPPLY_H_
#define _FLASHAPPLY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"
#include "systemdefine.h"          //! 系统宏定义头文件
#include "flash.h"

#define defSystemParamAddr           0x0800F000 //! 屏幕参数保存地址
#define defSystemParamLen            40         //! 参数数据长度  只能是偶数 保存是按两个字节为单位

#ifdef __CC_ARM                                 //! MDK 编译器需要使用的预处理
#pragma anon_unions                             //! 支持匿名结构体，联合体   
#endif
typedef struct                                  //! 屏幕参数保存
{
    union
    {
        struct 
        {
            u8 SystemStatus ;                   //! 此字节若为0xFF表示第一次使用 0x5A表示已经有数据保存
            u8 DeviceId ;                       //! 设备ID
            u8 SystemVolume ;                   //! 系统声音
            u8 SystemLightness ;                //! 系统亮度
        };
        u8 byte[defSystemParamLen] ;
    } ;
} SystemParamTypeDef ;                          //! 屏幕参数结构体

extern SystemParamTypeDef SystemParamStruct ;   //! 屏幕参数结构体变量

void System_Read_Param(void) ;                  //! 读取串口屏参数
void System_Write_Param(void) ;                 //! 保存串口屏参数
void System_Param_Init(void) ;                  //! 屏幕参数初始化

#ifdef __cplusplus
}
#endif

#endif //! _FLASHAPPLY_H_

