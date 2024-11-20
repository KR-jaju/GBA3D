
@a_x, b_x, l_u, l_v, l_du, l_dv, a_dx, b_dx - y단
@dudx, dvdx, clipped_x, ptr, left, width, uv, color, color_id - x단
.extern gbavfx_vbo
.extern gbavfx_texture_slot
.extern gbavfx_color

.section .iwram, "ax"
.global gbavfx_rasterize_interlaced_odd
gbavfx_rasterize_interlaced_odd:
	push	{r4-r11, lr}
	mov		lr, #0xFFFFFFFF
	ldr		ip, =gbavfx_vbo
	and		r2, r0, lr, LSR #16 @0번 정점의 인덱스
	mov		r3, r0, LSR #16 @1번 정점의 인덱스
	and		r4, r1, lr, LSR #16 @2번 정점의 인덱스
	add		r2, ip, r2, LSL #3 @0번 정점의 주소
	add		r3, ip, r3, LSL #3 @1번 정점의 주소
	add		r4, ip, r4, LSL #3 @2번 정점의 주소
	and		r1, r1, #0x001F0000
	ldr		ip, =gbavfx_texture_slot
	add		ip, ip, r1, LSR #4 @ 텍스쳐 슬롯 주소
	ldmia	r2, {r0, r1} @ a, b of 0
	ldmia	r3, {r2, r3} @ a, b of 1
	ldmia	r4, {r4, r5} @ a, b of 2
	mov		r7, r1, LSR #16 @ u of 0
	mov		r9, r3, LSR #16 @ u of 1
	mov		r11, r5, LSR #16 @ u of 2
	and		r1, r1, lr, LSR #16
	and		r3, r3, lr, LSR #16
	and		r5, r5, lr, LSR #16

	mov		lr, #32768
	rsb		r6, lr, r0, LSR #16 @ y of 0
	rsb		r8, lr, r2, LSR #16 @ y of 1
	rsb		r10, lr, r4, LSR #16 @ y of 2
	mov		r0, r0, LSL #16
	mov		r2, r2, LSL #16
	mov		r4, r4, LSL #16
	rsb		r0, lr, r0, LSR #16
	rsb		r2, lr, r2, LSR #16
	rsb		r4, lr, r4, LSR #16
	sub		r11, r11, r9 @ 2.u - 1.u 
	sub		lr, r5, r3 @ 2.v - 1.v
	push	{r2, r4, r8, r10, r11, lr} @ {x1, x2, y1, y2, du, dv}

	push	{r0, r1, r6, r7, r8} @ {0.x, 0.v, 0.y, 0.u, 1.y}
	sub		r2, r2, r0 @ (1.x - 0.x) = dx01
	sub		r4, r4, r0
	sub		r8, r8, r6 @ 1.y - 0.y = dy01
	sub		r10, r10, r6 @ 2.y - 0.y = dy02
	mul		r0, r2, r10 @ a * d
	mul		r6, r4, r8 @ b * c
	sub		r0, r0, r6 @ det = a * d - b * c

	cmp		r0, #0 @ det과 0 비교, 음수면 01이 왼쪽, 양수면 02가 왼쪽
	addeq	sp, sp, #44 @ 44바이트 날림
	beq		.end_of_function @ return if (det == 0)
	@------------------determinant 계산 완료---------------------
	sub		r9, r9, r7 @ 1.u - 0.u = du01
	add		r11, r9, r11 @ 2.u - 0.u
	sub		r3, r3, r1 @ 1.v - 0.v = dv01
	sub		r5, r5, r1 @ 2.v - 0.v = dv02
	mul		r6, r9, r10 @ du01 * dy02
	mul		r1, r11, r8 @ du02 * dy01
	sub		r6, r6, r1 @ du01 * dy02 - du02 * dy01 = dudx * det
	mul		r1, r3, r10 @ dv01 * dy02
	mul		r7, r5, r8 @ dv02 * dy01
	sub		r7, r1, r7 @ dv01 * dy02 - dv02 * dy01 = dvdx * det
	@ 2.x
	@ 1.x
	@ 2.y
	@ 1.y
	@ 2.uv - 1.uv
	@ 총 5개
	@------------------du,dv 계산 완료---------------------------
	@ inv_det, inv_ah, inv_bh,adx,bdx,ldu,ldv, dudx,dvdx 를 계산해야함, r0, r3, r5, r9, r11을 살려야함
	@ 총 14개
	@ r11, r5 (uv)
	@ r9, r4 (adx,bdx)
	@ r0 (det)
	@ r10, r8 (ah, bh)
	@ r6, r7(dudx,dvdx)

	movlt	r5, r3 @ v dv01
	movlt	r11, r9 @ u 01이 왼쪽일 때 02를 덮어씌움

	mov		r9, r2 @ dx01을 r9으로 옮김

	bl		reciprocal @ inv_det 계산
	smull	r1, r2, r0, r6
	mov		r6, r1, LSR #15 @ 낮은 자리 32비트
	orr		r6, r6, r2, LSL #17 @dudx
	
	smull	r1, r2, r0, r7
	mov		r7, r1, LSR #15
	orr		r7, r7, r2, LSL #17 @dvdx

	cmp		r0, #0 @ inv_det ?
	mrs		r3, cpsr @ luckily reciprocal_u16 doesn't use r3 and ip

	mov		r0, r8 @ a_dy
	bl		reciprocal_u16 @ inv_dy 계산
	mov		r0, r0, ASR #15
	msr		cpsr, r3 @ reload
	mul		r8, r0, r9 @ a(dx/dy)
	mullt	r9, r0, r5 @ dv/dy
	mullt	r11, r0, r11 @ du/dy

	mov		r0, r10 @ b_dy
	bl		reciprocal_u16 @ inv_dy 계산
	mov		r0, r0, ASR #15
	msr		cpsr, r3 @ reload
	mul		r10, r0, r4 @ b(dx/dy)
	mulgt	r9, r0, r5 @ dv/dy
	mulgt	r11, r0, r11 @ du/dy

	@-------------------------초기화 완료-----------------------
	pop		{r0, r1, r2, r3, r4} @ r4가 1.y라고 가정 // 49번줄과 대응됨
	bic		r5, r2, r2, ASR #31 @ top

	cmp		r4, #160
	rsble	r4, r5, r4
	rsbgt	r4, r5, #160 @ height

	sub		lr, r5, r2 @ clipped_y

	mov		r2, #240
	mul		r5, r2, r5 @ r5 = 240 * r5
	ldr		r2, =gbavfx_color
	ldr		r2, [r2]
	add		r5, r2, r5 @ gbavfx_color += top * 240
	mov		r0, r0, LSL #16
	mov		r1, r1, LSL #16
	mov		r3, r3, LSL #16
	mla		r2, r10, lr, r0 @ b_x += dx02 * clipped_y
	mla		r0, r8, lr, r0 @ a_x += dx01 * clipped_y
	mla		r1, r9, lr, r1 @ l_v += dv * clipped_y
	mla		r3, r11, lr, r3 @ l_u += du * clipped_y
	@-----------------------stm으로 수정한 것들 저장하기----------------
	cmp		r8, r10 @ which side is v1 on?
	bge		.case_r
	cmp		r4, #0 @ height == 0
	ble		.l_high_y_loop_end_1
