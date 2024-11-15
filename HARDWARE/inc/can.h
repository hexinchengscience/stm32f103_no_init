#ifndef __CAN_H__
#define __CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"
#include "STM32F103.h"
#include "system.h"
#include "gpio.h"

//! CAN接收RX0中断使能
#define CAN_RX0_INT_ENABLE  1    //0,不使能;1,使能.                    
                                                
u8 CAN_Mode_Init(u8 tsjw,u8 tbs2,u8 tbs1,u16 brp,u8 mode);        //! CAN初始化
u8 CAN_Tx_Msg(u32 id,u8 ide,u8 rtr,u8 len,u8 *dat);                //! 发送数据
u8 CAN_Msg_Pend(u8 fifox);                                        //! 查询邮箱报文
void CAN_Rx_Msg(u8 fifox,u32 *id,u8 *ide,u8 *rtr,u8 *len,u8 *dat);//! 接收数据
u8 CAN_Tx_Staus(u8 mbox);                                          //! 返回发送状态
u8 CAN_Send_Msg(u8* msg,u8 len);                                  //! 发送数据
u8 CAN_Receive_Msg(u8 *buf);                                      //! 接收数据

#ifdef __cplusplus
}
#endif
  
#endif /*  __CAN_H__  */
