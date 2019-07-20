/**
 * Base-2 exponential function.
 * 
 * Copyright 2019 ARaspiK <araspik@protonmail.com>
 * Licensed under the GNU General Public License 3.0.
 * 
 * Based on the LUT algorithm by Claude Baumann (2004), whose work can be found
 * at https://www.convict.lu/Jeunes/ultimate_stuff/exp_ln_2.htm. Thank you!
 */

.file "b2exp.S"

#include "config.h"

.intel_syntax

#ifdef MACHO
.section __TEXT,__text,regular,pure_instructions
#else
.section .text
#endif

.global GLOBAL(b2exp)

#ifdef ELF
.type GLOBAL(b2exp),@function
#endif

.p2align 5, 0x90

GLOBAL(b2exp):
    // x -> qa, qc
        movq rcx, xmm0
        movq rax, xmm0

    // sign = x < 0
        xor dx, dx
        lea rdi, [rip + LOCAL(lut)]
        lea rsi, [rip + LOCAL(lut_rcp)]
        btr rcx, 63
        setnc dl
        cmovc rdi, rsi
        dec rdx

    // abs(x_exp = ((x & EXP_MASK) >> 52) + 12)
        shr rcx, 52
        cmovz rax, [rip + LOCAL(f64.one)]
        jz LOCAL(b2exp.ret)
        cmp cx, 0x07ff
        je LOCAL(b2exp.inf_nan)
        cmp cx, 1023+10
        cmovae rax, [rdi + 65 * 8]
        jae LOCAL(b2exp.ret)
        cmp cx, 1023-52
        cmove rax, [rdi + 64 * 8]
        cmovb rax, [rip + LOCAL(f64.one)]
        jbe LOCAL(b2exp.ret)
        // x_exp + 12
        sub rcx, 1023 - 12

    // man+exp = (x & MAN_MASK) << exp
        xor esi, esi
        mov r8, rsi
        mov r10, rsi
        and rax, [rip + LOCAL(f64.mask.man)]
        bts rax, 52
        // aexp(pos) = rsi
        shld rsi, rax, cl
        // r8 = -exp
        sub r8, rcx
        // man(neg) = r9
        shrx r9, rax, r8
        // man(pos) = rax
        shlx rax, rax, rcx
        // exp < 0 ? (aexp = 0, man = man(neg))
        cmovg rsi, r10
        cmovg rax, r9
        // aexp *= (x < 0 ? -1 : 1)
        add si, dx
        xor si, dx
        // aexp += 1023 - 62
        add si, 1023 - 62
        // TODO: combine into 'add si, dx' above?

    // ONE constant
        mov rcx, 0x8000000000000000
        mov r8, rcx
        mov r9, rcx
    
    // loop
    .p2align 4, 0x90
    LOCAL(b2exp.loop):
        // load sq, multiply
        mov rdx, [rdi]
        bt rax, 63
        cmovnc rdx, rcx
        mulx r10, r8, r8
        // x2
        mov rdx, [rdi + 8]
        bt rax, 62
        cmovnc rdx, rcx
        mulx r11, r9, r9
        // shift right, add CF (a.k.a round)
        shrd r8, r10, 63
        adc r8, 0
        shrd r9, r11, 63
        adc r9, 0
        // update ptr
        add rdi, 16
        // update mantissa
        shl rax, 2
        jnz LOCAL(b2exp.loop)

    // prod0 * prod1
        mov rax, r8
        mul r9

    // shift = bsr prod
        bsr rcx, rdx

    // shift and round
        shrd rax, rdx, cl
        shr rax, 12
        adc rax, 0

    // exp
        add si, cx
        shl rsi, 52

    // mout | exp
        or rax, rsi

    LOCAL(b2exp.ret):
        movq xmm0, rax

    LOCAL(b2exp.ret_raw):
        ret

    LOCAL(b2exp.inf_nan):
        test rax, [rip + LOCAL(f64.mask.man)]
        jnz LOCAL(b2exp.ret)
        movq xmm0, [rdi + 65 * 8]
        ret

#ifdef ELF
.size GLOBAL(b2exp_b2mi), .-GLOBAL(b2exp_b2mi)
#endif

#ifdef MACHO
.section __DATA,__data
#else
.section .data
#endif

.p2align 4