.l_high_y_loop_begin: @ while문 시작 r0-r5, r8
	tst		r5, #0x10 @ check if even scanline
	beq		.l_high_y_loop_end_2
	push	{r0, r2} @ a_x,b_x,l_u,l_v, height, base, ddy----texture도 옮길 수 있으면 옮기기
	mov		lr, r0, ASR #16 @ a_x >>= 16
	bic		r0, lr, lr, ASR #31
	
	mov		r2, r2, ASR #16 @ b_x >>= 16
	cmp		r2, #240
	rsble	r2, r0, r2
	rsbgt	r2, r0, #240

	cmp		r2, #0
	ble		.l_high_y_loop_end_0 @ if (width <= 0) continue;
	push	{r1, r3-r5}
	sub		lr, r0, lr @ clipped_x = left - a_x
	add		r5, r5, r0 @ ptr = base + left
	mla		r3, r6, lr, r3 @ u += dudx * clipped_x;
	mla		r1, r7, lr, r1 @ v += dvdx * clipped_x;

	tst		r5, #1	@if (intptr_t(ptr) & 1)
	beq		.l_high_odd_pixel_end_0
	and		r0, r3, #0x003F0000
	mov		lr, r0, LSR #16
	and		r0, r1, #0x003F0000
	orr		lr, lr, r0, LSR #10 @ uv
	ldrb	r0, [r5, #-1]!
	ldrb	lr, [ip, lr]
	orr		r0, r0, lr, LSL #8 @ (*ptr | texture[uv] << 8)
	strh	r0, [r5], #2 @ *(u16*)ptr = (*ptr | texture[uv] << 8); ptr += 2
	add		r3, r3, r6
	add		r1, r1, r7
	sub		r2, r2, #1 @ width -= 1;
.l_high_odd_pixel_end_0:
	tst		r2, #1 @ if (width & 1) 홀수인 경우만 들어옴
	beq		.l_high_odd_pixel_end_1
	ldrb	r4, [r5, r2] @ r4 = ptr[width]
	sub		r2, r2, #1 @ width - 1
	mla		lr, r2, r6, r3 @ (width - 1) * dudx + u
	mla		r0, r2, r7, r1 @ (width - 1) * dvdx + v
	and		lr, lr, #0x003F0000
	mov		lr, lr, LSR #16
	and		r0, r0, #0x003F0000
	orr		lr, lr, r0, LSR #10 @ uv
	ldrb	lr, [ip, lr] @ texture[uv]
	orr		lr, lr, r4, LSL #8 @ptr[width] << 8 | texture[uv]
	strh	lr, [r5, r2] @ *(ptr + width - 1) = 
.l_high_odd_pixel_end_1:
	cmp		r2, #0
	ble		.l_high_x_loop_end @ while (width--)
.l_high_x_loop_begin:
	and		r0, r3, #0x003F0000
	and		r4, r1, #0x003F0000
	mov		r0, r0, LSR #16
	orr		r0, r0, r4, LSR #10 @ uv
	ldrb	r0, [ip, r0] @ texture[uv]
	add		r3, r3, r6 @ u += dudx
	add		r1, r1, r7 @ v += dvdx
	and		r4, r3, #0x003F0000
	and		lr, r1, #0x003F0000
	mov		r4, r4, LSR #16
	orr		r4, r4, lr, LSR #10 @ uv
	ldrb	r4, [ip, r4] @ texture[uv]
	orr		r0, r0, r4, LSL #8 @ color |= texture[uv]
	add		r3, r3, r6 @ u += dudx
	add		r1, r1, r7 @ v += dvdx
	strh	r0, [r5], #2 @ *ptr = color; ptr += 2
	subs	r2, r2, #2 @ width -= 2
	bne		.l_high_x_loop_begin
	@----------------------
.l_high_x_loop_end:
	pop		{r1, r3-r5}
.l_high_y_loop_end_0: @ while 문 끝
	pop		{r0, r2} @ 159번과 대응됨
.l_high_y_loop_end_2:
	add		r5, r5, #240 @ base += 240
	add		r0, r0, r8 @ ax += a_dx
	add		r2, r2, r10 @ bx += b_dx
	add		r1, r1, r9 @ lv += dvdy--------------------------------
	add		r3, r3, r11 @ lu += dudy
	subs	r4, r4, #1 @ height -= 1
	bne		.l_high_y_loop_begin
.l_high_y_loop_end_1:
	@ pop		{r0, r4, r8, r9, r11, lr} @ {x1, x2, y1, y2, du, dv}
	pop		{r0, r4, r8, r9, r11} @ {x1, x2, y1, y2, du, dv}
	push	{r0-r2}
	sub		r0, r9, r8 @ reciprocal(dy)
	bl		reciprocal_u16
	bic		r8, r8, r8, ASR #31 @ max(y1, 0)
	cmp		r9, #160
	rsblt	r9, r8, r9
	rsbge	r9, r8, #160 @ height(r9) min(y2, 160) - max(y1, 0)
	mov		r8, r0, ASR #15 @ inv dy-----------------
	pop		{r0-r2, lr}
	sub		r4, r4, r0 @ dx12(r4)
	mul		r4, r8, r4 @ a_dx(r4)
	mul		r11, r8, r11 @ l_du(r11) inv_dy
	mul		lr, r8, lr @ l_dv(lr) inv_dy
	mov		r0, r0, LSL #16 @ a_x = x1 << 16; to f32 point
@------------------------------------------------------------------------------
@------------------------------------------------------------------------------
@------------------------------------------------------------------------------
@------------------------------------------------------------------------------

	cmp		r9, #0 @ height == 0
	ble		.l_low_y_loop_end_1
.l_low_y_loop_begin:
	tst		r5, #0x10 @ check if even scanline
	beq		.l_low_y_loop_end_2
	push	{r0, r2}
	mov		r8, r0, ASR #16 @ a_x >>= 16
	bic		r0, r8, r8, ASR #31 @ left
	
	mov		r2, r2, ASR #16 @ b_x >>= 16
	cmp		r2, #240
	rsble	r2, r0, r2
	rsbgt	r2, r0, #240 @ width

	cmp		r2, #0
	ble		.l_low_y_loop_end_0 @ if (width <= 0) continue;
	push	{r1, r3, r5, r9} @ lv, lu, base, height
	sub		r8, r0, r8 @ clipped_x = left - a_x
	add		r5, r5, r0 @ ptr = base + left
	mla		r3, r6, r8, r3 @ u += dudx * clipped_x;
	mla		r1, r7, r8, r1 @ v += dvdx * clipped_x;

 
 	tst		r5, #1	@if (intptr_t(ptr) & 1)
	beq		.l_low_odd_pixel_end_0
	and		r0, r3, #0x003F0000
	mov		r8, r0, LSR #16
	and		r0, r1, #0x003F0000
	orr		r8, r8, r0, LSR #10 @ uv
	ldrb	r0, [r5, #-1]!
	ldrb	r8, [ip, r8]
	orr		r0, r0, r8, LSL #8 @ (*ptr | texture[uv] << 8)
	strh	r0, [r5], #2 @ *(u16*)ptr = (*ptr | texture[uv] << 8); ptr += 2
	add		r3, r3, r6
	add		r1, r1, r7
	sub		r2, r2, #1 @ width -= 1;
.l_low_odd_pixel_end_0:
	tst		r2, #1 @ if (width & 1) 홀수인 경우만 들어옴
	beq		.l_low_odd_pixel_end_1
	ldrb	r9, [r5, r2] @ r9 = ptr[width]
	sub		r2, r2, #1 @ width - 1
	mla		r8, r2, r6, r3 @ (width - 1) * dudx + u
	mla		r0, r2, r7, r1 @ (width - 1) * dvdx + v
	and		r8, r8, #0x003F0000
	mov		r8, r8, LSR #16
	and		r0, r0, #0x003F0000
	orr		r8, r8, r0, LSR #10 @ uv
	ldrb	r8, [ip, r8] @ texture[uv]
	orr		r8, r8, r9, LSL #8 @ptr[width] << 8 | texture[uv]
	strh	r8, [r5, r2] @ *(ptr + width - 1) = 
.l_low_odd_pixel_end_1:
	cmp		r2, #0
	ble		.l_low_x_loop_end @ while (width--)
.l_low_x_loop_begin:
	and		r0, r3, #0x003F0000
	and		r9, r1, #0x003F0000
	mov		r0, r0, LSR #16
	orr		r0, r0, r9, LSR #10 @ uv
	ldrb	r0, [ip, r0] @ texture[uv]
	add		r3, r3, r6 @ u += dudx
	add		r1, r1, r7 @ v += dvdx
	and		r9, r3, #0x003F0000
	and		r8, r1, #0x003F0000
	mov		r9, r9, LSR #16
	orr		r9, r9, r8, LSR #10 @ uv
	ldrb	r9, [ip, r9] @ texture[uv]
	orr		r0, r0, r9, LSL #8 @ color |= texture[uv]
	add		r3, r3, r6 @ u += dudx
	add		r1, r1, r7 @ v += dvdx
	strh	r0, [r5], #2 @ *ptr = color; ptr += 2
	subs	r2, r2, #2 @ width -= 2
	bgt		.l_low_x_loop_begin
	@----------------------
.l_low_x_loop_end:
	pop		{r1, r3, r5, r9}
.l_low_y_loop_end_0: @ while 문 끝
	pop		{r0, r2} @ 159번과 대응됨
.l_low_y_loop_end_2:
	add		r5, r5, #240 @ base += 240
	add		r0, r0, r4 @ ax += a_dx
	add		r2, r2, r10 @ bx += b_dx
	add		r3, r3, r11 @ lu += dudy
	add		r1, r1, lr @ lv += dvdy
	subs	r9, r9, #1 @ height -= 1
	bgt		.l_low_y_loop_begin
.l_low_y_loop_end_1:
	b		.end_of_function @ v1 on left side end


@------------------------ RIGHT EDGE TRIANGLE
.case_r:
	cmp		r4, #0 @ height == 0
	ble		.r_high_y_loop_end_1
.r_high_y_loop_begin: @ while문 시작 r0-r5, r8
	tst		r5, #0x10 @ check if even scanline
	beq		.r_high_y_loop_end_2
	push	{r0, r2} @ a_x,b_x,l_u,l_v, height, base, ddy----texture도 옮길 수 있으면 옮기기
	mov		lr, r2, ASR #16 @ b_x >>= 16
	bic		r2, lr, lr, ASR #31 @ left
	
	mov		r0, r0, ASR #16 @ a_x >>= 16
	cmp		r0, #240
	rsble	r0, r2, r0
	rsbgt	r0, r2, #240 @ width

	cmp		r0, #0
	ble		.r_high_y_loop_end_0 @ if (width <= 0) continue;
	push	{r1, r3-r5}
	sub		lr, r2, lr @ clipped_x = left - a_x
	add		r5, r5, r2 @ ptr = base + left
	mla		r3, r6, lr, r3 @ u += dudx * clipped_x;
	mla		r1, r7, lr, r1 @ v += dvdx * clipped_x;

	tst		r5, #1	@if (intptr_t(ptr) & 1)
	beq		.r_high_odd_pixel_end_0
	and		r2, r3, #0x003F0000
	mov		lr, r2, LSR #16
	and		r2, r1, #0x003F0000
	orr		lr, lr, r2, LSR #10 @ uv
	ldrb	r2, [r5, #-1]!
	ldrb	lr, [ip, lr]
	orr		r2, r2, lr, LSL #8 @ (*ptr | texture[uv] << 8)
	strh	r2, [r5], #2 @ *(u16*)ptr = (*ptr | texture[uv] << 8); ptr += 2
	add		r3, r3, r6
	add		r1, r1, r7
	sub		r0, r0, #1 @ width -= 1;
.r_high_odd_pixel_end_0:
	tst		r0, #1 @ if (width & 1) 홀수인 경우만 들어옴
	beq		.r_high_odd_pixel_end_1
	ldrb	r4, [r5, r0] @ r4 = ptr[width]
	sub		r0, r0, #1 @ width - 1
	mla		lr, r0, r6, r3 @ (width - 1) * dudx + u
	mla		r2, r0, r7, r1 @ (width - 1) * dvdx + v
	and		lr, lr, #0x003F0000
	mov		lr, lr, LSR #16
	and		r2, r2, #0x003F0000
	orr		lr, lr, r2, LSR #10 @ uv
	ldrb	lr, [ip, lr] @ texture[uv]
	orr		lr, lr, r4, LSL #8 @ptr[width] << 8 | texture[uv]
	strh	lr, [r5, r0] @ *(ptr + width - 1) = 
.r_high_odd_pixel_end_1:
	cmp		r0, #0
	ble		.r_high_x_loop_end @ while (width--)
.r_high_x_loop_begin:
	and		r2, r3, #0x003F0000
	and		r4, r1, #0x003F0000
	mov		r2, r2, LSR #16
	orr		r2, r2, r4, LSR #10 @ uv
	ldrb	r2, [ip, r2] @ texture[uv]
	add		r3, r3, r6 @ u += dudx
	add		r1, r1, r7 @ v += dvdx
	and		r4, r3, #0x003F0000
	and		lr, r1, #0x003F0000
	mov		r4, r4, LSR #16
	orr		r4, r4, lr, LSR #10 @ uv
	ldrb	r4, [ip, r4] @ texture[uv]
	orr		r2, r2, r4, LSL #8 @ color |= texture[uv]
	add		r3, r3, r6 @ u += dudx
	add		r1, r1, r7 @ v += dvdx
	strh	r2, [r5], #2 @ *ptr = color; ptr += 2
	subs	r0, r0, #2 @ width -= 2
	bne		.r_high_x_loop_begin
	@----------------------
.r_high_x_loop_end:
	pop		{r1, r3-r5}
.r_high_y_loop_end_0: @ while 문 끝
	pop		{r0, r2} @ 159번과 대응됨
.r_high_y_loop_end_2:
	add		r5, r5, #240 @ base += 240
	add		r0, r0, r8 @ ax += a_dx
	add		r2, r2, r10 @ bx += b_dx
	add		r1, r1, r9 @ lv += dvdy
	add		r3, r3, r11 @ lu += dudy
	subs	r4, r4, #1 @ height -= 1
	bne		.r_high_y_loop_begin
.r_high_y_loop_end_1:
	@ pop		{r0, r4, r8, r9, r11, lr} @ {x1, x2, y1, y2, du, dv}
	add		sp, sp, #4 @ x1 받아오기 스킵
	pop		{r4, r8, lr} @ {x2, y1, y2}
	push	{r1-r3}
	sub		sp, sp, #4 @ x1 받을 수 있게하기
	mov		r3, lr
	sub		r0, r3, r8 @ reciprocal(dy)
	bl		reciprocal_u16
	bic		r8, r8, r8, ASR #31 @ max(y1, 0)
	cmp		r3, #160
	rsblt	lr, r8, r3
	rsbge	lr, r8, #160 @ height(lr) min(y2, 160) - max(y1, 0)
	mov		r8, r0, ASR #15 @ inv dy-----------------
	pop		{r0-r3}
	add		sp, sp, #8
	sub		r4, r4, r0 @ dx12(r4)
	mul		r4, r8, r4 @ a_dx(r4)
	mov		r0, r0, LSL #16 @ a_x = x1 << 16; to f32 point
@------------------------------------------------------------------------------
@------------------------------------------------------------------------------
@------------------------------------------------------------------------------
@------------------------------------------------------------------------------

	cmp		lr, #0 @ height <= 0
	ble		.r_low_y_loop_end_1
.r_low_y_loop_begin:
	tst		r5, #0x10 @ check if even scanline
	beq		.r_low_y_loop_end_2
	push	{r0, r2}
	mov		r8, r2, ASR #16 @ a_x >>= 16
	bic		r2, r8, r8, ASR #31 @ left
	
	mov		r0, r0, ASR #16 @ b_x >>= 16
	cmp		r0, #240
	rsble	r0, r2, r0
	rsbgt	r0, r2, #240 @ width

	cmp		r0, #0
	ble		.r_low_y_loop_end_0 @ if (width <= 0) continue;
	push	{r1, r3, r5, lr} @ lv, lu, base, height
	sub		r8, r2, r8 @ clipped_x = left - a_x
	add		r5, r5, r2 @ ptr = base + left
	mla		r3, r6, r8, r3 @ u += dudx * clipped_x;
	mla		r1, r7, r8, r1 @ v += dvdx * clipped_x;

 
 	tst		r5, #1	@if (intptr_t(ptr) & 1)
	beq		.r_low_odd_pixel_end_0
	and		r2, r3, #0x003F0000
	mov		r8, r2, LSR #16
	and		r2, r1, #0x003F0000
	orr		r8, r8, r2, LSR #10 @ uv
	ldrb	r2, [r5, #-1]!
	ldrb	r8, [ip, r8]
	orr		r2, r2, r8, LSL #8 @ (*ptr | texture[uv] << 8)
	strh	r2, [r5], #2 @ *(u16*)ptr = (*ptr | texture[uv] << 8); ptr += 2
	add		r3, r3, r6
	add		r1, r1, r7
	sub		r0, r0, #1 @ width -= 1;
.r_low_odd_pixel_end_0:
	tst		r0, #1 @ if (width & 1) 홀수인 경우만 들어옴
	beq		.r_low_odd_pixel_end_1
	ldrb	lr, [r5, r0] @ lr = ptr[width]
	sub		r0, r0, #1 @ width - 1
	mla		r8, r0, r6, r3 @ (width - 1) * dudx + u
	mla		r2, r0, r7, r1 @ (width - 1) * dvdx + v
	and		r8, r8, #0x003F0000
	mov		r8, r8, LSR #16
	and		r2, r2, #0x003F0000
	orr		r8, r8, r2, LSR #10 @ uv
	ldrb	r8, [ip, r8] @ texture[uv]
	orr		r8, r8, lr, LSL #8 @ptr[width] << 8 | texture[uv]
	strh	r8, [r5, r0] @ *(ptr + width - 1) = 
.r_low_odd_pixel_end_1:
	cmp		r0, #0
	ble		.r_low_x_loop_end @ while (width--)
.r_low_x_loop_begin:
	and		r2, r3, #0x003F0000
	and		lr, r1, #0x003F0000
	mov		r2, r2, LSR #16
	orr		r2, r2, lr, LSR #10 @ uv
	ldrb	r2, [ip, r2] @ texture[uv]
	add		r3, r3, r6 @ u += dudx
	add		r1, r1, r7 @ v += dvdx
	and		lr, r3, #0x003F0000
	and		r8, r1, #0x003F0000
	mov		lr, lr, LSR #16
	orr		lr, lr, r8, LSR #10 @ uv
	ldrb	lr, [ip, lr] @ texture[uv]
	orr		r2, r2, lr, LSL #8 @ color |= texture[uv]
	add		r3, r3, r6 @ u += dudx
	add		r1, r1, r7 @ v += dvdx
	strh	r2, [r5], #2 @ *ptr = color; ptr += 2
	subs	r0, r0, #2 @ width -= 2
	bgt		.r_low_x_loop_begin
	@----------------------
.r_low_x_loop_end:
	pop		{r1, r3, r5, lr}
.r_low_y_loop_end_0: @ while 문 끝
	pop		{r0, r2} @ 159번과 대응됨
.r_low_y_loop_end_2:
	add		r5, r5, #240 @ base += 240
	add		r0, r0, r4 @ ax += a_dx
	add		r2, r2, r10 @ bx += b_dx
	add		r1, r1, r9 @ lv += dvdy
	add		r3, r3, r11 @ lu += dudy
	subs	lr, lr, #1 @ height -= 1
	bgt		.r_low_y_loop_begin
.r_low_y_loop_end_1:
.end_of_function:
	pop		{r4-r11, lr} @ 10번 줄과 대응됨
	bx		lr