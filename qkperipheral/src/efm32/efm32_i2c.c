#include "qk_peripheral.h"

volatile I2C_TransferReturn_TypeDef i2c_status;


//void I2C0_IRQHandler(void)
//{
//  /* Just run the I2C_Transfer function that checks interrupts flags and returns */
//  /* the appropriate status */
//	i2c_status = I2C_Transfer(I2C0);
//}

void qk_i2c_init(qk_i2c_id_t id, qk_i2c_init_t *init)
{
	_qk_i2c_datainit(id, init);
	__i2c_t *hw = &__i2c[id];

	CMU_ClockEnable(hw->clock, true);

	I2C_Init_TypeDef i2c_init = I2C_INIT_DEFAULT;
	i2c_init.enable = init->enable;

	hw->i2c->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN | (init->location << _I2C_ROUTE_LOCATION_SHIFT);
	I2C_Init(hw->i2c, &i2c_init);

//	NVIC_ClearPendingIRQ(hw->irq);
//	NVIC_EnableIRQ(hw->irq);
}


void qk_i2c_start(qk_i2c_id_t id)
{
	__i2c_t *hw = &__i2c[id];
	if (hw->i2c->STATE & I2C_STATE_BUSY)
	{
		hw->i2c->CMD = I2C_CMD_ABORT;
	}

	/* Ensure buffers are empty */
	hw->i2c->CMD = I2C_CMD_CLEARPC | I2C_CMD_CLEARTX;
	if (hw->i2c->IF & I2C_IF_RXDATAV)
	{
		(void)hw->i2c->RXDATA;
	}

	/* Clear all pending interrupts prior to starting transfer. */
	hw->i2c->IFC = _I2C_IFC_MASK;
	hw->i2c->IEN = I2C_IF_NACK | I2C_IF_ACK | I2C_IF_RXDATAV;

	hw->i2c->CMD = I2C_CMD_START;
}

void qk_i2c_restart(qk_i2c_id_t id)
{
	__i2c_t *hw = &__i2c[id];
	hw->i2c->CMD = I2C_CMD_START;
}

void qk_i2c_wait_ack(qk_i2c_id_t id)
{
	__i2c_t *hw = &__i2c[id];
	while((hw->i2c->IF & I2C_IF_ACK) == 0);
	hw->i2c->IFC = I2C_IFC_ACK;
}

void qk_i2c_ack(qk_i2c_id_t id)
{
	__i2c_t *hw = &__i2c[id];
	hw->i2c->CMD = I2C_CMD_ACK;
}

void qk_i2c_nack(qk_i2c_id_t id)
{
	__i2c_t *hw = &__i2c[id];
	hw->i2c->CMD = I2C_CMD_NACK;
}

void qk_i2c_tx(qk_i2c_id_t id, uint8_t data)
{
	__i2c_t *hw = &__i2c[id];
	hw->i2c->TXDATA = (uint32_t) data;
	//while((hw->i2c->IF & I2C_IF_TXC) == 0);
	qk_i2c_wait_ack(id);
}

void qk_i2c_rx(qk_i2c_id_t id, uint8_t *data)
{
	__i2c_t *hw = &__i2c[id];
	while((hw->i2c->IF & I2C_IF_RXDATAV) == 0);
	*data = (uint8_t) hw->i2c->RXDATA;
}

void qk_i2c_stop(qk_i2c_id_t id)
{
	__i2c_t *hw = &__i2c[id];
	hw->i2c->CMD = I2C_CMD_STOP;
}
