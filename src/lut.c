/**
 * b2exp:lut.c: LUT table of constants
 *
 * The LUT consists of two consecutive 64-element tables of 64-bit constants.
 *
 * The constants are formatted as 63-bit mantissas; See the algorithm
 * explanation for details about the format.
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

#include <stdint.h>

const uint64_t b2exp_LUT[128] = {
    0xB504F333F9DE6484,
    0x9837F0518DB8A96F,
    0x8B95C1E3EA8BD6E7,
    0x85AAC367CC487B15,
    0x82CD8698AC2BA1D7,
    0x8164D1F3BC030773,
    0x80B1ED4FD999AB6C,
    0x8058D7D2D5E5F6B1,
    0x802C6436D0E04F51,
    0x8016302F17467628,
    0x800B179C82028FD1,
    0x80058BAF7FEE3B5D,
    0x8002C5D00FDCFCB7,
    0x800162E61BED4A49,
    0x8000B17292F702A4,
    0x800058B92ABBAE02,
    0x80002C5C8DADE4D7,
    0x8000162E44EAF636,
    0x80000B1721FA7C19,
    0x8000058B90DE7E4D,
    0x800002C5C8678F37,
    0x80000162E431DBA0,
    0x800000B1721872D1,
    0x80000058B90C1AA9,
    0x8000002C5C8605A4,
    0x800000162E4300E6,
    0x8000000B17217FF8,
    0x800000058B90BFDD,
    0x80000002C5C85FE7,
    0x8000000162E42FF2,
    0x80000000B17217F8,
    0x8000000058B90BFC,
    0x800000002C5C85FE,
    0x80000000162E42FF,
    0x800000000B17217F,
    0x80000000058B90C0,
    0x8000000002C5C860,
    0x800000000162E430,
    0x8000000000B17218,
    0x800000000058B90C,
    0x80000000002C5C86,
    0x8000000000162E43,
    0x80000000000B1721,
    0x8000000000058B91,
    0x800000000002C5C8,
    0x80000000000162E4,
    0x800000000000B172,
    0x80000000000058B9,
    0x8000000000002C5D,
    0x800000000000162E,
    0x8000000000000B17,
    0x800000000000058C,
    0x80000000000002C6,
    0x8000000000000163,
    0x80000000000000B1,
    0x8000000000000059,
    0x800000000000002C,
    0x8000000000000016,
    0x800000000000000B,
    0x8000000000000006,
    0x8000000000000003,
    0x8000000000000001,
    0x8000000000000001,
    0x8000000000000000,
    0x5A827999FCEF3242,
    0x6BA27E656B4EB57A,
    0x75606373EE921C97,
    0x7A92BE8A92436616,
    0x7D41D96DB915019D,
    0x7E9F06067A4360BA,
    0x7F4F08AE3DC7C426,
    0x7FA765ACA88F6453,
    0x7FD3AB290E46D769,
    0x7FE9D3A8E07BF086,
    0x7FF4E9597BED93AB,
    0x7FFA748DFF8DC61F,
    0x7FFD3A3F50020332,
    0x7FFE9D1DBC0A75AA,
    0x7FFF4E8E6306ED59,
    0x7FFFA74712C3CDFD,
    0x7FFFD3A381B1FA29,
    0x7FFFE9D1BEED018A,
    0x7FFFF4E8DEFB81D7,
    0x7FFFFA746F5F012F,
    0x7FFFFD3A37A7D0A8,
    0x7FFFFE9D1BD1FC58,
    0x7FFFFF4E8DE8832D,
    0x7FFFFFA746F422D7,
    0x7FFFFFD3A37A09BB,
    0x7FFFFFE9D1BD02F2,
    0x7FFFFFF4E8DE80FE,
    0x7FFFFFFA746F4060,
    0x7FFFFFFD3A37A028,
    0x7FFFFFFE9D1BD012,
    0x7FFFFFFF4E8DE809,
    0x7FFFFFFFA746F404,
    0x7FFFFFFFD3A37A02,
    0x7FFFFFFFE9D1BD01,
    0x7FFFFFFFF4E8DE81,
    0x7FFFFFFFFA746F40,
    0x7FFFFFFFFD3A37A0,
    0x7FFFFFFFFE9D1BD0,
    0x7FFFFFFFFF4E8DE8,
    0x7FFFFFFFFFA746F4,
    0x7FFFFFFFFFD3A37A,
    0x7FFFFFFFFFE9D1BD,
    0x7FFFFFFFFFF4E8DF,
    0x7FFFFFFFFFFA746F,
    0x7FFFFFFFFFFD3A38,
    0x7FFFFFFFFFFE9D1C,
    0x7FFFFFFFFFFF4E8E,
    0x7FFFFFFFFFFFA747,
    0x7FFFFFFFFFFFD3A3,
    0x7FFFFFFFFFFFE9D2,
    0x7FFFFFFFFFFFF4E9,
    0x7FFFFFFFFFFFFA74,
    0x7FFFFFFFFFFFFD3A,
    0x7FFFFFFFFFFFFE9D,
    0x7FFFFFFFFFFFFF4F,
    0x7FFFFFFFFFFFFFA7,
    0x7FFFFFFFFFFFFFD4,
    0x7FFFFFFFFFFFFFEA,
    0x7FFFFFFFFFFFFFF5,
    0x7FFFFFFFFFFFFFFA,
    0x7FFFFFFFFFFFFFFD,
    0x7FFFFFFFFFFFFFFF,
    0x7FFFFFFFFFFFFFFF,
    0x8000000000000000,
};
