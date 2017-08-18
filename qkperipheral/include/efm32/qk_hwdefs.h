#ifndef QK_HWDEFS_H
#define QK_HWDEFS_H

#include "em_chip.h"
#include "em_emu.h"
#include "em_cmu.h"
#include "em_int.h"
#include "em_gpio.h"
#include "em_rtc.h"
#include "em_usart.h"
#include "em_timer.h"
#include "em_i2c.h"

// MCU
#define	MCU_INTEN()					INT_Enable()
#define MCU_INTDIS()				INT_Disable()

// GPIO
#define _QK_GPIO_PORT_COUNT			6
#define _GPIO_HAS_PORT_A
#define _GPIO_HAS_PORT_B
#define _GPIO_HAS_PORT_C
#define _GPIO_HAS_PORT_D
#define _GPIO_HAS_PORT_E
#define _GPIO_HAS_PORT_F

typedef uint32_t __gpio_mode_t;
extern __gpio_mode_t __gpio_mode[];

// UART
#define QK_UART_COUNT 				(USART_COUNT + LEUART_COUNT)
#define QK_UART_SUPPORT_DATABITS_9	1
#define QK_UART_SUPPORT_TXINV		1
#define QK_UART_SUPPORT_RXINV		1
#define __UART_USE_USART0			1
#define __UART_USE_USART1			1

typedef enum { __USART, __LEUART } __uart_type_t;
typedef struct {
	__uart_type_t type;
	USART_TypeDef *usart;
	CMU_Clock_TypeDef clock;
	IRQn_Type rx_irq;
	IRQn_Type tx_irq;
} __uart_t;
extern __uart_t __uart[];

// I2C
#define QK_I2C_COUNT				(I2C_COUNT)
#define __I2C_USE_I2C0				1

typedef struct {
	I2C_TypeDef *i2c;
	CMU_Clock_TypeDef clock;
	IRQn_Type irq;
} __i2c_t;
extern __i2c_t __i2c[];

// VTIMER
#define VTIMER_CLKFREQ				(32768U)
#define VTIMER_CLKDIV				(4)
#define _VTIMER_TIMEDIFF(a,b)		(((a<<8)-(b<<8)) >> 8)
#define _VTIMER_CNT_MASK			(0x00FFFFFF)
#define _VTIMER_CNT_GET()			RTC_CounterGet()
#define _VTIMER_CNT_INTCLR()		RTC_IntClear(RTC_IF_COMP0)
#define _VTIMER_CNT_INTEN()			RTC_IntEnable(RTC_IF_COMP0)
#define _VTIMER_CNT_INTDIS()		RTC_IntDisable(RTC_IF_COMP0)
#define _VTIMER_CNT_COMPSET(v)		RTC_CompareSet(0, (v))


#endif /* QK_HWDEFS_P_H */
