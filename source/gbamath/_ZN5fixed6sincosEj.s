.extern _ZN5fixed4sqrtEj
@ param {angle} Q16.16 (unsigned)
@ returns (Q1.14 | Q1.14), 0 ~ 15bit -> cosine, 16 ~ 31bit -> sine
@ u32	sincos(u32 angle);

.global _ZN5fixed6sincosEj
_ZN5fixed6sincosEj:
	push	{r4, r5, r6, lr}
	mov		r0, r0, LSL #16
	mov		r0, r0, LSR #16 @ angle & 0xFFFF

	mov		r4, r0, LSR #13 @ octant(r4) = angle >> 13
	and		r1, r4, #1
	add		r1, r4, r1 @ (octant + (octant & 1))
	sub		r0, r0, r1, LSL #13 @ x(r5) = angle - ((octant + (octant & 1)) << 13)

	ldr		r12, =0x12F9AE66
	mul		r1, r0, r0 @ r1 = x^2
	umull	r2, r3, r1, r12 @ x^2 * 0x12F9AE66
	@ r3 >> 10
	mov		r2, #0x4000 @ r2 = 1(Q0.14)
	sub		r5, r2, r3, LSR #10 @ cosine(r5) = 1 - x^2 / divisor((x^2 * 0x0x12F9AE660) >> 46)
	mul		r2, r5, r5 @ r2 = c^2
	mov		r3, #0x10000 @ r4 = 1(Q16.16)
	sub		r0, r3, r2, LSR #12 @ 1 - c^2
	bl		_ZN5fixed4sqrtEj
	mov		r6, r0, ASR #2 @ sine(r6) = sqrt(1 - c^2)
	eor		r0, r4, r4, LSL #1 @ shift(r0) = octant ^ (octant << 1)

	tst		r0, #2 @ octant == 1 | 2 | 5 | 6
	eorne	r5, r6, r5
	eorne	r6, r6, r5
	eorne	r5, r6, r5

	tst		r0, #4 @ octant == 2 | 3 | 4 | 5
	rsbne	r5, r5, #0 @ c = -c

	tst		r4, #4 @ octant == 4 | 5 | 6 | 7
	rsbne	r6, r6, #0 @ s = -s

	bic		r0, r5, #0xFF000000
	bic		r0, r0, #0x00FF0000 @ r0 = cosine
	orr		r0, r0, r6, LSL #16 @ r0 = (sine | cosine)

	pop		{r4, r5, r6, pc}