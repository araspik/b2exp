/**
 * Defines the LUT table.
 *
 * ---
 *
 * Copyright (C) 2019  ARaspiK
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
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef B2EXP_PRIVATE_LUT_H
#define B2EXP_PRIVATE_LUT_H

#include <stdint.h>

/**
 * The LUT.
 *
 * The LUT consists of two consecutive tables, each containing 64 elements of
 * 63-bit mantissas [1]. The first table contains iterative square roots of 2,
 * and the second table contains reciprocals of the same values.
 */
const uint64_t b2exp_LUT[128];

#endif
