#include "qk_peripheral.h"

typedef struct qk_i2c_s
{
	bool enable;
} qk_i2c_t;


typedef enum qk_i2c_id_e
{
#if defined(QK_I2C_COUNT) && (QK_I2C_COUNT >= 1)
	QK_I2C_0 = 0,
#endif
#if defined(QK_I2C_COUNT) && (QK_I2C_COUNT >= 2)
	QK_I2C_1 = 0,
#endif
} qk_i2c_id_t;

typedef struct qk_i2c_init_s
{
	bool enable;
	uint8_t location;
} qk_i2c_init_t;

#define QK_I2C_INIT_DEFAULT			\
{									\
	.enable = true,					\
	.location = 0,					\
}									\


extern qk_i2c_t _i2c[QK_I2C_COUNT];

void _qk_i2c_datainit(qk_i2c_id_t id, qk_i2c_init_t *init);
void qk_i2c_init(qk_i2c_id_t id, qk_i2c_init_t *init);
void qk_i2c_start(qk_i2c_id_t id);
void qk_i2c_restart(qk_i2c_id_t id);
void qk_i2c_ack(qk_i2c_id_t id);
void qk_i2c_nack(qk_i2c_id_t id);
void qk_i2c_tx(qk_i2c_id_t id, uint8_t data);
void qk_i2c_rx(qk_i2c_id_t id, uint8_t *data);
void qk_i2c_stop(qk_i2c_id_t id);

//void qk_i2c_set_enabled(qk_i2c_id_t id, bool enabled);
//int qk_i2c_write(qk_i2c_id_t id, uint8_t addr, uint8_t *data, uint16_t len);
//int qk_i2c_read(qk_i2c_id_t id, uint8_t addr, uint8_t *data, uint16_t len);
