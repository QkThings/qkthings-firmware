#ifndef QK_PERIPHERAL_H
#define QK_PERIPHERAL_H

#if QK_PERIPHERAL_CONF
#include "qk_peripheral_conf.h"
#else
//#error "You must provide a qk_peripheral_conf.h file"
// Use everything
#define QK_PERIPHERAL_USE_POWER		1
#define QK_PERIPHERAL_USE_GPIO		1
#define QK_PERIPHERAL_USE_USART		1
#define QK_PERIPHERAL_USE_I2C		1
#define QK_PERIPHERAL_USE_VTIMER	1
#endif

#define QK_PERIPHERAL_PRINTF

#ifdef QK_DEBUG
#define QK_PERIPHERAL_ASSERT
#endif

#include <stdint.h>
#include <stdbool.h>

#include "qk_hwdefs.h"
#include "qk_mcu.h"

#if QK_PERIPHERAL_USE_POWER
#include "qk_power.h"
#endif

#if QK_PERIPHERAL_USE_GPIO
#include "qk_gpio.h"
#endif

#if QK_PERIPHERAL_USE_UART
#include "qk_uart.h"
#endif

#if QK_PERIPHERAL_USE_I2C
#include "qk_i2c.h"
#endif

#if QK_PERIPHERAL_USE_VTIMER
#include "qk_vtimer.h"
#endif

#include "qk_log.h"

void qk_peripheral(void);

#ifdef QK_PERIPHERAL_PRINTF
void __qk_peripheral_print(char c);

int qk_sprintf(char *str, const char *format, ...);
int qk_printf(const char *format, ...);

#define QK_PRINT(...) qk_printf(__VA_ARGS__)

static inline void QK_DUMP_HEX(char *name, uint8_t *b, uint32_t count)
{
	uint32_t i = 0;
	QK_PRINT("DUMP %s [%d bytes]:\n", name, count);
	for(i = 0; i < count; i++)
	{
		QK_PRINT("%02X ", b[i]);
		if(count % 8) QK_PRINT("\n");
	}
}
#else
#define QK_PRINT(...) 	{}

#endif

#define QK_UNUSED(x)	((void)x)

#ifdef QK_DEBUG
void __qk_peripheral_assert(uint16_t line, uint8_t *file);

#define QK_ASSERT(expr)	\
	do{if(expr){} else {__qk_peripheral_assert((uint16_t)__LINE__, (uint8_t*)__FILE__);}} while(0)

#else
#define QK_ASSERT(expr)	{}
#endif


#endif // QK_PERIPHERAL_H
