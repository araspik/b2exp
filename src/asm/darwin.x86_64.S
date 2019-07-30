/**
 * Raises 2 to the power of `x`.
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

#include "asm/names.h"

.section __TEXT,__text,regular,pure_instructions

.global _b2exp

.intel_syntax

_b2exp:
    // qc = x0
    // q8 = qc
    movq    Qc, X0
    mov     Q8, Qc

    // qc = qc >> 52
    // qc[12] =? 0
    // qi = 0
    // qi = qi - (0 + CF)
    // q8 = q8 << 12
    // qc = qc - 1023 + 52
    // <= 00 ? min
    // >= 62 ? max
    shr     Qc, 52
    xor     Di, Di
    btr     Dc, 12
    sbb     Qi, 0
    shl     Q8, 12
    sub     Dc, 971
    jle     L_.min
    cmp     Dc, 62
    jae     L_.max

    // qo = &LUT[0]
    // qd = 8*64
    // qd = qd & qi
    // qo = qo + qd
    // qa = 1
    // qa = qa,q8 << qc
    // qc = qi + 8
    // qi = qi ^ qa
    // qa = qa,q8 << 12
    lea     Qo, [rip + _b2exp_LUT]
    mov     Dd, 8*64
    and     Dd, Di
    add     Qo, Qd
    mov     Da, 1
    shld    Qa, Q8, Lc
    lea     Qc, [Qi + 8]
    xor     Qi, Qd
    shld    Qa, Q8, 12

    // loop
    .p2align 4, 0x90
    L_.loop:

        // qd = 1.0m63
        // q9 = qd
        // qa[63] ?
        // qd CF?= qo[0]
        // qA,qB = qA * qd
        // qa = qa << 2
        // q9 CF?= qo[1]
        // qd = q8
        // q8,q9 = q9 * qd
        // == 0 ? fin
        // qA = qB,qA >> 63
        // qA = qA + (0 + CF)
        // q8 = q9,q8 >> 63
        // q8 = q8 + (0 + CF)
        // loop
        mov     Qd, 0x8000000000000000
        mov     Q9, Qd
        bt      Qa, 63
        cmovc   Qd, [Qo + 0]
        mulx    QB, QA, QA
        shl     Qa, 2
        cmovc   Q9, [Qo + 8]
        mov     Qd, Q8
        mulx    Q9, Q8, Q9
        jz      L_.loop.fin
        shrd    QA, QB, 63
        adc     QA, 0
        shrd    Q8, Q9, 63
        adc     Q8, 0
        jmp     L_.loop

    L_.loop.fin:

    // qd = q9
    // qd,qa = qB * qd
    // qo = inf
    // qi = qi & qo
    // q8 = one
    // qi = qi + q8
    // qd = qd >> lc
    // qd = qd + (0 + CF)
    // qd[52] =? 0
    // qd = qd | qi
    // ret
    mov     Qd, Q9
    mul     QB
    mov     Qo, 0x7FF0000000000000
    and     Qi, Qo
    mov     Q8, 0x3FF0000000000000
    add     Qi, Q8
    shr     Qd, Lc
    adc     Qd, 0
    btr     Qd, 52
    or      Qd, Qi

    L_.ret:

        // x0 = qd
        movq    X0, Qd

    L_.ret_raw:

        // return
        ret

    L_.min:

        // qd = 1f64
        // != 0 ? ret
        // qd = qd + 1
        // qi = qi << 1
        // qd = qd + qi
        // ret
        mov     Qd, 0x3FF0000000000000
        jnz     L_.ret
        add     Qd, 1
        shl     Qi, 1
        add     Qd, Qi
        jmp     L_.ret

    L_.max:

        // q8 != 0 ? ret_raw
        // qi = ~qi
        // qd = +inf
        // qd = qd & qi
        // ret
        test    Q8, Q8
        jnz     L_.ret_raw
        mov     Qd, 0x7FF0000000000000
        and     Qd, Qi
        jmp     L_.ret

.section __TEXT,__const

.global _b2exp_LUT
