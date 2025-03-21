.extern _ZN5mode87contextE

.section .iwram, "ax"
.global _ZN5mode84flipEv
_ZN5mode84flipEv:
	ldr		r0, =_ZN5mode87contextE @ r1 = &context
.vsync:
	ldr		r1, [r0, #0x0BF4] @ r1 = vblank_counter
	cmp		r1, #2
	blt		.vsync
	mov		r1, #0
	str		r1, [r0, #0x0BF4] @ vblank_counter = 0
	mov		r0, #0x04000000 @ &REG_DISPCNT
	ldr		r1, [r0] @ r1 = REG_DISPCNT
	eor		r1, r1, #0x10 @ r1 ^= DCNT_PAGE (page flip)
	str		r1, [r0] @ REG_DISPCNT = r1
	bx		lr