
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
	@ orr		r2, r2, #16 @ r1 |= TIMER1_INTERRUPT_BIT
	strh	r2, [r1] @ REG_INTERRUPT_ENABLE = r1
	add		r1, r0, #0x0208 @ r1 = &REG_INTERRUPT_MASTER_ENABLE
	mov		r2, #1
	strh	r2, [r1] @ REG_IME = 1, enable interrupts
	bx		lr

@ r0 = interrupt id
@ r1 = handler address
.global _ZN3gba19setInterruptHandlerE11InterruptIDPFvvE
_ZN3gba19setInterruptHandlerE11InterruptIDPFvvE:
	adr		r2, .self_modifying_code_pivot @ base
	add		r2, r2, r0, LSL #3 @ branch_src
	sub		r1, r1, r2 @ calculate (branch_dst - branch_src)
	sub		r1, r1, #8 @ pc is 8bytes ahead, so subtract 8 to correct the address difference
	mov		r1, r1, LSR #2
	bic		r1, r1, #0xFF000000 @ (address_diff >> 2)
	orr		r0, r1, #0x1B000000 @ blne
	str		r0, [r2] @ modify code
	bx		lr

.interrupt_handler:
	push	{r0, r1, r2, lr}
	mov		r0, #0x04000000 @ r0 = I/O register base
	add		r0, r0, #0x0200
	add		r0, r0, #0x0002 @ r0 = &REG_IF
	ldrh	r1, [r0] @ r1 = REG_INTERRUPT_FLAG
	tst		r1, #1	@ VBlank FLAG
.self_modifying_code_pivot:
	nop
	tst		r1, #2		@ HBlank FLAG
	nop
	tst		r1, #4		@ VCount FLAG
	nop
	tst		r1, #8		@ Timer0 FLAG
	nop
	tst		r1, #16 	@ Timer1 FLAG
	nop
	tst		r1, #32		@ Timer2 FLAG
	nop
	tst		r1, #64		@ Timer3 FLAG
	nop
	tst		r1, #128	@ Serial FLAG
	nop
	tst		r1, #256	@ DMA0 FLAG
	nop
	tst		r1, #512	@ DMA1 FLAG
	nop
	tst		r1, #1024	@ DMA2 FLAG
	nop
	tst		r1, #2048	@ DMA3 FLAG
	nop
	strh	r1, [r0] @ INTERRUPT_FLAG = INTERRUPT_FLAG
	pop		{r0, r1, r2, pc}