#include "qk_peripheral.h"


__gpio_mode_t __gpio_mode[_QK_GPIO_MODE_COUNT] =
{
		gpioModeDisabled,
		gpioModePushPull,
		gpioModeInput,
		gpioModeInputPull,
		gpioModeInputPull,
		gpioModeWiredAnd,
};


#if  __UART_USE_USART0
#define __UART_0 	{.type=__USART, .usart=USART0, .clock=cmuClock_USART0, .rx_irq=USART0_RX_IRQn, .tx_irq=USART0_TX_IRQn},
#else
#define __UART_0
#endif

#if  __UART_USE_USART0
#define __UART_1 	{.type=__USART, .usart=USART1, .clock=cmuClock_USART1, .rx_irq=USART1_RX_IRQn, .tx_irq=USART1_TX_IRQn},
#else
#define __UART_1
#endif

__uart_t __uart[QK_UART_COUNT] =
{
		__UART_0
		__UART_1
};

#if __I2C_USE_I2C0
#define	__I2C_0		{.i2c=I2C0, .clock=cmuClock_I2C0, .irq=I2C0_IRQn},
#else
#define __I2C_0
#endif

__i2c_t __i2c[QK_I2C_COUNT] =
{
		__I2C_0
};

#if defined(DEBUG_EFM_USER)
void assertEFM(const char *file, int line)
{
	QK_LOG_FATAL("%s:%d\n", file, line);
}

#endif
