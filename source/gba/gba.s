
@ 인터럽트 핸들러
@ sp와 lr은 인터럽트용으로 뱅크되고, r0~r12는 필요하면 스택에 저장해야함


.section .iwram, "ax"
.global _ZN3gba4initEv
_ZN3gba4initEv:
	mov		r0, #0x04000000 @ r0 = I/O register base
	sub		r1, r0, #0x0004 @ r1 = ISR_MAIN
	adr		r2, .interrupt_handler
	str		r2, [r1] @ ISR_MAIN = interrupt_handler
	add		r1, r0, #0x0004 @ r1 = &DISPSTAT
	ldrh	r2, [r1] @ r2 = DISPSTAT
	orr		r2, r2, #0x0008 @ DISPSTAT | VID_VBL_IRQ
	strh	r2, [r1] @ DISPSTAT |= VID_VBL_IRQ, tell display to fire vblank interrupt
	add		r1, r0, #0x200 @ r1 = &REG_INTERRUPT_ENABLE
	mov		r2, #1 @ r1 |= VBLANK_INTERRUPT_BIT
	orr		r2, r2, #16 @ r1 |= TIMER1_INTERRUPT_BIT
	strh	r2, [r1] @ REG_INTERRUPT_ENABLE = r1
	add		r1, r0, #0x0208 @ r1 = &REG_INTERRUPT_MASTER_ENABLE
	strh	r2, [r1] @ REG_IME = 1, enable interrupts
	bx		lr


.interrupt_handler:
	push	{r0, r1, lr}
	mov		r0, #0x04000000 @ r0 = I/O register base
	add		r0, r0, #0x0200
	add		r0, r0, #0x0002 @ r0 = &REG_IF
	ldrh	r1, [r0] @ r1 = REG_INTERRUPT_FLAG
	tst		r1, #1	@ VBlank FLAG
	blne	.vblank_isr
	tst		r1, #16 @ Timer1 FLAG
	blne	.timer1_isr
	strh	r1, [r0] @ INTERRUPT_FLAG = INTERRUPT_FLAG
	pop		{r0, r1, pc}

.timer1_isr:
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