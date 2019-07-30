/**
 * A declaration of the benchmarking implementation.
 *
 * This is used by the benchmark interface code to access the benchmarking
 * implementation.
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

#ifndef B2EXP_PRIVATE_BENCHMARK
#define B2EXP_PRIVATE_BENCHMARK

#include <stdint.h>

/**
 * Benchmarks the given two function pointers across the given range of inputs
 * with the given step.
 *
 * The timings (in nanoseconds) for both functions is returned, and the last
 * input (exclusive) used is returned.
 */
double bench_f64(
    double (*a)(double),
    double (*b)(double),
    double first,
    double step,
    uint64_t times,
    uint64_t* time_a_sec,
    uint64_t* time_a_ns,
    uint64_t* time_b_sec,
    uint64_t* time_b_ns
);

#endif
