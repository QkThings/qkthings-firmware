#include "qk_peripheral.h"

#define _UART_OVS_DEFAULT	USART_CTRL_OVS_X4

static void usart_rx_irq_handler(qk_uart_id_t id)
{
	qk_uart_t *uart = &_uart[id];
	__uart_t *hw = &__uart[id];

	int max = 2;
	while((hw->usart->STATUS & USART_STATUS_RXDATAV) && max--)
	{
		if(uart->databits == QK_UART_DATABITS_8)
		{
			_qk_uart_handle_rx(id , USART_Rx( hw->usart ));
		}
		else // 9 data bits
		{
			uint16_t data = USART_RxExt(hw->usart);
			// LSB first, so data is correctly 'aligned' when casting rx buf
			// to uint16_t*
			_qk_uart_handle_rx(id, (uint8_t)((data) & 0xFF));
			_qk_uart_handle_rx(id, (uint8_t)((data >> 8) & 0xFF));
		}
	}
	USART_IntClear( hw->usart , USART_IF_RXDATAV);
}


#define __USART_IRQ(name, id) void name ## _RX_IRQHandler() { usart_rx_irq_handler(id); }

#if __UART_USE_USART0
__USART_IRQ(USART0, QK_UART_0)
#endif

#if __UART_USE_USART1
__USART_IRQ(USART1, QK_UART_1)
#endif

void qk_uart_init(qk_uart_id_t id, qk_uart_init_t *init)
{
	_qk_uart_datainit(id, init);
	__uart_t *hw = &__uart[id];

	CMU_ClockEnable(hw->clock, true);

	USART_InitAsync_TypeDef usartInit = USART_INITASYNC_DEFAULT;
	usartInit.enable = init->enable ? usartEnable : usartDisable;
	usartInit.baudrate = init->baudrate;
	switch(init->databits)
	{
	case QK_UART_DATABITS_8:	usartInit.databits = USART_FRAME_DATABITS_EIGHT; break;
	case QK_UART_DATABITS_9:	usartInit.databits = USART_FRAME_DATABITS_NINE; break;
	default: ;
	}
	switch(init->stopbits)
	{
	case QK_UART_STOPBITS_0_5:	usartInit.stopbits = USART_FRAME_STOPBITS_HALF; break;
	case QK_UART_STOPBITS_1_0:	usartInit.stopbits = USART_FRAME_STOPBITS_ONE; break;
	case QK_UART_STOPBITS_1_5:	usartInit.stopbits = USART_FRAME_STOPBITS_ONEANDAHALF; break;
	case QK_UART_STOPBITS_2_0:	usartInit.stopbits = USART_FRAME_STOPBITS_TWO; break;
	default: ;
	}
	switch(init->parity)
	{
	case QK_UART_PARITY_NONE: 	usartInit.parity = USART_FRAME_PARITY_NONE; break;
	case QK_UART_PARITY_EVEN: 	usartInit.parity = USART_FRAME_PARITY_EVEN; break;
	case QK_UART_PARITY_ODD: 	usartInit.parity = USART_FRAME_PARITY_ODD; break;
	default: ;
	}
	usartInit.oversampling = _UART_OVS_DEFAULT;

	// Note: this resets USART registers
	USART_InitAsync(hw->usart, &usartInit);

	hw->usart->CMD = USART_CMD_CLEARRX | USART_CMD_CLEARTX;
	hw->usart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC0;
	if(init->rx_invert)
		hw->usart->CTRL |= USART_CTRL_RXINV;
	if(init->tx_invert)
		hw->usart->CTRL |= USART_CTRL_TXINV;

	USART_IntClear(hw->usart, _USART_IF_MASK); // Clear any USART interrupt flags
	NVIC_ClearPendingIRQ(hw->rx_irq);   // Clear pending RX interrupt flag in NVIC
	NVIC_EnableIRQ(hw->rx_irq);
	NVIC_ClearPendingIRQ(hw->tx_irq);   // Clear pending TX interrupt flag in NVIC
	NVIC_DisableIRQ(hw->tx_irq);

	USART_IntEnable(hw->usart, USART_IF_RXDATAV);
}

void qk_uart_set_enabled(qk_uart_id_t id, bool enabled)
{
	__uart_t *hw = &__uart[id];
	USART_Enable_TypeDef enable;
	enable = enabled ? usartEnable : usartDisable;
	USART_Enable(hw->usart, enable);
}

void qk_uart_set_baudrate(qk_uart_id_t id, uint32_t baudrate)
{
	qk_uart_t *uart = &_uart[id];
	__uart_t *hw = &__uart[id];
	USART_BaudrateAsyncSet(hw->usart, 0, baudrate, _UART_OVS_DEFAULT);
	uart->baudrate = baudrate;
}

void qk_uart_write(qk_uart_id_t id, uint8_t *buf, uint32_t count)
{
	qk_uart_t *uart = &_uart[id];
	__uart_t *hw = &__uart[id];
	uint16_t *b16 = (uint16_t*)buf;
	int32_t _count = (int32_t) count;
	while(_count > 0)
	{
		if(uart->databits == QK_UART_DATABITS_8)
		{
			hw->usart->TXDATA = (uint32_t) *buf++;
			//while (!(hw->usart->STATUS & USART_STATUS_TXBL));
			_count -= 1;
		}
		else
		{
			//hw->usart->TXDATAX = (uint32_t)(((uint16_t)buf[0]<<8) + (uint16_t)buf[1]);
			hw->usart->TXDATAX = (uint32_t) *b16++;
			_count -= 2;
		}
		while (!(hw->usart->STATUS & USART_STATUS_TXBL));
		//hw->usart->CMD = USART_CMD_CLEARTX;
	}
}


