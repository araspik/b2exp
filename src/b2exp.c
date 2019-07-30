/**
 * Raises 2 to the power of `x` with 1/2 ulp (exact) precision.
 *
 * Based on the LUT algorithm by Claude Baumann (2004) at
 * https://www.convict.lu/Jeunes/ultimate_stuff/exp_ln_2.htm.
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

#include <lut.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// Raw double -> uint64_t
static uint64_t f642raw(double x) {
    uint64_t res;
    memcpy(&res, &x, 8);
    return res;
}

// Raw uint64_t -> double
static double raw2f64(uint64_t x) {
    double res;
    memcpy(&res, &x, 8);
    return res;
}

// Round down by n bits.
//
// In x86, it is much better to perform a right-shift first, as it sets the
// carry flag to the last bit shifted away. The carry flag can then be added
// back to perform rounding.
static uint64_t rnddn(uint64_t x, unsigned int n) {
    return (x >> n) + !!(x & (1UL << (n-1)));
}

// Round down 128-bit by n bits.
static __uint128_t rnddnl(__uint128_t x, unsigned int n) {
    return (x >> n) + !!(x & (((__uint128_t) 1) << (n-1)));
}

double b2exp(double x) {
    // Get raw bits, to extract mantissa and exponent.
    const uint64_t raw = f642raw(x);

    // The sign of x as -1 (negative) or 0 (positive).
    int64_t sign = !(raw & (1UL << 63)) - 1;

    // The exponent of x, without the sign bit, and offset by 52.
    // This 0 (the exponent being -52) is the minimum valid value for a non-1
    // output.
    int64_t exp = ((raw & ~(1UL << 63)) >> 52) - 1023 + 52;

    // A magical parting between the whole and fractional part of x.
    // The top 64 bits contain the whole number part and mantissa parts in the
    // IEEE 754 format (the sign bit is 0).
    __uint128_t man = (((__uint128_t)(uint64_t)(raw << 12)) | (((__uint128_t) 1) << 64)) << exp;

    // When the exponent is less than -52 (here 0), it is either 1 or within
    // 2^-52 of it.
    if (exp <= 0) {
        // 1.0 in IEEE 754 format.
        uint64_t res = 0x3FF0000000000000;
        if (exp == 0)
            // This becomes res+1 for positive x and res-1 for negative x.
            return raw2f64(res + 1 + (sign << 1));
        return raw2f64(res);
    }

    // When the exponent is more than or equal to 10 (here 62), the result is
    // infinity (+x) or 0 (-x).
    if (exp >= 52+10)
        return raw2f64(0x7FF0000000000000 & ~sign);

    // The exponent of the result.
    // The XOR is used to negate and subtract 1 if negative x and have no affect
    // on positive x.
    exp = ((int64_t)(man >> 64) ^ sign) + (1023UL << 52);

    // The LUT subtable used in calculating the mantissa of the result.
    const uint64_t* table = &b2exp_LUT[64 & sign];

    // A 1.0 in 63-bit mantissa format.
    const uint64_t SIGN = 1UL << 63;

    // Two simultaneous products of iterative square roots (from the LUT)
    // selected based on the fractional part of x, in 63-bit mantissa format.
    //
    // Their product is the mantissa of the result.
    __uint128_t products[2] = {SIGN, SIGN};

    // The fractional part of the input as a 64-bit integer.
    uint64_t mantissa = (uint64_t) ((man << 12) >> 64);

    // The multiplier loop.
    //
    // It stops when mantissa is zero (no more bits to account for).
    // It is guaranteed that the mantissa is never zero at the beginning.
    while (true) {
        products[0] *= (mantissa & (1UL << 63)) ? table[0] : SIGN;
        products[1] *= (mantissa & (1UL << 62)) ? table[1] : SIGN;
        mantissa <<= 2;
        if (mantissa == 0) break;
        table = &table[2];
        products[0] = rnddnl(products[0], 63);
        products[1] = rnddnl(products[1], 63);
    }

    // The product of the top 64 bits (most significant bit is 0 of both), then
    // rounding to 52 significant bits (3 most significant bits of the product
    // are 0), then ORing in the exponent.
    return raw2f64(
        (rnddn(((products[0] >> 64) * (products[1] >> 64)) >> 64, 8+sign)
          & ~(1UL << 52))
      | exp);
}
