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

 #ifndef QK_FIR_H
 #define QK_FIR_H

/** \addtogroup QkFIR
 * @brief Finite Impulse Response
 *  @{
 */

/**
 * Finite Impulse Response (FIR) filter
 */
typedef struct qk_fir
{
  uint16_t N;
  const int16_t *b; // Coefficients (N+1)
  int16_t *x;       // Input sampels buffer (N)
  uint16_t _head;
} qk_fir;

/**
 * @brief .
 */
void qk_fir_setup(qk_fir *f, int N, const int16_t *b, int16_t *x);

/**
 * @brief .
 */
void qk_fir_init(qk_fir *f, int16_t initial);

/**
 * @brief .
 */
int16_t qk_fir_filter(qk_fir *f, int16_t new_sample);

/** @}*/

#endif
