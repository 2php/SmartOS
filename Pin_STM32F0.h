#ifndef _PIN_STM32F1_H_
#define _PIN_STM32F1_H_ 1

#include "Pin.h"

// ��ȡ������
#define GET_GPIO_GROUP(PIN) ((GPIO_TypeDef *) (GPIOA_BASE + 0x40 * ((PIN) & (uint16_t)0xF0)))
#define GET_GPIO_PIN(PIN) (1 << ((PIN) & (uint16_t)0x0F))
#define _PIN(pin) ('A' + (pin >> 4)), (pin & 0x0F)

/* ͨ��ͬ��/�첽�շ���(USART)��� ------------------------------------------------------------------*/
#define UARTS {USART1, USART2}
#define UART_PINS {\
 /* TX   RX   CTS  RTS */	\
	PA9, PA10,PA11,PA12,/* USART1 */	\
	PA2, PA3, PA0, PA1, /* USART2 */	\
}
#define UART_PINS_FULLREMAP {\
 /* TX   RX   CTS  RTS */	\
	PB6, PB7, PA11,PA12,/* USART1 AFIO_MAPR_USART1_REMAP */	\
	PD5, PD6, PD3, PD4, /* USART2 AFIO_MAPR_USART2_REMAP */	\
}

/* ��ʱ����� ------------------------------------------------------------------*/
#define TIMS {TIM1, TIM2, TIM3, TIM4, TIM5, TIM6, TIM7, TIM8}
#define TIM_PINS {\
	PA8, PA9, PA10,PA11,/* TIM1 */	\
	PA0, PA1, PA2, PA3, /* TIM2 */	\
	PA6, PA7, PB0, PB1, /* TIM3 */	\
	PB6, PB7, PB8, PB9, /* TIM4 */	\
	PA0, PA1, PA2, PA3, /* TIM5 */	\
	P0,  P0,  P0,  P0,	/* TIM6 */	\
	P0,  P0,  P0,  P0,	/* TIM7 */	\
	PC6, PC7, PC8, PC9	/* TIM8 */	\
}
#define TIM_PINS_FULLREMAP {\
	PE9, PE11,PE13,PE14,/* TIM1 AFIO_MAPR_TIM1_REMAP_FULLREMAP */	\
	PA15,PB3, PB10,PB11,/* TIM2 AFIO_MAPR_TIM2_REMAP_FULLREMAP */	\
	PC6, PC7, PC8, PC9, /* TIM3 AFIO_MAPR_TIM3_REMAP_FULLREMAP */	\
	PD12,PD13,PD14,PD15,/* TIM4 AFIO_MAPR_TIM4_REMAP */	\
	PA0, PA1, PA2, PA3, /* TIM5 */	\
	P0,  P0,  P0,  P0,	/* TIM6 */	\
	P0,  P0,  P0,  P0,	/* TIM7 */	\
	PC6, PC7, PC8, PC9	/* TIM8 */	\
}

/* ADC(ģ��/����ת����)��� ------------------------------------------------------------------*/
#define DAC_PINS {PA4,PA5}
#define ADC1_PINS {PA0,PA1,PA2,PA3,PA4,PA5,PA6,PA7,PB0,PB1,PC0,PC1,PC2,PC3,PC4,PC5}
#define ADC3_PINS {PA0,PA1,PA2,PA3,PF6,PF7,PF8,PF9,PF10,PF3,PC0,PC1,PC2,PC3,PF4,PF5}

/* I2C������� ------------------------------------------------------------------*/


/* ��������ӿ�(SPI)��� ------------------------------------------------------------------*/
#define SPI_NSS_PINS  {4, 28, 15} // PA4, PB12, PA15
#define SPI_SCLK_PINS {5, 29, 19} // PA5, PB13, PB3
#define SPI_MISO_PINS {6, 30, 20} // PA6, PB14, PB4
#define SPI_MOSI_PINS {7, 31, 21} // PA7, PB15, PB5

/* ��������������(CAN)��� ------------------------------------------------------------------*/
//						  TX    RX
#define CAN_PINS		{PA12, PA11} // AFIO_MAPR_CAN_REMAP_REMAP1
#define CAN_PINS_REMAP2	{PB9,  PB8 } // AFIO_MAPR_CAN_REMAP_REMAP2
#define CAN_PINS_REMAP3	{PD1,  PD0 } // AFIO_MAPR_CAN_REMAP_REMAP3

/* ͨ�ô�������(USB)��� ------------------------------------------------------------------*/

/* SDIO��� ------------------------------------------------------------------*/

#endif
