#include "qk_peripheral.h"
#include <string.h>

static uint32_t _pins_state[_QK_GPIO_PORT_COUNT];
static void (*_callback[_QK_GPIO_PORT_COUNT][16])(bool state);

static uint32_t update_pins_state(uint8_t port, uint32_t pins_mask)
{
	uint32_t tmp = GPIO_PortInGet(port);
	uint32_t changed = (tmp ^ _pins_state[port]) & pins_mask;
	_pins_state[port] &= ~pins_mask;
	_pins_state[port] |= (tmp & pins_mask);
	return changed;
}

static void interrupt_exec_callbacks(uint8_t iflags)
{
	uint8_t port;
	for(port = 0; port < _QK_GPIO_PORT_COUNT; port++)
	{
		uint32_t changed = update_pins_state(port, iflags);
		uint8_t pin = 0;
		while(changed > 0)
		{
			if(changed & 0x01)
			{
				if(_callback[port][pin] != 0)
				{
					bool state = (_pins_state[port] & (1<<pin)) != 0;
					_callback[port][pin](state);
				}
			}
			pin++;
			changed >>= 1;
		}
	}
}

void GPIO_ODD_IRQHandler()
{
	uint32_t odd_flags;

	/* Get all odd interrupts. */
	odd_flags = GPIO_IntGetEnabled() & 0x0000AAAA;
	interrupt_exec_callbacks(odd_flags);
	/* Clean only odd interrupts. */
	GPIO_IntClear(odd_flags);
}
void GPIO_EVEN_IRQHandler()
{
	uint32_t even_flags;
	even_flags = GPIO_IntGetEnabled() & 0x00005555;
	interrupt_exec_callbacks(even_flags);
	GPIO_IntClear(GPIO_IntGet());
}

void _qk_gpio_startup()
{
	CMU_ClockEnable(cmuClock_GPIO, true);

	memset(_pins_state, 0, sizeof(_pins_state));
	memset(_callback, 0, sizeof(_callback));

	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);
	NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);
}



void qk_gpio_pin_register_callback(qk_gpio_port_t port, qk_gpio_pin_t pin, qk_gpio_event_t evt, qk_gpio_cb_t cb)
{
	bool riseEdge = evt == QK_GPIO_EVENT_RISE || evt == QK_GPIO_EVENT_TOGGLE;
	bool fallEdge = evt == QK_GPIO_EVENT_FALL || evt == QK_GPIO_EVENT_TOGGLE;
	_callback[port][pin] = cb;
	GPIO_IntConfig((GPIO_Port_TypeDef) port, pin, riseEdge, fallEdge, true);
}

void qk_gpio_pin_config(qk_gpio_port_t port, qk_gpio_pin_t pin, qk_gpio_mode_t mode)
{
	uint32_t out = 0;
	__gpio_mode_t gpioMode = __gpio_mode[mode];
	if(mode == QK_GPIO_MODE_INPUT || mode == QK_GPIO_MODE_INPUT_PULLUP || mode == QK_GPIO_MODE_OUTPUT_OPENDRAIN)
	{
		out = 1;
	}
	GPIO_PinModeSet(port, pin, gpioMode, out);
	update_pins_state(port, (1<<pin));
}

void qk_gpio_pin_set(qk_gpio_port_t port, qk_gpio_pin_t pin, qk_gpio_state_t state)
{
	if(state)
	{
		GPIO_PinOutSet((GPIO_Port_TypeDef) port, (unsigned int) pin);
	}
	else
	{
		GPIO_PinOutClear((GPIO_Port_TypeDef) port, (unsigned int) pin);
	}
}
qk_gpio_state_t qk_gpio_pin_get(qk_gpio_port_t port, qk_gpio_pin_t pin)
{
	return GPIO_PinInGet((GPIO_Port_TypeDef) port, (unsigned int) pin);
}
void qk_gpio_port_set(qk_gpio_port_t port, uint32_t value)
{
	GPIO_PortOutSet((GPIO_Port_TypeDef) port, value);
}
uint32_t qk_gpio_port_get(qk_gpio_port_t port)
{
	return (uint32_t) GPIO_PortOutGet((GPIO_Port_TypeDef) port);
}
void qk_gpio_pin_toggle(qk_gpio_port_t port, qk_gpio_pin_t pin)
{
	GPIO_PinOutToggle((GPIO_Port_TypeDef) port, (unsigned int) pin);
}

void qk_gpio_port_toggle(qk_gpio_port_t port, uint32_t pins)
{
	GPIO_PortOutToggle((GPIO_Port_TypeDef) port, pins);
}
