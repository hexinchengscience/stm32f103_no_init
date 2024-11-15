/****************************************************************************************
* 文件名称: can.cpp
* 
* 创建时间：2021/04/11
*
* 修改时间：2021/04/11
*
* 作    者：science
*
* 版    本：V1.0
*
* 文摘描述：CAN通信
*
* 说    明：
****************************************************************************************/ 
#include "can.h"

/**
 * @brief  CAN1 初始化
 *
 * @param  tsjw : 波特率设置相关参数
 *         tbs2 : 
 *         tbs1 : 
 *         brp  :
 *         mode :  
 *
 * @return 0 : 初始化成功
 *         1 : 参数错误
 *         2 : 初始化失败 
 *         3 : 退出初始化模式失败
 *
 * @note   设tsjw = 1 、tbs1 = 8 、tbs2 = 9 、brp = 4，波特率 = 36000 / [(1 + 8 + 9) * 4] = 500Kbps
 **/
u8 CAN_Mode_Init(u8 tsjw , u8 tbs2 , u8 tbs1 , u16 brp , u8 mode)
{
    u16 i = 0 ;
  
    //! 判断参数是否正确
     if(tsjw == 0 || tbs2 == 0 || tbs1 == 0 || brp == 0) return 1;
  
    //! 先减去1.再用于设置
    tsjw -= 1 ; tbs2 -= 1 ; tbs1 -= 1 ; brp -= 1 ;
  
    //! 硬件IO口初始化
    RCC -> APB2ENR |= 1 << 2 ;                //! 打开A口时钟
    GPIO_Init(GPIOA , 11 , GPIO_Mode_IPU) ;   //! PA11  RX 上拉输入
    GPIO_Init(GPIOA , 12 , GPIO_Mode_AF_OD) ; //! PA12  TX  复用推挽输出
    GPIOA -> ODR |= 3 << 11 ;                 //! 引脚初始状态
            
    RCC -> APB1ENR |= 1 << 25 ;                //! 使能CAN时钟 CAN使用的是APB1的时钟(max:36M)
    CAN1 -> MCR = 0x0000 ;                    //! 退出睡眠模式(同时设置所有位为0)
    CAN1 -> MCR |= 1 << 0 ;                    //! 请求CAN进入初始化模式
    while((CAN1 -> MSR & 1 << 0) == 0)
    {
        i ++ ; if(i > 100) return 2 ;          //! 进入初始化模式失败
    }
    CAN1 -> MCR |= 0 << 7 ;                    //! 非时间触发通信模式
    CAN1 -> MCR |= 0 << 6 ;                    //! 软件自动离线管理
    CAN1 -> MCR |= 0 << 5 ;                    //! 睡眠模式通过软件唤醒(清除CAN1->MCR的SLEEP位)
    CAN1 -> MCR |= 1 << 4 ;                    //! 禁止报文自动传送
    CAN1 -> MCR |= 0 << 3 ;                    //! 报文不锁定,新的覆盖旧的
    CAN1 -> MCR |= 0 << 2 ;                    //! 优先级由报文标识符决定
    
    //! 波特率 : Fpclk1 / ((Tbs1 + Tbs2 + 1) * Fdiv)
    CAN1 -> BTR = 0x00000000 ;                //! 清除原来的设置.
    CAN1 -> BTR |= mode << 30 ;                //! 模式设置 0,普通模式;1,回环模式;
    CAN1 -> BTR |= tsjw << 24 ;               //! 重新同步跳跃宽度(Tsjw)为tsjw+1个时间单位
    CAN1 -> BTR |= tbs2 << 20 ;               //! Tbs2=tbs2+1个时间单位
    CAN1 -> BTR |= tbs1 << 16 ;                //! Tbs1=tbs1+1个时间单位
    CAN1 -> BTR |= brp << 0 ;                  //! 分频系数(Fdiv)为brp+1
              
    CAN1 -> MCR &= ~(1 << 0) ;                //! 请求CAN退出初始化模式
    while((CAN1->MSR&1<<0)==1)
    {
        i++ ; if(i > 0xFFF0) return 3 ;       //! 退出初始化模式失败
    }
    
    //! 过滤器初始化
    CAN1 -> FMR |= 1 << 0 ;                    //! 过滤器组工作在初始化模式
    CAN1 -> FA1R &= ~(1 << 0) ;                //! 过滤器0不激活
    CAN1 -> FS1R |= 1 << 0 ;                   //! 过滤器位宽为32位.
    CAN1 -> FM1R |= 0 << 0 ;                  //! 过滤器0工作在标识符屏蔽位模式
    CAN1 -> FFA1R |= 0 << 0 ;                  //! 过滤器0关联到FIFO0
    CAN1 -> sFilterRegister[0].FR1 = 0X00000000 ;//! 32位ID
    CAN1 -> sFilterRegister[0].FR2 = 0X00000000 ;//! 32位MASK
    CAN1 -> FA1R |= 1 <<0 ;                    //! 激活过滤器0
    CAN1 -> FMR &= 0 << 0 ;                    //! 过滤器组进入正常模式

  #if CAN_RX0_INT_ENABLE                      //! 使用中断接收
    CAN1 -> IER |= 1 << 1 ;                    //! FIFO0消息挂号中断允许.      
    NVIC_Set_IRQn(USB_LP_CAN1_RX0_IRQn , 0x1F) ;
  #endif
    
    return 0 ;                                //! 初始化成功
}   

