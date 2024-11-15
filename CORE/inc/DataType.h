/****************************************************************************************
* 文件名称: DataType.h
* 
* 创建时间：2019/12/11
*
* 修改时间：2021/03/11
*
* 作    者：science
*
* 版    本：V1.1
*
* 文摘描述：常用数据缩写
*
* 说    明：2021/03/11：增加空指针定义
****************************************************************************************/ 
#ifndef __DATA_TYPE_H__
#define __DATA_TYPE_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NULL
#define NULL 0
#endif

typedef signed            char s8;     /* 有符号8位数据           */
typedef signed   short     int s16;    /* 有符号16位数据          */
typedef signed             int s32;    /* 有符号32位数据          */
typedef signed   long long int s64;    /* 有符号64位数据          */

typedef unsigned          char u8;     /* 无符号8位数据           */
typedef unsigned short     int u16;    /* 无符号16位数据          */
typedef unsigned           int u32;    /* 无符号32位数据          */
typedef unsigned long long int u64;    /* 无符号64位数据          */

typedef signed            char const sc8;        /* 只读8位有符号数据     */
typedef signed       short int const sc16;       /* 只读16位有符号数据    */
typedef signed             int const sc32;       /* 只读32位有符号数据    */
typedef signed   long long int const sc64;       /* 只读64位有符号数据    */

typedef unsigned            char const uc8;      /* 只读8位无符号数据     */
typedef unsigned       short int const uc16;     /* 只读16位无符号数据    */
typedef unsigned             int const uc32;     /* 只读32位无符号数据    */
typedef unsigned   long long int const uc64;     /* 只读64位无符号数据    */

typedef volatile signed          char vs8;
typedef volatile signed     short int vs16;
typedef volatile signed           int vs32;
typedef volatile signed long long int vs64;

typedef volatile unsigned          char vu8;
typedef volatile unsigned     short int vu16;
typedef volatile unsigned           int vu32;
typedef volatile unsigned long long int vu64;

typedef volatile signed          char const vsc8;
typedef volatile signed     short int const vsc16;
typedef volatile signed           int const vsc32;
typedef volatile signed long long int const vsc64;

typedef volatile unsigned          char const vuc8;
typedef volatile unsigned     short int const vuc16;
typedef volatile unsigned           int const vuc32;
typedef volatile unsigned long long int const vuc64;

#ifdef __cplusplus
}
#endif

#endif /*  __DATA_TYPE_H__  */

