#ifndef QK_VTIMER_H
#define QK_VTIMER_H

typedef enum
{
	QK_VTIMER_MODE_SINGLE,
	QK_VTIMER_MODE_PERIODIC
} qk_vtimer_mode_t;

typedef struct
{
	uint32_t id;
	uint64_t ticks;
	uint64_t remaining;
	qk_vtimer_mode_t mode;
	void *cb_arg;
	void (*cb)(int, void*);
	bool exec_callback;
	bool running;
} qk_vtimer_t;

typedef struct
{
	qk_vtimer_t *first;
	qk_vtimer_t *last;
	qk_vtimer_t *instances;
	uint32_t count;
} _vtimer_list_t;

extern _vtimer_list_t _vtimer_list;

void _qk_vtimer_startup(void);
void _qk_vtimer_handle_interrupt(void);

void qk_vtimer_init(qk_vtimer_t *timers, uint32_t count);
int qk_vtimer_create(uint64_t msec, void (*cb)(int, void*), void *arg, qk_vtimer_mode_t mode);
void qk_vtimer_destroy(int id);
void qk_vtimer_destroy_all(void);

void qk_delay_ms(uint64_t msec);


#endif /* QK_VTIMER_H */
