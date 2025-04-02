.extern _ZN5mode87contextE

.section .iwram, "ax"
.global _ZN5mode84initEv
_ZN5mode84initEv:
	@ --------------- context init ---------------------
	ldr		r0, =_ZN5mode87contextE @ r0 = &context
	mov		r1, #0
	str		r1, [r0, #0x0BF4] @ context->vblank_counter = 0

	add		r1, r0, #0x0C00 @ r1 = &context->post_transform_buffer
	str		r1, [r0, #0x0BF8] @ init ptb_top

	add		r1, r0, #0x2C00 @ r2 = &context->face_buffer
	str		r1, [r0, #0x0BFC] @ init fb_top

	@ --------------- context init ---------------------

	mov		r0, #0x04000000 @ r0 = I/O register base
	sub		r1, r0, #0x0004 @ r1 = ISR_MAIN
	adr		r2, .vblank_isr
	str		r2, [r1] @ ISR_MAIN = vblank_isr

	add		r1, r0, #0x0004 @ r1 = &DISPSTAT
	ldrh	r2, [r1] @ r2 = DISPSTAT
	orr		r2, r2, #0x0008 @ DISPSTAT | VID_VBL_IRQ
	strh	r2, [r1] @ DISPSTAT |= VID_VBL_IRQ, tell display to fire vblank interrupt
	add		r1, r0, #0x200 @ r1 = &REG_IE
	mov		r2, #1
	strh	r2, [r1] @ REG_IE = 1, tell gba to catch vblank interrupts
	add		r1, r0, #0x0208 @ r1 = &REG_IME
	strh	r2, [r1] @ REG_IME = 1, enable interrupts
	bx		lr

.vblank_isr:
	push	{r0, r1}
	ldr		r0, =_ZN5mode87contextE @ r0 = &context
	ldr		r1, [r0, #0x0BF4] @ r1 = context->vblank_counter
	add		r1, r1, #1
	str		r1, [r0, #0x0BF4] @ vblank_counter = r1
	mov		r0, #0x04000000 @ r0 = I/O register base
	add		r0, r0, #0x0200
	add		r0, r0, #0x0002 @ r0 = &REG_IF
	mov		r1, #1
	strh	r1, [r0] @ REG_IF = 1
	pop		{r0, r1}
	bx		lr
