#include "qk_peripheral.h"

void qk_power_EM1()
{
	EMU_EnterEM1();
}

void qk_power_EM2()
{
	EMU_EnterEM1();
}

void qk_power_EM3()
{
	EMU_EnterEM2(true);
}
