#ifndef _ARITHMETIC_H_
#define _ARITHMETIC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "DataType.h"
#include "system.h"

#define ToLower(c)       (c |  0x20)       //! 统一转换为小写
#define ToUpper(c)       (c & ~0x20)       //! 统一转换为大写

void NumberToChar(int number , char * chr) ;                    //! 数字转字符串
void Xor_Encryption_Deal(u8 * buffer , u8 secret , u8 len) ;    //! 异或加密处理
u8 Get_One_Byte_Random_Number(u8 index) ;                       //! 获取一个字节的随机数
u8 Is_Simple_Eual_Str(u8 * str1 , u8 *str2 , int len) ;         //! 两个简单的字符串是否相等

#ifdef __cplusplus
}
#endif

#endif //! _ARITHMETIC_H_
