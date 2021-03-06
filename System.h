/*
  * 全新的系统API架构
  *
  */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "stm32.h"

/* 类型定义 */
typedef char            sbyte;
typedef unsigned char   byte;
typedef unsigned short  ushort;
typedef unsigned int    uint;
typedef char*           string;
typedef unsigned char   bool;
#define true            1
#define false           0

/* 引脚定义 */
typedef ushort			Pin;
#include "Pin.h"

/* 面向对象宏 */
/* 以结构体来定义一个类的头部和尾部，同时创建一个全局的初始化函数 */
#define _class(name) typedef struct T##name##_Def\
{\
	void (*Init)(struct T##name##_Def* this);\
	void (*Uninit)(struct T##name##_Def* this);

#define _class_end(name) } T##name;\
extern void T##name##_Init(T##name* this);


/* 核心定义 */
_class(Core)
    //void (*Printf)(const string format, ...);
    /*void (*LcdPrintf)(const string format,...);
    void* (*Malloc)(uint len);
    void (*Free)(void* ptr);*/
    void (*Sleep)(uint ms); // 毫秒级延迟
    void (*Delay)(uint us); // 微秒级延迟
    void (*DisableInterrupts)();    // 关闭中断
    void (*EnableInterrupts)();     // 打开中断
    //uint (*WaitForEvents)(uint wakeupSystemEvents, uint timeout_Milliseconds);
    //uint (*ComputeCRC)(const void* rgBlock, int nLength, uint crc);
_class_end(Core)

/* 引导 */
_class(Boot)
_class_end(Boot)

/* IO口 */
_class(IO)
    void (*Open)(Pin pin, GPIOMode_TypeDef mode);
    // mode=GPIO_Mode_IN/GPIO_Mode_OUT/GPIO_Mode_AF/GPIO_Mode_AN
    // speed=GPIO_Speed_50MHz/GPIO_Speed_2MHz/GPIO_Speed_10MHz
    // type=GPIO_OType_PP/GPIO_OType_OD
#ifdef STM32F0XX
    void (*OpenPort)(Pin pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed, GPIOOType_TypeDef type);
#else
    void (*OpenPort)(Pin pin, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed);
#endif
    void (*Close)(Pin pin);
    bool (*Read)(Pin pin);
    void (*Write)(Pin pin, bool state);
_class_end(IO)

/* 串口 */
_class(Usart)
    bool (*Open)(int com, int baudRate);
    bool (*Open2)(int com, int baudRate, int parity, int dataBits, int stopBits, int flowValue);
    void (*Close)(int com);
    void (*Write)(int com, const string data, int size);
    int  (*Read)(int com, string data, uint size);
    void (*Flush)(int com);
    //int  (*BytesInBuffer)(int com, bool fRx);
    //void (*DiscardBuffer)(int com, bool fRx);
_class_end(Usart)

/* 内存 */
_class(Mem)
    int (*snprintf)(string buffer, uint len, const string format, ...);
    int (*stricmp)(const string dst, const string src);
    int (*strncmp)(const string str1, const string str2, uint num);
    uint (*strlen)(const string str);
    void *(*memcpy)(void * dst, const void * src, uint len);
    void *(*memset)(void * dst, int value, uint len);
_class_end(Mem)

/* Flash存储 */
_class(Flash)
    int (*Erase)(uint address, uint count);
    int (*Read)(uint address, uint count,byte *buffer);
    int (*Write)(uint address, uint count,byte *buffer);
_class_end(Flash)

/* 模拟量 */
_class(Analog)
	//void (*DA_Write)(ANALOG_CHANNEL channel, int level);
	//bool (*AD_Initialize)(ANALOG_CHANNEL channel, int precisionInBits);
	//int (*AD_Read)(ANALOG_CHANNEL channel);
_class_end(Analog)

/* 串行总线 */
_class(Spi)
    //bool (*WriteRead)(const SPI_CONFIGURATION& Configuration, byte* Write8, int WriteCount, byte* Read8, int ReadCount, int ReadStartOffset);
    //bool (*WriteRead16)(const SPI_CONFIGURATION& Configuration, ushort* Write16, int WriteCount, ushort* Read16, int ReadCount, int ReadStartOffset);
_class_end(Spi)

/*typedef struct
{
	void (*Init)(void);
	void (*Uninit)(void);

    bool (*Initialize)();
    bool (*Uninitialize)();
    bool (*Execute)(ushort address,byte *inBuffer,int inCount,byte *outBuffer,int outCount,uint clockRateKhz,int timeout);
} TI2c;

typedef struct
{
	void (*Init)(void);
	void (*Uninit)(void);

    //bool (*Initialize)(PWM_CHANNEL channel);
    //bool (*Uninitialize)(PWM_CHANNEL channel);
    //bool (*ApplyConfiguration)(PWM_CHANNEL channel, Pin pin, uint& period, uint& duration, PWM_SCALE_FACTOR &scale, bool invert);
    //bool (*Start)(PWM_CHANNEL channel, Pin pin);
    //void (*Stop)(PWM_CHANNEL channel, Pin pin);
    //Pin (*GetPinForChannel)(PWM_CHANNEL channel);
} TPwm;

typedef struct
{
	void (*Init)(void);
	void (*Uninit)(void);

    void (*Clear)(uint color);
    void (*SetPixel)(int x,int y,uint color);
    uint (*GetPixel)(int x,int y);
    void (*DrawLine)(int x1,int y1,int x2,int y2,uint color);
    void (*DrawRectangle)(int x,int y,int width,int height,uint color);
    void (*DrawEllipse)(int x,int y,int width,int height,uint color);
    void (*DrawImage)(int x,int y,byte *bytData);
    void (*DrawImageEx)(int x,int y,byte *bytData,uint MaskColor);
    void (*DrawString)(int x,int y, string s,uint color);
    void (*DrawStringEx)(int x,int y,uint color,byte *fontdata,int width,int height,int count);
    void (*FillRectangle)(int x,int y,int width,int height,uint color);
    void (*FillEllipse)(int x,int y,int width,int height,uint color);
    void (*GetFrameBufferEx)(byte *bytData,uint offset,uint size);
    void (*SuspendLayout)();
    void (*ResumeLayout)();
} TLcd;
*/

/* 日志 */
/*_class(Log)
    int MessagePort;    // 消息口，默认0表示USART1

    void (*WriteLine)(const string format, ...);    // 输出一行日志，自动换行
    void (*DebugLine)(const string format, ...);    // 输出一行日志，Sys.Debug时有效
_class_end(Log)
*/

// 全局系统根
typedef struct
{
	void (*Init)(void);
	void (*Uninit)(void);
	
    bool Debug; // 是否调试
	byte Clock;  // 系统时钟
    byte MessagePort;    // 消息口，默认0表示USART1

	TBoot Boot;
	TCore Core;
	TIO IO;
	TUsart Usart;
	TMem Mem;
	TFlash Flash;
	TAnalog Analog;
	TSpi Spi;
	/*TI2c I2c;
	TPwm Pwm;
	TLcd Lcd;
	TLog Log;*/
} TSystem;

// 声明全局的Sys根对象
extern TSystem Sys;

// 使用何种模块的宏定义
#define using(module) Sys.module.Init = T##module##_Init;

#endif //_SYSTEM_H_
