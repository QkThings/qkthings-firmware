#ifndef QK_UART_H_
#define QK_UART_H_

typedef enum qk_uart_id_e
{
#if defined(QK_UART_COUNT) && (QK_UART_COUNT >= 1)
	QK_UART_0 = 0,
#endif
#if defined(QK_UART_COUNT) && (QK_UART_COUNT >= 2)
	QK_UART_1 = 1,
#endif
#if defined(QK_UART_COUNT) && (QK_UART_COUNT >= 3)
	QK_UART_2 = 2,
#endif
#if defined(QK_UART_COUNT) && (QK_UART_COUNT >= 4)
	QK_UART_3 = 3,
#endif
#if defined(QK_UART_COUNT) && (QK_UART_COUNT >= 5)
	QK_UART_4 = 4,
#endif
#if defined(QK_UART_COUNT) && (QK_UART_COUNT >= 6)
	QK_UART_5 = 5,
#endif
} qk_uart_id_t;

typedef enum qk_uart_parity_e
{
	QK_UART_PARITY_NONE,
	QK_UART_PARITY_EVEN,
	QK_UART_PARITY_ODD,
} qk_uart_parity_t;

typedef enum qk_uart_stopbits_s
{
	QK_UART_STOPBITS_0_5,
	QK_UART_STOPBITS_1_0,
	QK_UART_STOPBITS_1_5,
	QK_UART_STOPBITS_2_0,
} qk_uart_stopbits_t;

typedef enum qk_uart_databits_s
{
	QK_UART_DATABITS_8,
#ifdef QK_UART_SUPPORT_DATABITS_9
	QK_UART_DATABITS_9,
#endif
} qk_uart_databits_t;

typedef struct qk_uart_s
{
	uint8_t *rxbuf;
	uint32_t rxbuf_len;
	uint32_t count;
	uint32_t wr_i;
	uint32_t rd_i;
	uint32_t baudrate;
	qk_uart_databits_t databits;
	bool overflow;
} qk_uart_t;

typedef struct qk_uart_init_s
{
	bool enable;
	uint32_t baudrate;
	uint8_t *rxbuf;
	uint32_t rxbuf_len;
	qk_uart_databits_t databits;
	qk_uart_stopbits_t stopbits;
	qk_uart_parity_t parity;
#ifdef QK_UART_SUPPORT_TXINV
	bool tx_invert;
#endif
#ifdef QK_UART_SUPPORT_RXINV
	bool rx_invert;
#endif
} qk_uart_init_t;

#ifdef QK_UART_SUPPORT_TXINV
#define __UART_INIT_TXINV	.tx_invert = false,
#else
#define __UART_INIT_TXINV
#endif

#ifdef QK_UART_SUPPORT_RXINV
#define __UART_INIT_RXINV	.rx_invert = false,
#else
#define __UART_INIT_RXINV
#endif

#define QK_UART_INIT_DEFAULT 			\
{ 										\
	.enable = false,					\
	.baudrate = 38400,					\
	.rxbuf = 0,							\
	.rxbuf_len = 0,						\
	.databits = QK_UART_DATABITS_8,		\
	.parity = QK_UART_PARITY_NONE,		\
	.stopbits = QK_UART_STOPBITS_1_0,	\
	__UART_INIT_TXINV					\
	__UART_INIT_RXINV 					\
}

extern qk_uart_t _uart[QK_UART_COUNT];

void _qk_uart_datainit(qk_uart_id_t id, qk_uart_init_t *init);
void qk_uart_init(qk_uart_id_t id, qk_uart_init_t *init);
void qk_uart_set_enabled(qk_uart_id_t id, bool enabled);
void qk_uart_set_baudrate(qk_uart_id_t id, uint32_t baudrate);
void qk_uart_clear(qk_uart_id_t id);
uint32_t qk_uart_bytes_available(qk_uart_id_t id);
uint32_t qk_uart_read(qk_uart_id_t id, uint8_t *buf, uint32_t max);
void qk_uart_write(qk_uart_id_t id, uint8_t *buf, uint32_t count);

void _qk_uart_handle_rx(qk_uart_id_t id, uint8_t data);

#endif /* QK_UART_H_ */
