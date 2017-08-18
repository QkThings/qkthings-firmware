#include "qk_peripheral.h"

qk_i2c_t _i2c[QK_I2C_COUNT];

void _qk_i2c_datainit(qk_i2c_id_t id, qk_i2c_init_t *init)
{
	qk_i2c_t *i2c = &_i2c[id];
	i2c->enable = init->enable;
}

