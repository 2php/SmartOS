#include "stm32f0xx.h"
#include "System.h"

#ifndef BIT
#define BIT(x)	(1 << (x))
#endif

ushort fac_ms;//ȫ�ֱ���
byte fac_us;//ȫ�ֱ���

/****************************************************
�������ܣ���ʱ��ʼ��
���������SYSCLK : ϵͳʱ��(48)MHZ
�����������
��    ע����
*****************************************************/
void delay_init(uint clk)
{
     SysTick->CTRL &=~BIT(2);//ѡ���ⲿʱ��
	 SysTick->CTRL &=~BIT(1);//�رն�ʱ������0����ж�����
	 fac_us = clk/8;//�����SysTick����ֵ
	 fac_ms = (ushort)fac_us*1000;	 
}

/****************************************************
�������ܣ�ms����ʱ
���������nms : ����
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/							    
void delay_ms(uint nms)
{
   	  SysTick->LOAD = (uint)fac_ms*nms-1;//����ʱ��ֵ
	  SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	  SysTick->CTRL |= BIT(0);//SysTickʹ��
	  while(!(SysTick->CTRL&(1<<16)));//�ж��Ƿ����0
	  SysTick->CTRL &=~BIT(0);//�ر�SysTick
}

/****************************************************
�������ܣ�us����ʱ
���������nus : ΢��
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/		    								   
void delay_us(uint nus)
{		
	  SysTick->LOAD = (uint)fac_us*nus-1;//����ʱ��ֵ
	  SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	  SysTick->CTRL |= BIT(0);//SysTickʹ��
	  while(!(SysTick->CTRL&(1<<16)));//�ж��Ƿ����0
	  SysTick->CTRL &=~BIT(0);//�ر�SysTick
}

void TCore_Init(TCore* this)
{
    this->Sleep = delay_ms;
    this->Delay = delay_us;
    
    delay_init(Sys.Clock/1000000);
}
