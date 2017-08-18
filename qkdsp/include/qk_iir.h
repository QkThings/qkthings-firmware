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

 #ifndef QK_IIR_H
 #define QK_IIR_H

/** \addtogroup QkIIR
 * @brief Infinite Impulse Response
 *  @{
 */

/**
 * Infinite Impulse Response (IIR) filter
 */
typedef struct
{
  uint16_t N;         // Filter order
  int16_t gain;       // Numerator coeffs gain (when scaled, otherwise must be 1)
  const int16_t *b;   // Numerator coefficients (N+1)
  const int16_t *a;   // Denominator coefficients (N+1)
  int16_t *x;         // Input samples buffer (N)
  int16_t *y;         // Output samples buffer (N)
  uint8_t format;     // Fixed point format
  uint16_t _head;
} qk_iir;

/**
 * @brief .
 */
void qk_iir_setup(qk_iir *f, const int16_t *b, const int16_t *a, int16_t *x, int16_t *y);

/**
 * @brief .
 */
void qk_iir_init(qk_iir *f, int16_t initial);

/**
 * @brief .
 */
void qk_iir_set_gain(qk_iir *f, int16_t gain);

/**
 * @brief .
 */
void qk_iir_set_format(qk_iir *f, uint8_t format);

/**
 * @brief .
 */
int16_t qk_iir_filter(qk_iir *f, int16_t new_sample);

/** @}*/

#endif
