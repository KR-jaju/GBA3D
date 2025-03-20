.extern	division_lut

.section .iwram, "ax"
.global reciprocal_i16
reciprocal_i16:
	adds	r1, r0, #1 @ r1 = r0 + 1											1 cycle
	cmp		r1, #2 @															1 cycle
	movle	r0, #0x7FFFFFFF @ 0x7FFFFFFF if -1 + 1 <= r0 + 1 <= 1 + 1			1 cycle
	bxle	lr @ divide by (almost) zero										1 or 3 cycle
	@ total 6 cycles (early return)
	@ --------- count leading zero ---------
	cmp		r0, #0 @ if r0 < 0													1 cycle
	rsblt	r0, r0, #0 @ r0 = -r0												1 cycle
	mov		r1, r0, LSL #16 @													1 cycle
	orrlt	r1, r1, #0x00000001 @ store sign bit in lo(r1)						1 cycle
	mov		r2, #0 @															1 cycle
	tst		r1, #0xFF000000 @													1 cycle
	moveq	r1, r1, LSL #8 @													1 cycle
	addeq	r2, r2, #8 @														1 cycle
	tst		r1, #0xF0000000 @													1 cycle
	moveq	r1, r1, LSL #4 @													1 cycle
	addeq	r2, r2, #4 @														1 cycle
	tst		r1, #0xC0000000 @													1 cycle
	moveq	r1, r1, LSL #2 @													1 cycle
	addeq	r2, r2, #2 @														1 cycle
	tst		r1, #0x80000000 @													1 cycle
	addeq	r2, r2, #1 @														1 cycle
	@----------count leading zero calculated-------------
	@ (r2 is clz(result), and r1 is free)
	@ 16bit fixed point -> clz >= 16 (always)
	tst		r1, #0x000000FF @ has sign bit?(test 1)								1 cycle
	tsteq	r1, #0x0000FF00 @ has sign bit?(test 2)								1 cycle

	mov		r1, r0, LSL r2 @ i <<= (lz - 16)									1 cycle
	sub		r1, r1, #32768 @ omit leading 1										1 cycle
	@------------Key calculated--------------
	ldr		r0, =division_lut @													3 cycle
	add		r0, r0, r1, LSL #1 @												1 cycle
	ldrh	r1, [r0] @ *(division_lut + key * 2)								3 cycle
	@------------Lut value retrieved-----------
	moveq	r0, r1, LSL r2 @ r0 = r1 << r2 if r0 >= 0							1 cycle
	rsbne	r0, r1, LSL r2 @ r0 = -(r1 << r2) if r0 < 0							1 cycle
	bx		lr @ return															3 cycle
	@ total 35 cycles