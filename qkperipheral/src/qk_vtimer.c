#include "qk_peripheral.h"

#define MIN(a, b)    		((a) < (b) ? (a) : (b))
#define MAX(a, b)    		((a) > (b) ? (a) : (b))
#define TIMEDIFF(a,b)		_VTIMER_TIMEDIFF(a, b)
#define CNT_CLOSE_TO_MAX_VALUE	(_VTIMER_CNT_MASK-100UL)
#define MSEC_TO_TICK_RND	((1000U*VTIMER_CLKDIV)/2)
#define MSEC_TO_TICKS(msec)	\
	((((uint64_t)(msec) * (VTIMER_CLKFREQ)) + MSEC_TO_TICK_RND) \
	/(1000U*VTIMER_CLKDIV))

void update_list();
void reschedule();
void execute_callbacks();
void delay_ticks(uint32_t ticks);

_vtimer_list_t _vtimer_list;

void qk_vtimer_init(qk_vtimer_t *timers, uint32_t count)
{
	uint32_t i;
	for(i = 0; i < count; i++)
	{
		timers[i].id = i;
		timers[i].cb = 0;
		timers[i].running = false;
		timers[i].exec_callback = false;
	}

	_vtimer_list.instances = timers;
	_vtimer_list.count = count;
	_vtimer_list.first = 0;
	_vtimer_list.last = 0;
}

int qk_vtimer_create(uint64_t msec, void (*cb)(int, void*), void *arg, qk_vtimer_mode_t mode)
{
	uint32_t i;
	qk_vtimer_t *vt = 0;

	MCU_INTDIS();

	// Find an instance
	for(i = 0; i < _vtimer_list.count; i++)
	{
		if(_vtimer_list.instances[i].running == false)
		{
			vt = &_vtimer_list.instances[i];
			break;
		}
	}

	if(vt == 0)
	{
		MCU_INTEN();
		return -1;
	}

	update_list();

	vt->running = true;
	vt->cb = cb;
	vt->cb_arg = arg;
	vt->mode = mode;
	uint32_t ticks = MSEC_TO_TICKS(msec) + 1;

	vt->ticks = ticks;
	vt->remaining = ticks;

	update_list();
	reschedule();
	execute_callbacks();

	MCU_INTEN();

	return vt->id;
}

void qk_vtimer_destroy(int id)
{
	MCU_INTDIS();
	qk_vtimer_t *vt = &(_vtimer_list.instances[id]);
	vt->running = false;
	MCU_INTEN();
}

void qk_vtimer_destroy_all()
{
	uint32_t i;
	for(i = 0; i < _vtimer_list.count; i++)
	{
		qk_vtimer_destroy(i);
	}
}

void update_list()
{
	_VTIMER_CNT_INTDIS();
	static uint32_t last_update = 0;

	uint32_t cnt = _VTIMER_CNT_GET();
	uint32_t elapsedTicks = TIMEDIFF(cnt, last_update);

	last_update = _VTIMER_CNT_GET();

	uint32_t i;
	for(i = 0; i < _vtimer_list.count; i++)
	{
		qk_vtimer_t *vt = &(_vtimer_list.instances[i]);
		if(vt->running)
		{
			uint32_t decrement = MIN(elapsedTicks, vt->remaining);
			vt->remaining -= decrement;

			if(vt->remaining == 0)
			{
				if(vt->mode == QK_VTIMER_MODE_PERIODIC)
				{
					vt->remaining = vt->ticks;
				}
				else
				{
					vt->running = false;
				}
				vt->exec_callback = true;
			}
			else
			{
				vt->exec_callback = false;
			}
		}
	}
}

void _qk_vtimer_handle_interrupt(void)
{
	update_list();
	reschedule();
	execute_callbacks();
}

void execute_callbacks()
{
	uint32_t i;
	for(i = 0; i < _vtimer_list.count; i++)
	{
		qk_vtimer_t *vt = &(_vtimer_list.instances[i]);
		if(vt->exec_callback == true)
		{
			if(vt->cb != 0)
				vt->cb(vt->id, vt->cb_arg);
			vt->exec_callback = false;
		}
	}
}

void reschedule()
{
	_VTIMER_CNT_INTDIS();

	uint32_t i;
	uint32_t min = 0xFFFFFFFF;
	for(i = 0; i < _vtimer_list.count; i++)
	{
		if(_vtimer_list.instances[i].running)
			min = MIN(_vtimer_list.instances[i].remaining, min);
	}
	if(min != 0xFFFFFFFF)
	{
		uint32_t cnt = _VTIMER_CNT_GET();
		_VTIMER_CNT_INTCLR();
		_VTIMER_CNT_COMPSET((cnt + min) & _VTIMER_CNT_MASK);
		_VTIMER_CNT_INTEN();
	}
}

void qk_delay_ms(uint64_t msec)
{

	uint64_t total_ticks = MSEC_TO_TICKS(msec);
	while(total_ticks > CNT_CLOSE_TO_MAX_VALUE)
	{
		delay_ticks(CNT_CLOSE_TO_MAX_VALUE);
		total_ticks -= CNT_CLOSE_TO_MAX_VALUE;
	}
	delay_ticks(total_ticks);
}

void delay_ticks(uint32_t ticks)
{
	uint32_t start_time;
	volatile uint32_t now;

	if(ticks)
	{
		start_time = _VTIMER_CNT_GET();
		do
		{
			now = _VTIMER_CNT_GET();
		}
		while( TIMEDIFF(now, start_time) < ticks);
	}
}
