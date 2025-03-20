
.extern _ZN5mode87contextE
.extern value


@ .L5의 beq .L11를 bne로,
@ .L4의 251번째 줄의 r14에 넣는 #0x06000000를 buffer[1]로 바꾸기
@ -> scan_1 완성

.section .iwram, "ax"
.global _ZN5mode85flushEv
_ZN5mode85flushEv:
	push	{r4-r11, lr}
	ldr		r1, =_ZN5mode87contextE @ r1 = &context (&context->ordering_table)
	add		r2, r1, #0x0C00 @ r2 = &context->ptb;
	ldr		r3, [r1, #0x0BF4] @ r3 = context->texture_slot
	mov		r4, #0x04000000 @ &REG_DISPCNT
	ldr		r4,	[r4] @ REG_DISPCNT

	@ tst		r4, #0x0010 @ check 5th bit of DISPCNT
	@ adreq	r5, .rasterize_0 @ back_buffer == buffer[1]						1
	@ adrne	r5, .rasterize_0 @ back_buffer = buffer[0]						1
	@ adr		r6, .L2 @ self_modifying_code destination					1
	@ sub		r5, r5, r6 @ relative position								1
	@ sub		r5, r5, #8 @ adjust pc										1
	@ mov		r5, r5, LSR #2 @ pack address (>> 2)						1
	@ orr		r5, r5, #0xEB000000 @ bl instruction (self modifying code)	1
	@ str		r5, [r6] @ store bl instruction								2 = 9
	tst		r4, #0x0010 @ check 5th bit of DISPCNT
	adr		r5, .L4 @ add	r14, r14, #0xA000
	ldr		r6, [r5]
	bic		r6, r6, #0xF0000000 @ add -> addeq (back_buffer == buffer[0])
	eoreq	r6, r6, #0x10000000 @ addeq -> addne (back_buffer == buffer[1])
	str		r6, [r5]

	adr		r5, .L5 @ beq	.L11
	ldr		r6, [r5]
	bic		r6, r6, #0xF0000000 @ b -> beq (back_buffer == buffer[0])
	eoreq	r6, r6, #0x10000000 @ beq -> bne (back_buffer == buffer[1])
	str		r6, [r5]

	add		r11, r0, #0x2C00 @ r11 = &context->face_buffer
	
	mov		r0, #768
	sub		r0, r0, #1 @ r0 = 767 (depth, loop variable)
.L0:
	add		r12, r1, r0, LSL #1 @ &context->ordering_table + depth * sizeof(u16)
	ldrsh	r12, [r12] @ r12 = ordering_table[depth]
	cmp		r12, #-1
	beq		.L3
	push	{r0, r1, r11}
	@ r0 = depth
	@ r1 = &context->ordering_table
	@ r2 = &context->ptb.vertex
	@ r3 = context->texture_slot
	@ r11 = &context->face_buffer
	@ r12 = face_index
.L1:
	add		r12, r11, r12, LSL #3 @ r12 = &context->face_buffer + face_idx * sizeof(face)
	ldmia	r12, {r0, r1} @ r0, r1 = *face
	mov		r12, r1, ASR #21 @ r12 = next_face
	push	{r2, r3, r12}
.L2: @ rasterizer self modying code
	@ nop
	bl		.rasterize_0
	pop		{r2, r3, r12}
	cmp		r12, #-1
	bne		.L1
	pop		{r0, r1, r11}
.L3:
	subs	r0, r0, #1
	bne		.L0
	pop		{r4-r11, lr}
	bx		lr

@ r0 = face_data[0]
@ r1 = face_data[1]
@ r2 = &context->ptb.vertex
@ r3 = context->texture_slot

@ ---------------------------------- rasterizer 0 ----------------------------------

@ buffer[0]에 그리는 코드
.rasterize_0:
	mvn		r11, #0 @ r11 = 0xFFFFFFFF
	and		r9, r0, r11, LSR #16 @ r9 = i0
	mov		r10, r0, LSR #16 @ r10 = i1
	and		r11, r1, r11, LSR #16 @ r11 = i2
	add		r9, r2, r9, LSL #3 @ r9 = &context->ptb.vertex[i0]
	add		r10, r2, r10, LSL #3 @ r10 = &context->ptb.vertex[i1]
	add		r11, r2, r11, LSL #3 @ r11 = &context->ptb.vertex[i2]
	and		r1, r1, #0x001F0000 @ r1 = texture_id << 16

	@ texture_slot + (texture_id << 2)를 구해야함!
	ldr		r12, [r3, r1, LSR #14] @ r12 = &context->texture_slot.textures[texture_id]
	ldmia	r9, {r0, r2} @ vertex 0
	ldmia	r10, {r4, r6} @ vertex 1
	ldmia	r11, {r8, r10} @ vertex 2

	@ free registers(r1, r3, r5, r7, r9, r11)
	@ used registers(r0, r2, r4, r6, r8, r10, r12(ip))
	@ r0 = (0.y + 2048 | 0.x + 2048 | 0.z)
	@ r2 = (0.u | 0.v)
	@ r4 = (1.y + 2048 | 1.x + 2048 | 1.z)
	@ r6 = (1.u | 1.v)
	@ r8 = (2.y + 2048 | 2.x + 2048 | 2.z)
	@ r10 = (2.u | 2.v)
	@ r12 = &texture_slot[texture_id];
	@ r14 = return address

	mov		r1, r0, LSL #12
	mov		r5, r4, LSL #12
	mov		r9, r8, LSL #12
	mov		r11, #2048
	rsb		r0, r11, r0, LSR #20 @ r0 = 0.x
	rsb		r1, r11, r1, LSR #20 @ r1 = 0.y
	rsb		r4, r11, r4, LSR #20 @ r4 = 1.x
	rsb		r5, r11, r5, LSR #20 @ r5 = 1.y
	rsb		r8, r11, r8, LSR #20 @ r8 = 2.x
	rsb		r9, r11, r9, LSR #20 @ r9 = 2.y

	mvn		r11, #0 @ 0xFFFFFFFF
	and		r3, r2, r11, LSR #16 @ 0.v
	and		r7, r6, r11, LSR #16 @ 1.v
	and		r11, r10, r11, LSR #16 @ 2.v
	mov		r2, r2, LSR #16 @ 0.u
	mov		r6, r6, LSR #16 @ 1.u
	mov		r10, r10, LSR #16 @ 2.u
	
	sub		r10, r10, r6 @ 2.u - 1.u
	sub		r11, r11, r7 @ 2.v - 1.v

	@ free registers()
	@ used registers(r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12(ip), r14(lr))
	@ r0 = 0.y
	@ r1 = 0.x
	@ r2 = 0.u
	@ r3 = 0.v
	@ r4 = 1.y
	@ r5 = 1.x
	@ r6 = 1.u
	@ r7 = 1.v
	@ r8 = 2.y
	@ r9 = 2.x
	@ r10 = 2.u - 1.u
	@ r11 = 2.v - 1.v
	@ r12 = &texture_slot[texture_id];
	@ r14 = return address

	push	{r0-r3, r4, r5, r8-r11, lr} @ {0.yxuv, 1.yx, 2.yx, 2.uv - 1.uv, lr}

	@ pushed 11 * 4 bytes
	sub		r4, r4, r0 @ (1.y - 0.y) = dy01
	sub		r8, r8, r0 @ (2.y - 0.y) = dy02
	sub		r5, r5, r1 @ (1.x - 0.x) = dx01
	sub		r9, r9, r1 @ (2.x - 0.x) = dx02
	mul		r0, r5, r8 @ dx01 * dy02
	mul		r1, r4, r9 @ dy01 * dx02
	sub		r0, r0, r1 @ det = dx01 * dy02 - dy01 * dx02

	@ free registers(r1, r14(lr))
	@ used registers(r0, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12(ip))
	
	@ r0 = determinant
	@ r2 = 0.u
	@ r3 = 0.v
	@ r4 = dy01
	@ r5 = dx01
	@ r6 = 1.u
	@ r7 = 1.v
	@ r8 = dy02
	@ r9 = dx02
	@ r10 = du12
	@ r11 = dv12
	@ r12 = &texture_slot[texture_id];
	sub		r2, r6, r2 @ 1.u - 0.u = du01
	sub		r3, r7, r3 @ 1.v - 0.v = dv01
	add		r10, r10, r2 @ (2.u - 1.u) + (1.u - 0.u) = du02
	add		r11, r11, r3 @ (2.v - 1.v) + (1.v - 0.v) = dv02
	mul		r1, r2, r8 @ du01 * dy02
	mul		r6, r4, r10 @ dy01 * du02
	sub		r6, r1, r6 @ du01 * dy02 - dy01 * du02 = dudx * det
	mul		r1, r3, r8 @ dv01 * dy02
	mul		r7, r4, r11 @ dy01 * dv02
	sub		r7, r1, r7 @ dv01 * dy02 - dy01 * dv02 = dvdx * det

	cmp		r0, #0
	movlt	r10, r2 @ 01이 왼쪽일 때, 02를 01의 uv로 덮어씌움 (02.uv = 01.uv)
	movlt	r11, r3
@ free registers(r1, r2, r3, r14(lr))
@ used registers(r0, r4, r5, r6, r7, r8, r9, r10, r11, r12(ip))
@ r0 = determinant
@ r4 = dy01
@ r5 = dx01
@ r6 = dudx * det (5bit fraction)
@ r7 = dvdx * det (5bit fraction)
@ r8 = dy02
@ r9 = dx02
@ r10 = du_left (5bit fraction)
@ r11 = dv_left (5bit fraction)
@ r12 = &texture_slot[texture_id];

	bl		reciprocal @ inverse(determinant) (31bit fraction)
	smull	r1, r2, r0, r6 @ dudx * det / determinant (31 * 5bit -> 36bit)
	mov		r6, r1, LSR #15 @ (21bit fraction)
	orr		r6, r6, r2, LSL #17

	smull	r1, r2, r0, r7 @ dvdx * det / determinant
	mov		r7, r1, LSR #15 @ (21bit fraction)
	orr		r7, r7, r2, LSL #17

	mov		r3, r0 @ luckily reciprocal_u16 doesn't use r3 and ip
	mov		r0, r4 @ dy01
	bl		reciprocal_u16 @ inverse(dy01)
	mov		r0, r0, ASR #15 @ (16bit fraction)
	mul		r4, r0, r5 @ dx01 / dy01
	cmp		r3, #0 @ if 01 is left
	mullt	r10, r0, r10 @ r10 = du01 / dy01
	mullt	r11, r0, r11 @ r11 = dv01 / dy01

	mov		r0, r8 @ dy02
	bl		reciprocal_u16 @ inverse(dy02)
	mov		r0, r0, ASR #15  @ (16bit fraction)
	mul		r8, r0, r9 @ dx02 / dy02, (16bit fraction)
	cmp		r3, #0 @ if 02 is left
	mulgt	r10, r0, r10 @ r10 = du02 / dy02  @ (21bit fraction)
	mulgt	r11, r0, r11 @ r11 = dv02 / dy02  @ (21bit fraction)

	pop		{r0, r1, r2, r3, r9} @ {0.yxuv, 1.y}
	sub		sp, sp, #4 @ preserve 1.y (prevent 4byte pop)
	@ popped 5 * 4bytes - 4bytes = 16 bytes
@ free registers(r5, r14(lr))
@ used registers(r0, r1, r2, r3, r4, r6, r7, r8, r9, r10, r11, r12(ip))
@ r0 = 0.y
@ r1 = 0.x
@ r2 = 0.u (5bit fraction)
@ r3 = 0.v (5bit fraction)
@ r4 = dxdy01
@ r6 = dudx (21bit fraction)
@ r7 = dvdx (21bit fraction)
@ r8 = dxdy02
@ r9 = 1.y
@ r10 = dudy_left (21bit fraction)
@ r11 = dvdy_left (21bit fraction)
@ r12 = &texture_slot[texture_id];
	bic		r5, r0, r0, ASR #31 @ max(0.y, 0);

	cmp		r9, #160
	rsble	r9, r5, r9
	rsbgt	r9, r5, #160 @ height = min(1.y, 160) - max(0.y, 0);


	sub		r14, r5, r0 @ clipped_y = max(0.y, 0) - 0.y;
	@ r5 *= 15 -> (240 = 15 * 16)
	mov		r1, r1, LSL #16 @ left_x
	add		r1, r1, #0x00FF
	add		r1, r1, #0x7F00 @ pixel center
	mov		r2, r2, LSL #16 @ left_u  @ (21bit fraction)
	mov		r3, r3, LSL #16 @ left_v  @ (21bit fraction)

	mla		r0, r8, r14, r1 @ b_x = 0.x + dxdy02 * clipped_y
	mla		r1, r4, r14, r1 @ a_x = 0.x + dxdy01 * clipped_y
	mla		r2, r10, r14, r2 @ l_u = 0.u + dudy * clipped_y
	mla		r3, r11, r14, r3 @ l_v = 0.v + dvdy * clipped_y

	movs	r14, #0x06000000 @ r14 = buffer[0], Z = 0
.L4:
	addne	r14, r14, #0x0000A000 @ 0번 초기화인 경우는 실행안됨
	add		r5, r5, r5, LSL #1 @ r5 = r5 * 3
	add		r5, r5, r5, LSL #2 @ r5 = r5 * 5
	add		r5, r14, r5, LSL #4 @ context->render_target + 240 * top


	cmp		r4, r8 @ 왼쪽 변은 01인가 02인가?
	eorlt	r0, r0, r1
	eorlt	r1, r0, r1
	eorlt	r0, r0, r1 @ 01이 왼쪽이므로 r0에 01이 가도록 스왑

	eorgt	r4, r4, r8
	eorgt	r8, r4, r8
	eorgt	r4, r4, r8 @ 02이 왼쪽이므로 r4에 02가 가도록 스왑
	mov		r9, r9, LSL #1 @ 최하위 1비트를 플래그로 사용하기 위해 << 1
	orrgt	r9, r9, #1 @ 02가 왼쪽일 때 추가 플래그 (height | flag)
@ free registers(r14(lr))
@ used registers(r0, r1, r2, r3, r4, r6, r7, r8, r9, r10, r11, r12(ip))
@ r0 = x_left
@ r1 = x_right
@ r2 = u_left (21bit fraction)
@ r3 = v_left (21bit fraction)
@ r4 = dxdy_left
@ r5 = context-> f_target + 240 * top;
@ r6 = dudx (21bit fraction)
@ r7 = dvdx (21bit fraction)
@ r8 = dxdy_right
@ r9 = (flag | height) (loop_variable)
@ r10 = dudy_left (21bit fraction)
@ r11 = dvdy_left (21bit fraction)
@ r12 = &texture_slot[texture_id];
	cmp		r9, #1 
	ble		.L13 @ skip loop if (height >> 1) <= 0
	sub		r9, r9, #2 @ 2를 미리 빼놔야 함.
	@ height가 1인 경우, 플래그에 따라 10(2) 또는 11(3)이 되는데, 둘 다 루프를 한번만 돌아야한다.
	@ subs로 2씩 뺀다고 가정했을 때, 2는 2를 빼면 0이 되지만, 3은 1이되므로 subs로 판단할 수가 없어진다.
	@ 따라서 2를 먼저 빼 놓는다.
	bl		.scan_0
.L13:
@ free registers(r14(lr))
@ used registers(r0, r1, r2, r3, r4, r6, r7, r8, r9, r10, r11, r12(ip))
@ r0 = x_left
@ r1 = x_right
@ r2 = u_left
@ r3 = v_left
@ r4 = dxdy_left
@ r5 = context->render_target + 240 * top;
@ r6 = dudx
@ r7 = dvdx
@ r8 = dxdy_right
@ r9 = (height | flag) (loop_variable)
@ r10 = dudy_left
@ r11 = dvdy_left
@ r12 = &texture_slot[texture_id];

@ 현재 스택
@ {1.yx, 2.yx, 2.uv - 1.uv, lr}
	tst		r9, #1 @ (height | flag) 의 flag를 확인
	@ flag가 1이라면 02가 왼쪽
	@ flag가 0이라면 01이 왼쪽
	bne		.L14 @ 02가 왼쪽
	pop		{r4, r10, r11} @ {1.y, 1.x, 2.y}
	push	{r1, r2}
	sub		r0, r11, r4 @ r0 = dy12
	bl		reciprocal_u16
	bic		r4, r4, r4, ASR #31 @ r4 = max(y1, 0);
	cmp		r11, #160
	rsblt	r9, r4, r11
	rsbge	r9, r4, #160 @ r9 = min(y2, 160) - max(y1, 0) (height)
	mov		r14, r0, ASR #15 @ r14 = 1/dy12
	mov		r0, r10 @ r0 = 1.x
	pop		{r1, r2, r4, r10, r11} @ {2.x, 2.uv - 1.uv}
	sub		r4, r4, r0 @ r10 = 2.x - 1.x = dx12
	mul		r4, r14, r4 @ r4 = dx12 / dy12 = dxdy12
	mul		r10, r14, r10 @ r10 = du12 / dy12 = dudy12
	mul		r11, r14, r11 @ r11 = dv12 / dy12 = dvdy12
	mov		r0, r0, LSL #16 @ r0 = x_left (to fixed point)
	add		r0, r0, #0x00FF
	add		r0, r0, #0x7F00 @ pixel center
@ 현재 스택
@ {lr}
	b		.L15
.L14: @ 02가 왼쪽인 경우
	pop		{r1, r8, r14} @ {1.y, 1.x, 2.y}
	push	{r0, r2}
	sub		r0, r14, r1 @ r0 = dy12
	bic		r9, r1, r1, ASR #31 @ r9 = max(y1, 0);
	bl		reciprocal_u16
	cmp		r14, #160
	rsblt	r9, r9, r14
	rsbge	r9, r9, #160 @ r9 = min(y2, 160) - max(y1, 0);
	mov		r14, r0, ASR #15 @ r14 = 1/dy12
	mov		r1, r8 @ r1 = 1.x
	pop		{r0, r2, r8} @ restore r0, r2 and {2.x}
	add		sp, #8 @ drop {2.uv - 1.uv}
	sub		r8, r8, r1 @ r8 = 2.x - 1.x
	mul		r8, r14, r8 @ r8 = dx12 / dy12 = dxdy12
	mov		r1, r1, LSL #16 @ r1 = x_right (to fixed point)
	add		r1, r1, #0x00FF
	add		r1, r1, #0x7F00 @ pixel center
.L15:
	mov		r9, r9, LSL #1 @ 플래그를 저장할 필요는 없지만 코드를 공유하기 위해 0을 채운다.
	cmp		r9, #0
	sub		r9, r9, #2
	ble		.L16 @ skip loop if height <= 0
	bl		.scan_0
.L16:
	pop		{pc}


.scan_0:
	str		r14, [sp, #-4]! @ store lr
.L6: @ 윗 삼각형 y 루프
	@ 렌더타겟은 무조건 0x06000000 또는 0x0600A000 이고, 한 줄이 240(0x00F0)바이트 이므로
	@ r5(현재 스캔라인의 x=0위치에서 주소)
	@ r5의 5번째 비트를 확인함으로써 현재 스캔라인이 홀수번째인지 짝수번째인지 알 수 있음.
	tst		r5, #0x10
.L5:
	bne		.L11 @ skip loop if (0, 2, 4..)th scanline
	cmp		r1, #0
	ble		.L11 @ x_right < 0

	push	{r0, r1, r2, r3, r5, r9} @ x_left, x_right, u_left, v_left, rtv, height
	mov		r14, r0, ASR #16 @ r14 = x_left_pixel
	bic		r0, r14, r14, ASR #31 @ r0 = max(x_left_pixel, 0)

	mov		r1, r1, ASR #16 @ r1 = x_right_pixel
	cmp		r1, #240
	rsble	r1, r0, r1
	rsbgt	r1, r0, #240 @ width = min(x_right_pixel, 240) - max(x_left_pixel, 0)

	cmp		r1, #0 @ width == 0
	ble		.L10
	sub		r14, r0, r14 @ r14(clipped_x) = max(x_left_pixel, 0) - x_left_pixel
	add		r5, r5, r0 @ render_target + 240 * height + max(x_left_pixel, 0)
	mla		r2, r6, r14, r2 @ u += dudx * clipped_x;
	mla		r3, r7, r14, r3 @ v += dvdx * clipped_x;

	tst		r5, #1 @ if (ptr & 1 == 1), 홀수번째 픽셀에서 시작
	beq		.L7
	and		r0, r2, #0x07E00000 @ uv의 픽셀 좌표 (21bit fraction)
	mov		r14, r0, LSR #21 @ r14 = u
	and		r0, r3, #0x07E00000 @ v의 픽셀 좌표
	orr		r14, r14, r0, LSR #15 @ r14 = (v | u)
	ldrb	r0, [r5, #-1]! @ pixel[0]
	ldrb	r14, [r12, r14] @ texture of pixel[1]
	orr		r0, r0, r14, LSL #8 @ (texture[uv] << 8 | pixel[0])
	strh	r0, [r5], #2 @ pixels[i] = (pixel[0] | texture[uv] << 8);
	add		r2, r2, r6 @ u += dudx;
	add		r3, r3, r7 @ v += dvdx;
	sub		r1, r1, #1 @ width -= 1;
.L7:
	tst		r1, #1 @ 홀수 마지막 픽셀
	beq		.L8 @ skip if (width & 1 == 0)
	ldrb	r9, [r5, r1] @ r9 = ptr[width]
	sub		r1, r1, #1 @ width -= 1
	mla		r14, r1, r6, r2 @ pixel_u = (width - 1) * dudx + u
	mla		r0, r1, r7, r3 @ pixel_v = (width - 1) * dvdx + v
	and		r14, r14, #0x07E00000 @ u의 픽셀좌표
	mov		r14, r14, LSR #21
	and		r0, r0, #0x07E00000 @ v의 픽셀좌표
	orr		r14, r14, r0, LSR #15 @ uv
	ldrb	r14, [r12, r14] @ texture[uv]
	orr		r14, r14, r9, LSL #8 @ (texture[uv] | ptr[width] << 8)
	strh	r14, [r5, r1] @ *(ptr + width - 1) = (texture[uv] | ptr[width] << 8);
.L8:
	cmp		r1, #0
	ble		.L10 @ skip loop if (width < 0)
.L9:
	and		r0, r2, #0x07E00000 @ calculate u
	and		r9, r3, #0x07E00000 @ calculate v
	mov		r0, r0, LSR #21 @ u
	orr		r0, r0, r9, LSR #15 @ (v << 6 | u)
	ldrb	r0, [r12, r0] @ texture(uv)
	add		r2, r2, r6 @ u += dudx
	add		r3, r3, r7 @ v += dvdx
	and		r9, r2, #0x07E00000 @ calculate u
	and		r14, r3, #0x07E00000 @ calculate v
	mov		r9, r9, LSR #21 @ r9 = u
	orr		r9, r9, r14, LSR #15 @ (v << 6 | u)
	ldrb	r9, [r12, r9]
	orr		r0, r0, r9, LSL #8
	add		r2, r2, r6 @ u += dudx
	add		r3, r3, r7 @ v += dvdx
	strh	r0, [r5], #2 @ *ptr = color; ptr += 2
	subs	r1, r1, #2 @ width -= 2
	bne		.L9 @ x loop
.L10:
	pop		{r0, r1, r2, r3, r5, r9}
.L11:
	add		r5, r5, #240 @ base += 240
	add		r0, r0, r4 @ x_left += dxdy_left
	add		r1, r1, r8 @ x_right += dxdy_right
	add		r2, r2, r10 @ u_left += dudy_left
	add		r3, r3, r11 @ v_left += dvdy_left
	subs	r9, r9, #2 @ height -= 1, 2를 뺏을 때, 1보다 작으면 루프 탈출
	bgt		.L6
.L12:
	pop		{pc}