
/** \addtogroup QkPower
 * @brief Power Management
 *  @{
 */

#ifndef QK_POWER_H
#define QK_POWER_H

void qk_power_EM1(); // Energy mode 1 (only CPU is inactive)
void qk_power_EM2(); // Energy mode 2 (must wake up from UART RX interrupt)
void qk_power_EM3(); // Energy mode 3 (must wake up from RTC, if available)

#endif

/** @}*/