/**
 * @brief  CAN 发送数据
 *
 * @param  id  : 发送ID号
 *         ide : 0 标准帧  1 扩展帧
 *         rtr : 
 *         len : 发送数据长度
 *         dat : 数据数组
 *
 * @return 0~3 : 邮箱编号. 0xFF : 无有效邮箱.
 **/
u8 CAN_Tx_Msg(u32 id , u8 ide , u8 rtr , u8 len , u8 * dat)
{     
    u8 mbox ;    
    //! 查找当前空闲邮箱
    if(CAN1 -> TSR &(1 << 26)) mbox = 0 ;      //! 邮箱0为空
    else if(CAN1 -> TSR &(1 << 27)) mbox = 1 ;//! 邮箱1为空
    else if(CAN1 -> TSR &(1 << 28)) mbox = 2 ;//! 邮箱2为空
    else return 0xFF ;                        //! 无空邮箱,无法发送 
  
    //! 设置ID号
    CAN1 -> sTxMailBox[mbox].TIR = 0 ;        //! 清除之前的设置
    if(ide == 0)          //! 标准帧
    {
        id &= 0x7FF ;     //! 取低11位stdid
        id<<=21;      
    }else                  //! 扩展帧
    {
        id &= 0x1FFFFFFF ;//! 取低32位extid
        id <<= 3 ;                     
    }
    
    CAN1 -> sTxMailBox[mbox].TIR |= id ;      //! 设置ID等参数
    CAN1 -> sTxMailBox[mbox].TIR |= ide << 2 ;    
    CAN1 -> sTxMailBox[mbox].TIR |= rtr << 1 ;
    
    len &= 0x0F ;                             //! 得到低四位
    CAN1 -> sTxMailBox[mbox].TDTR &= ~(0x0000000F) ;
    CAN1 -> sTxMailBox[mbox].TDTR |= len ;    //! 设置DLC.
    
    //! 待发送数据存入邮箱.
    CAN1 -> sTxMailBox[mbox].TDHR = (((u32)dat[7] << 24) | ((u32)dat[6] << 16) | ((u32)dat[5] << 8) | ((u32)dat[4])) ;
    CAN1 -> sTxMailBox[mbox].TDLR = (((u32)dat[3] << 24) | ((u32)dat[2] << 16) | ((u32)dat[1] << 8) | ((u32)dat[0])) ;

    CAN1 -> sTxMailBox[mbox].TIR |= 1 << 0 ;   //! 请求发送邮箱数据
    return mbox ;
}

/**
 * @brief  获得发送状态
 * 
 * @param  mbox : 邮箱编号;
 *
 * @return 发送状态. 0x00:挂起;0x05:发送失败;0x07:发送成功.
 **/
u8 CAN_Tx_Staus(u8 mbox)
{  
    u8 sta=0;              
    switch(mbox)
    {
        case 0: 
        {
            sta |= CAN1 -> TSR & (1 << 0) ;           //! RQCP0
            sta |= CAN1 -> TSR & (1 << 1) ;           //! TXOK0
            sta |=((CAN1 -> TSR & (1 << 26)) >> 24) ;//! TME0
            break;
        }
        case 1: 
        {
            sta |= CAN1 -> TSR & (1 << 8) >> 8 ;     //! RQCP1
            sta |= CAN1 -> TSR & (1 << 9) >> 8 ;     //! TXOK1
            sta |=((CAN1 -> TSR & (1 << 27)) >> 25) ;//! TME1     
            break;
        }
        case 2: 
        {
            sta |= CAN1 -> TSR & (1 << 16) >> 16 ;   //! RQCP2
            sta |= CAN1 -> TSR & (1 << 17) >> 16 ;   //! TXOK2
            sta |=((CAN1 -> TSR & (1 << 28)) >> 26) ;//! TME2
            break;
        }
        default : {sta = 0x05 ; break ; }            //! 邮箱号不对,肯定失败.
    }
    return sta ;
} 

