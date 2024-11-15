#ifndef __MICROELECTRIC_H__
#define __MICROELECTRIC_H__

#include "DataType.h"
#include "STM32F103.h"
#include "device.h"

//! 微电类 PWM模式---------------------------------------------------------------------------------
class MicroElectric
{
public:
    static u32 *HeartbeatCount ;      //! 心跳计数
    static u16 *FixedValueCount ;     //! 固定频率计数
private:
    u16 ValidSetDuty ;                //! 设备设定占空比
    u16 ValidNowDuty ;                //! 设备当前运行时占空比
    u16 FixedValidValue ;             //! 固定占空比有效值
    u16 FixedAllValue ;               //! 固定占空比总时间
    void (*FixedOn)(void) ;           //! 固定频率固定占空比打开硬件接口
    void (*FixedOff)(void) ;          //! 固定频率固定占空比关闭硬件接口
    void (*SetDuty)(u16) ;            //! 设置占空比
    u32 ValidTime ;                   //! 模式有效输出时间
    u32 AllTime ;                     //! 模式周期时间
    u32 RiseTime ;                    //! 上升时间
    u32 DownTime ;                    //! 下降时间
public:
    MicroElectric(void (*fon)(void) , void (*foff)(void) , void (*duty)(u16)) {FixedOn = fon ; FixedOff = foff ; SetDuty = duty ;} //! 类初始化 , 设置占空比函数指针
    void MicroElectricOutput(void) ;  //! 硬件输出函数，每个定时器周期执行一次 
    void MicroElectricSetMode(u8 mode) ;                   //! 微电输出模式设置 
    void SetValidSetDuty(u16 duty) {ValidSetDuty = duty ;} //! 设置占空比
    u16 GetValidNowDuty(void) {return ValidNowDuty ;}      //! 读取当前占空比
    void CloseSlice(void) {ValidSetDuty = 0 ; ValidNowDuty = 0 ; SetDuty(0) ; }   //! 关闭通道输出
    void SetValidTime(u32 time) {ValidTime = time ;}       //! 设置有效时间
    void SetAllTime(u32 time) {AllTime = time ;}           //! 设置周期总时间
    void SetRiseTime(u32 time) {RiseTime = time ;}         //! 设置上升时间
    void SetDownTime(u32 time) {DownTime = time ;}         //! 设置下降时间
    u32 GetAllTime(void) {return AllTime ;}                //! 获取周期总时间
    u32 GetValidTime(void) {return ValidTime ;}            //! 获取有效时间
};

extern const u8 MicroElectricPwmDutyArray[] ;
extern MicroElectric MicroElectricRectusRecovery , MicroElectricGyromagneticHand ;

#endif //! __MICROELECTRIC_H__
