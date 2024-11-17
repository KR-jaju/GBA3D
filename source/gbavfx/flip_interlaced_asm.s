.extern gbavfx_color
.extern gbavfx_fbo
.extern gbavfx_rasterize_interlaced
.extern gbavfx_rasterize_interlaced_odd
.extern gbavfx_interlace

.section .iwram, "ax"
.global gbavfx_flip_interlaced
gbavfx_flip_interlaced:
	ldr		r0, =gbavfx_color
	ldr		r0, [r0]
	tst		r0, #0xA000
	ldrne	r0, =gbavfx_rasterize_interlaced_odd
	ldreq	r0, =gbavfx_rasterize_interlaced_even
	ldr		r1, =.rasterizer_code
	sub		r0, r0, r1 @ 상대 위치
	sub		r0, r0, #8 @ pc 조정
	mov		r0, r0, ASR #2
	orr		r0, r0, #0xEB000000 @ bl instruction (self modifying code)
	str		r0, [r1]
	@----------------------
	mov		r0, #1024
	ldr		r1, =ordering_table
.depth_loop_begin:
	add		r2, r1, r0, LSL #1
	ldrsh	r2, [r2] @ ordering_table[i]
	cmp		r2, #-1
	beq		.face_loop_end
	push	{r0, r1}
.face_loop_begin:
	ldr		r3, =gbavfx_fbo
	add		r3, r3, r2, LSL #3
	ldmia	r3, {r0, r1}
	mov		r2, r1, ASR #21
	push	{r2-r3, lr}
.rasterizer_code:
	nop
	pop		{r2-r3, lr}
	cmp		r2, #-1
	bne		.face_loop_begin
	pop		{r0, r1}
.face_loop_end:
	subs	r0, r0, #1
	bne		.depth_loop_begin
	@-------------------INTERLACE COPY
	push	{lr}
	bl		gbavfx_interlace
	pop		{lr}
	bx		lr
	