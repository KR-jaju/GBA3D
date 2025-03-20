.extern _ZN5mode87contextE
.extern _ZN5mode814vblank_counterE

.section .iwram, "ax"
.global _ZN5mode84flipEv
_ZN5mode84flipEv:
	ldr		r0, =_ZN5mode814vblank_counterE @ r0 = &vblank_counter
	ldr		r1, =_ZN5mode87contextE @ r1 = &context
.vsync:
	ldr		r2, [r0] @ r2 = vblank_counter
	cmp		r2, #2
	blt		.vsync
	mov		r2, #0
	str		r2, [r0] @ vblank_counter = 0
	mov		r0, #0x04000000 @ &REG_DISPCNT
	ldr		r2, [r0] @ r2 = REG_DISPCNT
	eor		r2, r2, #0x10 @ r2 ^= DCNT_PAGE (page flip)
	str		r2, [r0] @ REG_DISPCNT = r2
	ldr		r2, [r1] @ r2 = context->render_target
	eor		r2, r2, #0xA000 @ page flip
	str		r2, [r1] @ context->render_target = r2
	bx		lr