.extern gbavfx_color
.extern gbavfx_background
.extern gbavfx_fbo
.extern gbavfx_rasterize_interlaced
.extern gbavfx_rasterize_interlaced_odd
.extern gbavfx_interlace

.section .iwram, "ax"
.global gbavfx_flip_interlaced
gbavfx_flip_interlaced:
	push	{r4, r5, r6, lr}
	ldr		r5, =gbavfx_color
	ldr		r0, [r5]
	eor		r6, r0, #0xA000 @ vid_page ^ 0xA000

	ldr		r1, =gbavfx_background
	ldr		r1, [r1]

	mov		lr, #0x04000000
	mov		r3, #120
	orr		r3, r3, #0x80000000 @ copy count

	tst		r0, #0xA000 @ what page is currently being displyed?
	ldrne	ip, =gbavfx_rasterize_interlaced_odd @ buffer[0] is being displayed
	ldreq	ip, =gbavfx_rasterize_interlaced_even @ buffer[1] is being displayed
	ldr		r2, =.rasterizer_code
	sub		ip, ip, r2 @ 상대 위치
	sub		ip, ip, #8 @ pc 조정
	mov		ip, ip, ASR #2
	orr		ip, ip, #0xEB000000 @ bl instruction (self modifying code)
	str		ip, [r2]
	@---------------self modifying code done----------------------
	@ r0이 back 정보 뿐
	@ 0, 2, 4번은 front -> back, 1, 3, 5번은 스카이박스로 하면 총 80*2줄인데, 확신 가능한건 79 * 2줄 뿐, 뒤틀린 경우에만 추가함, 뒤틀리지 않은 경우는 마지막이 남음
	@ buffer[1]이 표시 중일 때는 홀수번째라인을 복사한다
	bne		.dma_init_odd
	@ buffer[1]을 표시 중일 때 ->
	str		r1, [lr, #0xD4] @ dma src set (skybg)
	str		r0, [lr, #0xD8] @ dma dst set (back)
	str		r3, [lr, #0xDC] @ dma control
	add		r0, r0, #240 @ back 한 줄 다음으로 이동
	add		r1, r1, #2400 @ skybg 두 줄 다음으로 이동-----------------------------------------------------------------------
	@ add		r1, r1, #480 @ skybg 두 줄 다음으로 이동
	eor		r2, r0, #0xA000 @ front == r2
	str		r2, [lr, #0xD4] @ dma src set (front)
	str		r0, [lr, #0xD8] @ dma dst set (back)
	str		r3, [lr, #0xDC] @ dma control
	add		r0, r0, #240 @ back은 한 줄 다음으로 이동
	add		r2, r2, #480 @ front는 두 줄 다음으로 이동
	@ 결과적으로 r0, r1, r2로 계속하면 됨.
	b		.dma_init_end
.dma_init_odd:
	@ buffer[0]을 표시 중일 때 ->
	eor		r2, r0, #0xA000 @ front == r2
	str		r2, [lr, #0xD4] @ dma src set (front)
	str		r0, [lr, #0xD8] @ dma dst set (back)
	str		r3, [lr, #0xDC] @ dma control
	add		r0, r0, #240 @ back 한 줄 다음으로 이동
	add		r2, r2, #480 @ front 두 줄 다음으로 이동
	add		r1, r1, #1200 @ skybg 한 줄 이동----------------------------------------------------------------------------------
	@ add		r1, r1, #240
	mov		ip, #0x9400
	add		ip, #0x0020 @ 240 * (160 - 2)
	add		r4, r0, ip @ back + 240 * (160 - 2) 마지막 줄
	str		r4, [lr, #0xD8] @ dma dst set (back)
	add		r4, r1, ip @ skybg + 960 * (160 - 2)
	str		r4, [lr, #0xD4] @ dma src set (skybg)
	str		r3, [lr, #0xDC] @ dma control
	@ 결과적으로 r0, r1, r2로 계속하면 됨.
.dma_init_end:
	mov		ip, #79
.dma_loop_begin:
	
	str		r1, [lr, #0xD4] @ dma src set (skybg)
	str		r0, [lr, #0xD8] @ dma dst set (back)
	str		r3, [lr, #0xDC] @ dma control
	add		r0, r0, #240 @ back 한 줄 다음으로 이동
	add		r1, r1, #2400 @ skybg 두 줄 다음으로 이동--------------------------------------------------------------------------
	@ add		r1, r1, #480 @ skybg 두 줄 다음으로 이동
	str		r2, [lr, #0xD4] @ dma src set (front)
	str		r0, [lr, #0xD8] @ dma dst set (back)
	str		r3, [lr, #0xDC] @ dma control
	add		r0, r0, #240 @ back은 한 줄 다음으로 이동
	add		r2, r2, #480 @ front는 두 줄 다음으로 이동

	subs	ip, ip, #1
	bne		.dma_loop_begin
.dma_loop_end:


	@----------------------
	mov		r0, #1024
	sub		r0, r0, #1
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
	push	{r2-r3}
.rasterizer_code:
	nop
	pop		{r2-r3}
	cmp		r2, #-1
	bne		.face_loop_begin
	pop		{r0, r1}
.face_loop_end:
	subs	r0, r0, #1
	bne		.depth_loop_begin
	str		r6, [r5] @ vid_page ^ 0xA000 = gbavfx_color
	
	ldr		r5, =gbavfx_vblank_counter
.vsync:
	ldrh	r4, [r5]
	cmp		r4, #2
	blt		.vsync
	mov		r4, #0
	strh	r4, [r5]

	mov		r5, #0x04000000 @ REG_DISPCNT
	ldr		r6, [r5]
	eor		r6, r6, #0x0010 @ DCNT_PAGE
	str		r6, [r5]
	pop		{r4, r5, r6, lr}
	bx		lr
	