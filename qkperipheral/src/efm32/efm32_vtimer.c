#include "qk_peripheral.h"

void RTC_IRQHandler(void)
{
	uint32_t flags;

	INT_Disable();

	flags = RTC_IntGet();

	if ( flags & RTC_IF_COMP0 )
	{
		RTC_IntDisable(RTC_IF_COMP0);
		_qk_vtimer_handle_interrupt();
	}

	INT_Enable();
}

void _qk_vtimer_startup()
{
	// Ensure LE modules are clocked.
	CMU_ClockEnable( cmuClock_CORELE, true );

	// Enable LFACLK in CMU (will also enable oscillator if not enabled).
	CMU_ClockSelectSet( cmuClock_LFA, cmuSelect_LFRCO );

	// Set clock divider.
	CMU_ClockDivSet( cmuClock_RTC, cmuClkDiv_4 );

	// Enable RTC module clock.
	CMU_ClockEnable( cmuClock_RTC, true );

	// Initialize RTC.
	RTC_Init_TypeDef initRTC =
	{
	  true,  // Start counting when init completed.
	  false, // Disable updating RTC during debug halt.
	  false  // Count until max. to wrap around.
	};
	RTC_Init( &initRTC );

	// Disable RTC/RTCC interrupt generation.
	RTC_IntDisable( _RTC_IF_MASK );
	RTC_IntClear( _RTC_IF_MASK );

	RTC_CounterReset();

	// Clear and then enable RTC interrupts in NVIC.
	NVIC_ClearPendingIRQ(RTC_IRQn);
	NVIC_EnableIRQ(RTC_IRQn);
}
