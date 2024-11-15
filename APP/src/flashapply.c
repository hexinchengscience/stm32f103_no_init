/****************************************************************************************
* 文件名称: flashapply.cpp
* 
* 创建时间：2020/11/26
*
* 修改时间：2020/11/26
*
* 作    者：默先
*
* 版    本：V1.0
*
* 文摘描述：系统参数函数
*
* 说    明：
****************************************************************************************/ 
#include "flashapply.h"

SystemParamTypeDef SystemParamStruct ;    //! 屏幕参数结构体变量

/**
 * @brief  读取系统参数
 **/
void System_Read_Param(void)
{
    FLASH_Read_N_Byte(defSystemParamAddr , SystemParamStruct.byte , defSystemParamLen) ;
}

/**
 * @brief  保存系统参数
 **/
void System_Write_Param(void)
{
    FLASH_Write_N_Byte(defSystemParamAddr , SystemParamStruct.byte , defSystemParamLen) ;
}

/**
 * @brief  系统参数初始化
 **/
void System_Param_Init(void)
{
    System_Read_Param() ;  //! 读取参数
  
    if(SystemParamStruct.SystemStatus != 0x5A)   //! 系统默认值
    {
        //! 当存储器为写数据时，ID号默认0，设置过之后，将由出厂设置
        SystemParamStruct.SystemStatus = 0x5A ;
        SystemParamStruct.DeviceId = 0x01 ;      //! ID默认为1
        SystemParamStruct.SystemVolume = 10 ;    //! 系统默认声音10
        SystemParamStruct.SystemLightness = 10 ; //! 系统默认亮度10
      
        System_Write_Param() ;                   //! 保存数据
    }  
}

