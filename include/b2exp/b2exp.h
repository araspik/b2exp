/**
 * b2exp header
 *
 * Defines the b2exp function.
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

#ifndef B2EXP_H
#define B2EXP_H

/**
 * Raises 2 to the power of `x`.
 *
 * The precision of the result is 1/2 ulp (as exact as possible).
 */
double b2exp(double x);

#endif
