.extern	division_lut

.section .iwram, "ax"
.global reciprocal
reciprocal:
	cmp		r0, #1 @ if (i == 1) -> return INF				1 cycle
	movls	r0, #0x7FFFFFFF
	bxls	lr @											1 cycle
	rsblt	r1, r0, #0 @ i' = -i;							1 cycle
	movgt	r1, r0 @ i' = i									1 cycle
	mov		r3, #0 @ i32 lz = 0;							1 cycle
	cmp		r3, r1, LSR #16 @ if ((i' >> 16) == 0)			1 cycle
	moveq	r2, r1, LSL #16 @ x = (i' << 16);				1 cycle
	movne	r2, r1 @ x = i'									1 cycle
	addeq	r3, r3, #16	@									1 cycle
	tst		r2, #0xFF000000
	moveq	r2, r2, LSL #8
	addeq	r3, r3, #8
	tst		r2, #0xF0000000
	moveq	r2, r2, LSL #4
	addeq	r3, r3, #4
	tst		r2, #0xC0000000
	moveq	r2, r2, LSL #2
	addeq	r3, r3, #2
	tst		r2, #0x80000000
	addeq	r3, r3, #1
	@----------Count leading zero calculated-------------(r3 is clz(result), and r2 is returned)
	subs		r3, r3, #16 @ lz - 16
	rsble		r3, r3, #0 @ 16 - lz
	movle		r2, r1, LSR r3
	movgt		r2, r1, LSL r3
	sub			r2, r2, #32768
	@------------Key calculated--------------
	ldr			r1, =division_lut
	add			r1, r1, r2, LSL #1
	ldrh		r2, [r1] @ *(division_lut + key * 2)
	@------------Lut value retrieved-----------
	movle		r2, r2, LSR r3
	movgt		r2, r2, LSL r3
	cmp			r0, #0 @ is_negative?
	rsblt		r0, r2, #0 @ -result;
	movge		r0, r2
	bx			lr