LOCAL(lut):
    .8byte 0xB504F333F9DE6484
    .8byte 0x9837F0518DB8A96F
    .8byte 0x8B95C1E3EA8BD6E7
    .8byte 0x85AAC367CC487B15
    .8byte 0x82CD8698AC2BA1D7
    .8byte 0x8164D1F3BC030773
    .8byte 0x80B1ED4FD999AB6C
    .8byte 0x8058D7D2D5E5F6B1
    .8byte 0x802C6436D0E04F51
    .8byte 0x8016302F17467628
    .8byte 0x800B179C82028FD1
    .8byte 0x80058BAF7FEE3B5D
    .8byte 0x8002C5D00FDCFCB7
    .8byte 0x800162E61BED4A49
    .8byte 0x8000B17292F702A4
    .8byte 0x800058B92ABBAE02
    .8byte 0x80002C5C8DADE4D7
    .8byte 0x8000162E44EAF636
    .8byte 0x80000B1721FA7C19
    .8byte 0x8000058B90DE7E4D
    .8byte 0x800002C5C8678F37
    .8byte 0x80000162E431DBA0
    .8byte 0x800000B1721872D1
    .8byte 0x80000058B90C1AA9
    .8byte 0x8000002C5C8605A4
    .8byte 0x800000162E4300E6
    .8byte 0x8000000B17217FF8
    .8byte 0x800000058B90BFDD
    .8byte 0x80000002C5C85FE7
    .8byte 0x8000000162E42FF2
    .8byte 0x80000000B17217F8
    .8byte 0x8000000058B90BFC
    .8byte 0x800000002C5C85FE
    .8byte 0x80000000162E42FF
    .8byte 0x800000000B17217F
    .8byte 0x80000000058B90C0
    .8byte 0x8000000002C5C860
    .8byte 0x800000000162E430
    .8byte 0x8000000000B17218
    .8byte 0x800000000058B90C
    .8byte 0x80000000002C5C86
    .8byte 0x8000000000162E43
    .8byte 0x80000000000B1721
    .8byte 0x8000000000058B91
    .8byte 0x800000000002C5C8
    .8byte 0x80000000000162E4
    .8byte 0x800000000000B172
    .8byte 0x80000000000058B9
    .8byte 0x8000000000002C5D
    .8byte 0x800000000000162E
    .8byte 0x8000000000000B17
    .8byte 0x800000000000058C
    .8byte 0x80000000000002C6
    .8byte 0x8000000000000163
    .8byte 0x80000000000000B1
    .8byte 0x8000000000000059
    .8byte 0x800000000000002C
    .8byte 0x8000000000000016
    .8byte 0x800000000000000B
    .8byte 0x8000000000000006
    .8byte 0x8000000000000003
    .8byte 0x8000000000000001
    .8byte 0x8000000000000001
    .8byte 0x8000000000000000
    .8byte 0x3FF0000000000001
    .8byte 0x7FF0000000000000

LOCAL(f64.one):
    .8byte 0x3FF0000000000000

LOCAL(f64.mask.man):
    .8byte 0x000FFFFFFFFFFFFF

.p2align 4

LOCAL(lut_rcp):
    .8byte 0x5A827999FCEF3242
    .8byte 0x6BA27E656B4EB57A
    .8byte 0x75606373EE921C97
    .8byte 0x7A92BE8A92436616
    .8byte 0x7D41D96DB915019D
    .8byte 0x7E9F06067A4360BA
    .8byte 0x7F4F08AE3DC7C426
    .8byte 0x7FA765ACA88F6453
    .8byte 0x7FD3AB290E46D769
    .8byte 0x7FE9D3A8E07BF086
    .8byte 0x7FF4E9597BED93AB
    .8byte 0x7FFA748DFF8DC61F
    .8byte 0x7FFD3A3F50020332
    .8byte 0x7FFE9D1DBC0A75AA
    .8byte 0x7FFF4E8E6306ED59
    .8byte 0x7FFFA74712C3CDFD
    .8byte 0x7FFFD3A381B1FA29
    .8byte 0x7FFFE9D1BEED018A
    .8byte 0x7FFFF4E8DEFB81D7
    .8byte 0x7FFFFA746F5F012F
    .8byte 0x7FFFFD3A37A7D0A8
    .8byte 0x7FFFFE9D1BD1FC58
    .8byte 0x7FFFFF4E8DE8832D
    .8byte 0x7FFFFFA746F422D7
    .8byte 0x7FFFFFD3A37A09BB
    .8byte 0x7FFFFFE9D1BD02F2
    .8byte 0x7FFFFFF4E8DE80FE
    .8byte 0x7FFFFFFA746F4060
    .8byte 0x7FFFFFFD3A37A028
    .8byte 0x7FFFFFFE9D1BD012
    .8byte 0x7FFFFFFF4E8DE809
    .8byte 0x7FFFFFFFA746F404
    .8byte 0x7FFFFFFFD3A37A02
    .8byte 0x7FFFFFFFE9D1BD01
    .8byte 0x7FFFFFFFF4E8DE81
    .8byte 0x7FFFFFFFFA746F40
    .8byte 0x7FFFFFFFFD3A37A0
    .8byte 0x7FFFFFFFFE9D1BD0
    .8byte 0x7FFFFFFFFF4E8DE8
    .8byte 0x7FFFFFFFFFA746F4
    .8byte 0x7FFFFFFFFFD3A37A
    .8byte 0x7FFFFFFFFFE9D1BD
    .8byte 0x7FFFFFFFFFF4E8DF
    .8byte 0x7FFFFFFFFFFA746F
    .8byte 0x7FFFFFFFFFFD3A38
    .8byte 0x7FFFFFFFFFFE9D1C
    .8byte 0x7FFFFFFFFFFF4E8E
    .8byte 0x7FFFFFFFFFFFA747
    .8byte 0x7FFFFFFFFFFFD3A3
    .8byte 0x7FFFFFFFFFFFE9D2
    .8byte 0x7FFFFFFFFFFFF4E9
    .8byte 0x7FFFFFFFFFFFFA74
    .8byte 0x7FFFFFFFFFFFFD3A
    .8byte 0x7FFFFFFFFFFFFE9D
    .8byte 0x7FFFFFFFFFFFFF4F
    .8byte 0x7FFFFFFFFFFFFFA7
    .8byte 0x7FFFFFFFFFFFFFD4
    .8byte 0x7FFFFFFFFFFFFFEA
    .8byte 0x7FFFFFFFFFFFFFF5
    .8byte 0x7FFFFFFFFFFFFFFA
    .8byte 0x7FFFFFFFFFFFFFFD
    .8byte 0x7FFFFFFFFFFFFFFF
    .8byte 0x7FFFFFFFFFFFFFFF
    .8byte 0x8000000000000000
    .8byte 0x3FEFFFFFFFFFFFFF
    .8byte 0x0000000000000000