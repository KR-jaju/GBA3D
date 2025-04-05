.extern	division_lut

.section .iwram, "ax"
.global reciprocal_u16
reciprocal_u16:
	cmp		r0, #1 @ 												1 cycle
	movls	r0, #0x7FFFFFFF @ 										1 cycle
	bxls	lr @ divide by (almost) zero	 						1 or 3 cycle
	@ total 5 cycles (early return)
	@ --------- count leading zero ---------
	mov		r1, r0, LSL #16 @ 										1 cycle
	mov		r2, #0 @ 												1 cycle
	tst		r1, #0xFF000000 @ 										1 cycle
	moveq	r1, r1, LSL #8 @ 										1 cycle
	addeq	r2, r2, #8 @ 											1 cycle
	tst		r1, #0xF0000000 @ 										1 cycle
	moveq	r1, r1, LSL #4 @ 										1 cycle
	addeq	r2, r2, #4 @ 											1 cycle
	tst		r1, #0xC0000000 @ 										1 cycle
	moveq	r1, r1, LSL #2 @ 										1 cycle
	addeq	r2, r2, #2 @ 											1 cycle
	tst		r1, #0x80000000 @ 										1 cycle
	addeq	r2, r2, #1 @ 											1 cycle
	@----------count leading zero calculated-------------(r2 is clz(result), and r1 is free)
	@ 16bit fixed point -> clz >= 16 (always)
	mov		r1, r0, LSL r2 @ i <<= (lz - 16)						1 cycle
	sub		r1, r1, #32768 @ omit leading 1							1 cycle
	@------------Key calculated--------------
	ldr		r0, =division_lut @										3 cycle
	add		r0, r0, r1, LSL #1 @									1 cycle
	ldrh	r1, [r0] @ *(division_lut + key * 2)					3 cycle
	@------------Lut value retrieved-----------
	mov		r0, r1, LSL r2 @										1 cycle
	bx		lr @													3 cycle
	@ total 29 cycles
	