/**
 * @brief  得到在FIFO0/FIFO1中接收到的报文个数.
 * 
 * @param  /fifox:0/1.FIFO编号;
 *
 * @return FIFO0/FIFO1中的报文个数.
 **/
u8 CAN_Msg_Pend(u8 fifox)
{
    if(fifox == 0) return CAN1 -> RF0R & 0x03 ; 
    else if(fifox == 1) return CAN1 -> RF1R & 0x03 ; 
    else return 0 ;
}

/**
 * @brief  接收数据
 * 
 * @param  fifox : 邮箱号
 *         id    : 标准ID(11位)/扩展ID(11位+18位)
 *         ide   : 0 标准帧;1 扩展帧
 *         rtr   : 0 数据帧;1 远程帧
 *         len   : 数据长度
 *         dat   : 接收数组
 *
 **/
void CAN_Rx_Msg(u8 fifox , u32 * id , u8 * ide ,u8 * rtr ,u8 * len , u8 * dat)
{     
    * ide = CAN1 -> sFIFOMailBox[fifox].RIR & 0x04 ;  //! 得到标识符选择位的值  
     if(*ide==0)    //! 标准标识符
    {
        * id = CAN1 -> sFIFOMailBox[fifox].RIR >> 21 ;
    }else           //! 扩展标识符
    {
        * id = CAN1 -> sFIFOMailBox[fifox].RIR >> 3 ;
    }
    * rtr = CAN1 -> sFIFOMailBox[fifox].RIR & 0x02 ;  //! 得到远程发送请求值.
    * len = CAN1 -> sFIFOMailBox[fifox].RDTR & 0x0F ;  //! 得到DLC
     //* fmi =(CAN1 -> sFIFOMailBox[FIFONumber].RDTR>>8) & 0xFF ;//! 得到FMI
    
    //! 接收数据
    dat[0] = CAN1 -> sFIFOMailBox[fifox].RDLR & 0xFF;
    dat[1] = (CAN1 -> sFIFOMailBox[fifox].RDLR >> 8) & 0xFF;
    dat[2] = (CAN1 -> sFIFOMailBox[fifox].RDLR >> 16) & 0xFF;
    dat[3] = (CAN1 -> sFIFOMailBox[fifox].RDLR >> 24) & 0xFF;    
    dat[4] = CAN1 -> sFIFOMailBox[fifox].RDHR & 0xFF ;
    dat[5] = (CAN1 -> sFIFOMailBox[fifox].RDHR >> 8) & 0xFF;
    dat[6] = (CAN1 -> sFIFOMailBox[fifox].RDHR >> 16) & 0xFF;
    dat[7] = (CAN1 -> sFIFOMailBox[fifox].RDHR >> 24) & 0xFF;    
    
    if(fifox == 0) CAN1 -> RF0R |= 0x20 ;      //! 释放FIFO0邮箱
    else if(fifox == 1) CAN1 ->RF1R |= 0x20 ;  //! 释放FIFO1邮箱   
}

#if CAN_RX0_INT_ENABLE  //使能RX0中断
//中断服务函数          
void USB_LP_CAN1_RX0_IRQHandler(void)
{
    u8 rxbuf[8] , ide , rtr , len ; u32 id ;
    
     CAN_Rx_Msg(0 , & id , & ide , & rtr , & len , rxbuf) ;
    CAN_Send_Msg(rxbuf , len) ;
}
#endif

/**
 * @brief  CAN发送一组数据
 * 
 * @param  msg : 需要发送的数据
 *         len : 数据长度(最大为8)
 *
 * @return 0 : 成功  其他 失败
 **/
u8 CAN_Send_Msg(u8 * msg , u8 len)
{  
    u8 mbox ; u16 i = 0 ;    

    mbox = CAN_Tx_Msg(0x12345678 , 0 , 0 , len , msg) ;  //! 发送数据
    while((CAN_Tx_Staus(mbox)!=0x07)&&(i<0xFFF)) i ++ ;  //! 等待发送结束
    if(i >= 0xFFF) return 1 ;                             //! 发送失败
    return 0 ;                                           //! 发送成功
}

/**
 * @brief  CAN口接收数据查询
 * 
 * @param  buf : 接收数据存放数组
 *
 * @return 0 : 数据被收到  其他 接收的数据长度
 **/
u8 CAN_Receive_Msg(u8 * buf)
{              
    u32 id ; u8 ide , rtr , len ; 
  
    if(CAN_Msg_Pend(0)==0) return 0 ;                    //! 没有接收到数据,直接退出    
    CAN_Rx_Msg(0 , & id , & ide , & rtr , & len , buf) ;//! 读取数据
  
    return len ;  //! 接收的数据长度
}

