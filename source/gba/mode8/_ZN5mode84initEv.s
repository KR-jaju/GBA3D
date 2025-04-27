.extern _ZN5mode87contextE

.section .iwram, "ax"
.global _ZN5mode84initEv
_ZN5mode84initEv:
	mov		r3, lr
	@ --------------- context init ---------------------
	ldr		r0, =_ZN5mode87contextE @ r0 = &context
	mov		r1, #0
	str		r1, [r0, #0x0BF4] @ context->vblank_counter = 0

	add		r1, r0, #0x0C00 @ r1 = &context->post_transform_buffer
	str		r1, [r0, #0x0BF8] @ init ptb_top

	add		r1, r0, #0x2C00 @ r2 = &context->face_buffer
	str		r1, [r0, #0x0BFC] @ init fb_top

	@ --------------- context init ---------------------
	
	@ ldr		r0, =_ZN3gba10vblank_isrE
	@ adr		r1, .vblank_isr
	@ str		r1, [r0]
	mov			r0, #0 @ r0 = INTERRUPT_ID_VBLANK
	adr			r1, .vblank_isr
	bl			_ZN3gba19setInterruptHandlerE11InterruptIDPFvvE	@ gba::setInterruptHanlder();
	bx		r3

.vblank_isr:
	push	{r0, lr}
	ldr		r0, =_ZN5mode87contextE @ r0 = &context
	ldr		lr, [r0, #0x0BF4] @ lr = context->vblank_counter
	add		lr, lr, #1
	str		lr, [r0, #0x0BF4] @ vblank_counter = lr
	pop		{r0, pc}