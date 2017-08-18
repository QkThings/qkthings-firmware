#include "qk_peripheral.h"

qk_uart_t _uart[QK_UART_COUNT];

void _qk_uart_datainit(qk_uart_id_t id, qk_uart_init_t *init)
{
	qk_uart_t *uart = &_uart[id];
	uart->count = 0;
	uart->rd_i = 0;
	uart->wr_i = 0;
	uart->baudrate = init->baudrate;
	uart->databits = init->databits;
	uart->rxbuf = init->rxbuf;
	uart->rxbuf_len = init->rxbuf_len;
}

void qk_uart_clear(qk_uart_id_t id)
{
	qk_uart_t *uart = &_uart[id];
	uart->rd_i = uart->wr_i = uart->count = 0;
	uart->overflow = false;
}

uint32_t qk_uart_bytes_available(qk_uart_id_t id)
{
	qk_uart_t *uart = &_uart[id];
	uint32_t count = 0;
	MCU_INTDIS();
	count = uart->count;
	MCU_INTEN();
	return count;
}
uint32_t qk_uart_read(qk_uart_id_t id, uint8_t *buf, uint32_t max)
{
	qk_uart_t *uart = &_uart[id];
	uint32_t i;
	uint32_t bytesToRead = max;

	MCU_INTDIS();

	uint32_t bytesAvailable = qk_uart_bytes_available(id);

	bytesToRead = bytesToRead > bytesAvailable ? bytesAvailable : bytesToRead;

	for(i = 0; i < bytesToRead; i++)
	{
		buf[i] = uart->rxbuf[uart->rd_i];
		uart->rd_i = uart->rd_i < uart->rxbuf_len - 1 ? uart->rd_i + 1 : 0;
	}
	uart->count -= bytesToRead;

	MCU_INTEN();

	return bytesToRead;
}

void _qk_uart_handle_rx(qk_uart_id_t id, uint8_t data)
{
	qk_uart_t *uart = &_uart[id];

	if(uart->count < uart->rxbuf_len)
	{
		uart->rxbuf[uart->wr_i] = data;
		uart->wr_i = uart->wr_i < uart->rxbuf_len - 1 ? uart->wr_i + 1 : 0;
		uart->count += 1;
	}
	else
	{
		uart->overflow = true;
	}
}
