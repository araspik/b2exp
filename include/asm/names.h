/**
 * A standardized naming system for assembly x86(_64) registers.
 *
 * Bytes: L_ (low), H_ (high)
 * Words: W_
 * Doublewords: D_
 * Quadwords: Q_
 * MMX: M_
 * XMM: X_
 * YMM: Y_
 *
 * The first 8 general purpose registers are named specially:
 * (r/e)a(x/l/h): a
 * (r/e)b(x/l/h): b
 * (r/e)c(x/l/h): c
 * (r/e)d(x/l/h): d
 * (r/e)si(l): i (input)
 * (r/e)di(l): o (output)
 * (r/e)sp(l): s (stack)
 * (r/e)bp(l): f (frame)
 * r8..15(d/w/l): 8..9,A..F (hexadecimal)
 * (r/e)ip: e (execution)
 * (x/y)mm0..(8/16): 0..9,A..F
 *
 * The size of the register is always encoded by the prefix.
 *
 * ---
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org>
 */

#define La al
#define Lb bl
#define Lc cl
#define Ld dl
#define Li sil
#define Lo dil
#define Ls spl
#define Lf bpl
#define L8 r8l
#define L9 r9l
#define LA r10l
#define LB r11l
#define LC r12l
#define LD r13l
#define LE r14l
#define LF r15l

#define Ha ah
#define Hb bh
#define Hc ch
#define Hd dh

#define Wa ax
#define Wb bx
#define Wc cx
#define Wd dx
#define Wi si
#define Wo di
#define Ws sp
#define Wf bp
#define W8 r8w
#define W9 r9w
#define WA r10w
#define WB r11w
#define WC r12w
#define WD r13w
#define WE r14w
#define WF r15w
#define We ip

#define Da eax
#define Db ebx
#define Dc ecx
#define Dd edx
#define Di esi
#define Do edi
#define Ds esp
#define Df ebp
#define D8 r8d
#define D9 r9d
#define DA r10d
#define DB r11d
#define DC r12d
#define DD r13d
#define DE r14d
#define DF r15d
#define De eip

#define Qa rax
#define Qb rbx
#define Qc rcx
#define Qd rdx
#define Qi rsi
#define Qo rdi
#define Qs rsp
#define Qf rbp
#define Q8 r8
#define Q9 r9
#define QA r10
#define QB r11
#define QC r12
#define QD r13
#define QE r14
#define QF r15
#define Qe rip

#define M0 mm0
#define M1 mm1
#define M2 mm2
#define M3 mm3
#define M4 mm4
#define M5 mm5
#define M6 mm6
#define M7 mm7

#define X0 xmm0
#define X1 xmm1
#define X2 xmm2
#define X3 xmm3
#define X4 xmm4
#define X5 xmm5
#define X6 xmm6
#define X7 xmm7
#define X8 xmm8
#define X9 xmm9
#define XA xmm10
#define XB xmm11
#define XC xmm12
#define XD xmm13
#define XE xmm14
#define XF xmm15

#define Y0 ymm0
#define Y1 ymm1
#define Y2 ymm2
#define Y3 ymm3
#define Y4 ymm4
#define Y5 ymm5
#define Y6 ymm6
#define Y7 ymm7
#define Y8 ymm8
#define Y9 ymm9
#define YA ymm10
#define YB ymm11
#define YC ymm12
#define YD ymm13
#define YE ymm14
#define YF ymm15
