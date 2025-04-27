
.section .iwram, "ax"
.global _ZN5mode89vblankISREv
_ZN5mode89vblankISREv:
	ldr		r2, =_ZN5mode87contextE @ r2 = &context
	ldr		r3, [r2, #0x0BF4] @ r3 = context->vblank_counter
	add		r3, r3, #1
	str		r3, [r2, #0x0BF4] @ context->vblank_counter = r3
	bx		lr
