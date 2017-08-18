#ifndef QK_GPIO_H
#define QK_GPIO_H

typedef uint32_t qk_gpio_pin_t;

typedef enum qk_gpio_port_e
{
#ifdef _GPIO_HAS_PORT_A
	QK_GPIO_PORT_A = 0,
#endif
#ifdef _GPIO_HAS_PORT_B
	QK_GPIO_PORT_B = 1,
#endif
#ifdef _GPIO_HAS_PORT_C
	QK_GPIO_PORT_C = 2,
#endif
#ifdef _GPIO_HAS_PORT_D
	QK_GPIO_PORT_D = 3,
#endif
#ifdef _GPIO_HAS_PORT_E
	QK_GPIO_PORT_E = 4,
#endif
#ifdef _GPIO_HAS_PORT_F
	QK_GPIO_PORT_F = 5,
#endif
#ifdef _GPIO_HAS_PORT_G
	QK_GPIO_PORT_G = 6,
#endif
#ifdef _GPIO_HAS_PORT_H
	QK_GPIO_PORT_H = 7,
#endif
} qk_gpio_port_t;

typedef enum qk_gpio_mode_e
{
	QK_GPIO_MODE_ANALOG,
	QK_GPIO_MODE_OUTPUT,
	QK_GPIO_MODE_INPUT,
	QK_GPIO_MODE_INPUT_PULLUP,
	QK_GPIO_MODE_INPUT_PULLDOWN,
	QK_GPIO_MODE_OUTPUT_OPENDRAIN,
	_QK_GPIO_MODE_COUNT
} qk_gpio_mode_t;

typedef enum qk_gpio_event_e
{
	QK_GPIO_EVENT_TOGGLE,
	QK_GPIO_EVENT_RISE,
	QK_GPIO_EVENT_FALL,
} qk_gpio_event_t;

typedef void (*qk_gpio_cb_t)(bool state);

typedef enum qk_gpio_state_e
{
	LOW = 0,
	HIGH = 1
} qk_gpio_state_t;

void _qk_gpio_startup();
void qk_gpio_pin_register_callback(qk_gpio_port_t port, qk_gpio_pin_t pin, qk_gpio_event_t evt, qk_gpio_cb_t cb);
void qk_gpio_pin_config(qk_gpio_port_t port, qk_gpio_pin_t pin, qk_gpio_mode_t mode);
void qk_gpio_pin_set(qk_gpio_port_t port, qk_gpio_pin_t pin, qk_gpio_state_t state);
qk_gpio_state_t qk_gpio_pin_get(qk_gpio_port_t port, qk_gpio_pin_t pin);
void qk_gpio_port_set(qk_gpio_port_t port, uint32_t value);
uint32_t qk_gpio_port_get(qk_gpio_port_t port);
void qk_gpio_pin_toggle(qk_gpio_port_t port, qk_gpio_pin_t pin);

#endif

