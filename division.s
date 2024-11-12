.extern	division_lut

.global reciprocal
reciprocal:
	subs	r1, r0, #0 @ if (d == 0)
	mvneq	r0, #0 
	bxeq	lr @ return (u32(-1)); // divide by zero
	@ moveq	r2, #32 @ count = 32
	@ beq		.L1
	mov		r2, #0 @ count = 0
	cmp		r2, r1, LSR #16 @ if ((d >> 16) == 0)
	lsleq	r1, r1, #16
	addeq	r2, r2, #16
	tst		r1, #0xFF000000
	lsleq	r1, r1, #8
	addeq	r2, r2, #8
	tst		r1, #0xF0000000
	lsleq	r1, r1, #4
	addeq	r2, r2, #4
	tst		r1, #0xC0000000
	lsleq	r1, r1, #2
	addeq	r2, r2, #2
	tst		r1, #0x80000000
	addeq	r2, r2, #1
.L1:@ r2
	@ u32 key = d << (lz + 1);
	add		r1, r2, #1 @ lz + 1
	mov		r3, r0, LSL r1 @ key = r3
	@ u32 value = division_lut[key >> 17];
	ldr		r2, =division_lut
	ldr		r2, [r2, r3, LSR #15] @ division_lut[key >> 17];
	@ return (value << (lz - 16))
	subs	r1, r1, #17 @ lz - 16
	movlt	r0, r2, LSR r1
	rsbge	r1, r1, #0
	movge	r0, r2, LSL r1
	bx		lr