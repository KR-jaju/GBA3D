
@ 인터럽트 핸들러
@ sp와 lr은 인터럽트용으로 뱅크되고, r0~r12는 필요하면 스택에 저장해야함

.section .iwram, "ax"

.global _ZN3gba4initEv
_ZN3gba4initEv:
	push	{lr}
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
	@ orr		r2, r2, #16 @ r1 |= TIMER1_INTERRUPT_BIT
	strh	r2, [r1] @ REG_INTERRUPT_ENABLE = r1
	add		r1, r0, #0x0208 @ r1 = &REG_INTERRUPT_MASTER_ENABLE
	mov		r2, #1
	strh	r2, [r1] @ REG_IME = 1, enable interrupts
	bl		_ZN5mode84initEv @ mode8::init
	pop		{pc}

@ r0 = interrupt id
@ r1 = handler address

.interrupt_handler:
	push	{r0, r1, r2, r3, lr}
	mov		r0, #0x04000000 @ r0 = I/O register base
	add		r0, r0, #0x0200
	add		r0, r0, #0x0002 @ r0 = &REG_IF
	ldrh	r1, [r0] @ r1 = REG_INTERRUPT_FLAG
	bl		_ZN5mode89vblankISREv
	strh	r1, [r0] @ INTERRUPT_FLAG = INTERRUPT_FLAG
	pop		{r0, r1, r2, r3, pc}
	
@ tst		r1, #1		@ VBlank FLAG
@ tst		r1, #2		@ HBlank FLAG
@ tst		r1, #4		@ VCount FLAG
@ tst		r1, #8		@ Timer0 FLAG
@ tst		r1, #16 	@ Timer1 FLAG
@ tst		r1, #32		@ Timer2 FLAG
@ tst		r1, #64		@ Timer3 FLAG
@ tst		r1, #128	@ Serial FLAG
@ tst		r1, #256	@ DMA0 FLAG
@ tst		r1, #512	@ DMA1 FLAG
@ tst		r1, #1024	@ DMA2 FLAG
@ tst		r1, #2048	@ DMA3 FLAG
