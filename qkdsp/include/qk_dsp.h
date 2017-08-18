/*
 * QkThings LICENSE
 * The open source framework and modular platform for smart devices.
 * Copyright (C) 2014 <http://qkthings.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef QK_DSP_H
#define QK_DSP_H

/**
@mainpage QkDSP

Many sensor based applications require the use of DSP algorithms and in particular digital filters. They may be used for noise reduction but also to extract meaningful information from digital signals. Some implementations may be complex and require considerable computational power and memory. Hence, small and low power embedded systems presents some challenges due to their lack of processing power and scarce memory. As such, a library that makes digital filters easy to use and implement at the embedded level was implemented.

*/

#include <stdint.h>

#include "qk_avg.h"
#include "qk_fir.h"
#include "qk_iir.h"


#define QK_DSP_MULSS(a,b) ((a)*(b))
//#define QK_DSP_MULSS(a,b) __builtin_mulss(a,b) // hack for Microchip microcontrollers

#endif
