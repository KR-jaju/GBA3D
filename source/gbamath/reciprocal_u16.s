.extern	division_lut

.section .iwram, "ax"
.global reciprocal_u16
reciprocal_u16:
	cmp		r0, #1
	movls	r0, #0x7FFFFFFF
	bxls	lr @ if (u <= 1)
	mov		r1, r0, LSL #16
	mov		r2, #0
	tst		r1, #0xFF000000
	moveq	r1, r1, LSL #8
	addeq	r2, r2, #8
	tst		r1, #0xF0000000
	moveq	r1, r1, LSL #4
	addeq	r2, r2, #4
	tst		r1, #0xC0000000
	moveq	r1, r1, LSL #2
	addeq	r2, r2, #2
	tst		r1, #0x80000000
	addeq	r2, r2, #1
	@----------Count leading zero calculated-------------(r2 is clz(result), and r1 is returned)
	@ clz >= 16 (always)
	mov		r1, r0, LSL r2 @ i << (lz - 16)
	sub		r1, r1, #32768
	@------------Key calculated--------------
	ldr		r0, =division_lut
	add		r0, r0, r1, LSL #1
	ldrh	r1, [r0] @ *(division_lut + key * 2)
	@------------Lut value retrieved-----------
	mov		r0, r1, LSL r2
	bx		lr