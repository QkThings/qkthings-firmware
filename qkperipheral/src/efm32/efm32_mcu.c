#include "qk_peripheral.h"

void _qk_mcu_startup()
{
	CHIP_Init();
	CMU_HFRCOBandSet(cmuHFRCOBand_28MHz);
	CMU_ClockEnable(cmuClock_HFPER, true);
}
