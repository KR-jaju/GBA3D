.extern _ZN5mode87contextE

.section .iwram, "ax"
.global _ZN5mode85clearEv
_ZN5mode85clearEv:
	@ r0 = background
	@ r1 = offset.x
	@ r2 = offset.y
	@ add		r1, r0, r1 @ r1 = background + background_offset.u;
	@ mov		r12, #1200
	@ mla		r1, r2, r12, r1 @ r1 = background + background_offset.v * 1200;

	ldr		r0, =_ZN5mode87contextE @ r0 = &context
	ldr		r1, [r0, #0x0BEC] @ r1 = context->background
	ldr		r2, [r0, #0x0BF0] @ r2 = context->background_offset
	add		r1, r1, r2 @ background += background_offset

	mov		r2, #0x04000000 @ I/O register base
	ldr		r12, [r2] @ r12 = REG_DISPCNT
	mov		r3, #0x06000000 @ r3(dst) = buffer[0]
	tst		r12, #0x0010 @ REG_DISPCNT 5th bit (page_flip bit)
	eoreq	r3, #0x0000A000 @ r3(dst) = buffer[1] (back_buffer == buffer[1])

	@ r1 = background(offset applied)
	@ r2 = I/O register base
	@ r3(dst) = back_buffer
	@ r0, r12
	@ dst = ordering_table (r0)
	@ src = sp(r13)
	@ control = (r12)
	@ src, dst, control (r13, r12, r0)
	@ r2 = I/O + #0xF0
	mvn		r0, #0 @ r0 = -1
	str		r0, [sp, #-4]! @ save -1
	ldr		r0, =_ZN5mode87contextE @ r0 = &context->ordering_table

	add		r12, r0, #0x0C00
	str		r12, [r0, #0x0BF8] @ context->ptb_top = &context->post_transform_buffer
	add		r12, r0, #0x2C00
	str		r12, [r0, #0x0BFC] @ context->fb_top = &context->face_buffer

	@ mov		r12, #768 @ (n of copy)
	@ orr		r12, r12, #0x81000000 @ (enable dma bit) | (fixed dst bit)
	mov		r12, #384 @ (n of copy)
	orr		r12, r12, #0x85000000 @ (enable dma bit) | 32bit copy | (fixed dst bit)
	@ 32bit copy is slightly(literally) faster
	add		r2, r2, #0xD4 @ DMA 3 register
	str		sp, [r2] @ src = sp
	str		r0, [r2, #4] @ dst = r0
	str		r12, [r2, #8] @ control = r12
	add		sp, sp, #4 @ pop -1

	eor		r0, r3, #0xA000 @ r0(src) = dst ^ 0xA000
	mov		r12, #120 @ 2byte * 120 = 240 pixels
	orr		r12, r12, #0x80000000 @ dma control value
	tst		r3, #0xA000 @ test if dst(r3) is buffer[0]
	beq		.clear_0 @ clear buffer[0]
	bne		.clear_1 @ clear buffer[1]

@ buffer[0] 초기화
@ 0, 2, 4.. 번째 줄을 buffer[1]로부터 복사.
@ 1, 3, 5.. 번째 줄을 배경으로부터 복사.
@ r0 = buffer[1]
@ r1 = background (offset 적용됨)
@ r2 = DMA I/O register
@ r3 = buffer[0]
@ r12 = dma control value
.clear_0:
	add		r1, r1, #1200 @ background 한 줄 다음으로 이동
.clear_0_loop: @ 8줄씩 복사
	stmia	r2, {r0, r3, r12} @ DMA src, dst, control
	add		r0, r0, #480 @ buffer[1] 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[0] 한 줄 다음으로 이동
	stmia	r2, {r1, r3, r12}
	add		r1, r1, #2400 @ background 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[0] 한 줄 다음으로 이동

	stmia	r2, {r0, r3, r12}
	add		r0, r0, #480 @ buffer[1] 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[0] 한 줄 다음으로 이동
	stmia	r2, {r1, r3, r12}
	add		r1, r1, #2400 @ background 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[0] 한 줄 다음으로 이동

	stmia	r2, {r0, r3, r12}
	add		r0, r0, #480 @ buffer[1] 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[0] 한 줄 다음으로 이동
	stmia	r2, {r1, r3, r12}
	add		r1, r1, #2400 @ background 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[0] 한 줄 다음으로 이동

	stmia	r2, {r0, r3, r12}
	add		r0, r0, #480 @ buffer[1] 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[0] 한 줄 다음으로 이동
	stmia	r2, {r1, r3, r12}
	add		r1, r1, #2400 @ background 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[0] 한 줄 다음으로 이동

	sub		r3, r3, #0x06000000
	cmp		r3, #0x9600 @ (dst - 0x06000000) < 0x9600
	add		r3, r3, #0x06000000
	blt		.clear_0_loop
	bx		lr

@ buffer[1] 초기화
@ 0, 2, 4.. 번째 줄을 배경으로부터 복사.
@ 1, 3, 5.. 번째 줄을 buffer[0]로부터 복사.
@ r0 = buffer[0]
@ r1 = background (offset 적용됨)
@ r2 = DMA I/O register
@ r3 = buffer[1]
.clear_1: 
	add		r0, r0, #240 @ buffer[0] 한 줄 다음으로 이동
.clear_1_loop: @ 8줄씩 복사
	stmia	r2, {r1, r3, r12} @ DMA src, dst, control
	add		r1, r1, #2400 @ background 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[1] 한 줄 다음으로 이동
	stmia	r2, {r0, r3, r12}
	add		r0, r0, #480 @ buffer[0] 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[1] 한 줄 다음으로 이동

	stmia	r2, {r1, r3, r12}
	add		r1, r1, #2400 @ background 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[1] 한 줄 다음으로 이동
	stmia	r2, {r0, r3, r12}
	add		r0, r0, #480 @ buffer[0] 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[1] 한 줄 다음으로 이동

	stmia	r2, {r1, r3, r12}
	add		r1, r1, #2400 @ background 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[1] 한 줄 다음으로 이동
	stmia	r2, {r0, r3, r12}
	add		r0, r0, #480 @ buffer[0] 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[1] 한 줄 다음으로 이동

	stmia	r2, {r1, r3, r12}
	add		r1, r1, #2400 @ background 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[1] 한 줄 다음으로 이동
	stmia	r2, {r0, r3, r12}
	add		r0, r0, #480 @ buffer[0] 두 줄 다음으로 이동
	add		r3, r3, #240 @ buffer[1] 한 줄 다음으로 이동

	sub		r3, r3, #0x06000000
	cmp		r3, #0x13000 @ (dst - 0x06000000) < 0x13000, 끝에서 6.4줄 부족한 값, 8줄씩 복사하기에 가능
	add		r3, r3, #0x06000000
	blt		.clear_1_loop
	bx		lr