/*
  * ȫ�µ�ϵͳAPI�ܹ�
  *
  */

#ifndef _SYSTEM_H_
#define _SYSTEM_H_ 1

typedef char                sbyte;
typedef unsigned char       byte;
typedef unsigned short      ushort;
typedef unsigned int        uint;
typedef char*               string;
//typedef unsigned char       bool;
#define true                1
#define false               0

//typedef uint				Pin;
struct Pin
{
	ushort Group;
	ushort Port;
};

struct TBase
{
	void (*Init)(void);
	void (*Uninit)(void);
};

struct TCore : TBase
{
    void (*Printf)(const string format, ...);
    void (*LcdPrintf)(const string format,...);
    void* (*Malloc)(uint len);
    void (*Free)(void*  ptr);
    void (*Sleep)(uint ms);
    void (*Delay)(uint us);
    void (*DisableInterrupts)();
    void (*EnableInterrupts)();
    uint (*WaitForEvents)(uint wakeupSystemEvents, uint timeout_Milliseconds);
    uint ComputeCRC(const void* rgBlock, int nLength, uint crc);
};

struct TBoot : TBase
{
	
};

struct TMem : TBase
{
    int (*snprintf)(string buffer, uint len, const string format, ...);
    int (*stricmp)(const string dst, const string src);
    int (*strncmp)(const string str1, const string str2, uint num);
    uint (*strlen)(const string str);
    void *(*memcpy)(void * dst, const void * src, uint len);
    void *(*memset)(void * dst, int value, uint len);
};

struct TFlash : TBase
{
    int (*Erase)(uint address, uint count);
    int (*Read)(uint address, uint count,byte *buffer);
    int (*Write)(uint address, uint count,byte *buffer);
};

struct TIO : TBase
{
    //void (*DisablePin)(Pin pin, GPIO_RESISTOR ResistorState, uint Direction, GPIO_ALT_MODE AltFunction);
    //bool (*EnableInputPin)(Pin pin, bool GlitchFilterEnable, GPIO_INTERRUPT_SERVICE_ROUTINE ISR, GPIO_INT_EDGE IntEdge, GPIO_RESISTOR ResistorState);
    void (*EnableOutputPin)(Pin pin, bool initialState);
    bool (*GetPinState)(Pin pin);
    void (*SetPinState)(Pin pin, bool state);
};

struct TUsart : TBase
{
    bool (*Initialize)(int ComPortNum, int BaudRate, int Parity, int DataBits, int StopBits, int FlowValue);
    bool (*Uninitialize)(int ComPortNum);
    int  (*Write)(int ComPortNum, const string Data, uint size);
    int  (*Read)(int ComPortNum, string Data, uint size);
    bool (*Flush)(int ComPortNum);
    int  (*BytesInBuffer)(int ComPortNum, bool fRx);
    void (*DiscardBuffer)(int ComPortNum, bool fRx);
};

struct TAnalog : TBase
{
	//bool (*DA_Initialize)(ANALOG_CHANNEL channel, int precisionInBits);
	//void (*DA_Write)(ANALOG_CHANNEL channel, int level);
	//bool (*AD_Initialize)(ANALOG_CHANNEL channel, int precisionInBits);
	//int (*AD_Read)(ANALOG_CHANNEL channel);
};

struct TPwm : TBase
{
    //bool (*Initialize)(PWM_CHANNEL channel);
    //bool (*Uninitialize)(PWM_CHANNEL channel);
    //bool (*ApplyConfiguration)(PWM_CHANNEL channel, Pin pin, uint& period, uint& duration, PWM_SCALE_FACTOR &scale, bool invert);
    //bool (*Start)(PWM_CHANNEL channel, Pin pin);
    //void (*Stop)(PWM_CHANNEL channel, Pin pin);
    //Pin (*GetPinForChannel)(PWM_CHANNEL channel);
};

struct TSpi : TBase
{
    //bool (*WriteRead)(const SPI_CONFIGURATION& Configuration, byte* Write8, int WriteCount, byte* Read8, int ReadCount, int ReadStartOffset);
    //bool (*WriteRead16)(const SPI_CONFIGURATION& Configuration, ushort* Write16, int WriteCount, ushort* Read16, int ReadCount, int ReadStartOffset);
};

struct TI2c : TBase
{
    bool (*Initialize)();
    bool (*Uninitialize)();
    bool (*Execute)(ushort address,byte *inBuffer,int inCount,byte *outBuffer,int outCount,uint clockRateKhz,int timeout);
};

struct TLcd : TBase
{
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
};

// ȫ��ϵͳ��
// ����ָ������Ƕ�����Ҫ�ǿ��ǵ�ÿ��ģ�������չ��������Ӱ��ϵͳ������������
struct TSystem : TBase
{
	struct TBoot* Boot;
	struct TCore* Core;
	struct TMem* Mem;
	struct TFlash* Flash;
	struct TIO* IO;
	struct TUsart* Usart;
	struct TAnalog* Analog;
	struct TPwm* Pwm;
	struct TSpi* Spi;
	struct TI2c* I2c;
	struct TLcd* Lcd;
};

// ����ȫ�ֵ�Sys������
extern TSystem Sys;
void SysInit();

#endif //_SYSTEM_H_
