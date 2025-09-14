.extern _ZN5mode87contextE
.extern value

@

.section .iwram, "ax"
.global _ZN5mode85renderEv
_ZN5mode85renderEv:
	push	{r4-r11, lr}
	ldr		r1, =_ZN5mode87contextE @ r1 = &context (&context->ordering_table)
	add		r2, r1, #0x0C00 @ r2 = &context->ptb;
	ldr		r3, =_ZN5mode88texturesE @ r3 = &mode8::textures
	mov		r4, #0x04000000 @ &REG_DISPCNT
	ldr		r4,	[r4] @ REG_DISPCNT

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

	add		r11, r1, #0x2C00 @ r11 = &context->face_buffer
	
	mov		r0, #768
	sub		r0, r0, #1 @ r0 = 767 (depth, loop variable)
.L0:
	add		r12, r1, r0, LSL #1 @ &context->ordering_table + depth * sizeof(u16)
	ldrh	r12, [r12] @ r12 = ordering_table[depth]
	sub		r12, r12, #0x0700
	cmp		r12, #0x00FF
	add		r12, r12, #0x0700
	bge		.L3 @ next_face가 2047 이상이면 루프 스킵
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
	mov		r12, r0, LSR #21 @ r12 = next_face
	push	{r2, r3, r11, r12}
.L2:
	@ r0 = face_data[0]
	@ r1 = face_data[1]
	@ r2 = &context->ptb.vertex
	@ r3 = context->texture_slot
	@ r11 = &context->face_buffer
	@ r12 = next_face


	bl		.rasterize
	pop		{r2, r3, r11, r12}
	sub		r12, r12, #0x0700
	cmp		r12, #0x00FF
	add		r12, r12, #0x0700
	blt		.L1 @ 2047미만이라면 계속 루프
	pop		{r0, r1, r11}
.L3:
	subs	r0, r0, #1
	bge		.L0
	pop		{r4-r11, pc}

@ r0 = face_data[0]
@ r1 = face_data[1]
@ r2 = &context->ptb.vertex
@ r3 = context->texture_slot

@ triangle_aabb (x_min, x_max, y_min, y_max)
@ tile_area (x_min, x_max, y_min, y_max)
.rasterize:
	mvn		r11, #0 @ r11 = 0xFFFFFFFF
	and		r6, r0, r11, LSR #16 @ r6 = i0
	mov		r7, r1, LSR #16 @ r7 = i1
	and		r8, r1, r11, LSR #16 @ r8 = i2

	add		r6, r2, r6, LSL #3 @ r6 = &context->ptb.vertex[i0]
	add		r7, r2, r7, LSL #3 @ r7 = &context->ptb.vertex[i1]
	add		r8, r2, r8, LSL #3 @ r8 = &context->ptb.vertex[i2]
	and		r1, r0, #0x001F0000 @ r1 = texture_id << 16
	add		r12, r3, r1, LSR #4 @ r12 = &textures[texture_id]

	ldmia	r6, {r0, r9} @ vertex 0
	ldmia	r7, {r2, r10} @ vertex 1
	ldmia	r8, {r4, r11} @ vertex 2

	@ free registers(r1, r3, r5, r7, r9, r11)
	@ used registers(r0, r2, r4, r6, r8, r10, r12(ip))
	@ r0 = (0.y + 2048 | 0.x + 2048 | 0.z)
	@ r2 = (1.y + 2048 | 1.x + 2048 | 1.z)
	@ r4 = (2.y + 2048 | 2.x + 2048 | 2.z)

	@ r9 = (0.u | 0.v)
	@ r10 = (1.u | 1.v)
	@ r11 = (2.u | 2.v)
	@ r12 = &texture_slot[texture_id];
	@ r14 = return address

	push	{r9, r10, r11} @ 일단 스택에 저장

	mov		r7, #0x0000FFF
	mov		r8, #2048
	and		r1, r7, r0, LSR #8 @ r1 = 0.y + 2048
	and		r3, r7, r2, LSR #8 @ r3 = 1.y + 2048
	and		r5, r7, r4, LSR #8 @ r5 = 2.y + 2048
	rsb		r0, r8, r0, LSR #20 @ r0 = 0.y
	rsb		r1, r8, r1, LSR #20 @ r1 = 0.x
	rsb		r2, r8, r2, LSR #20 @ r2 = 1.y
	rsb		r3, r8, r3, LSR #20 @ r3 = 1.x
	rsb		r4, r8, r4, LSR #20 @ r4 = 2.y
	rsb		r5, r8, r5, LSR #20 @ r5 = 2.x

@ r9, r10 -> min_x, min_y
@ r11 -> width

@ r0 ~ r5까지는 x, y 좌표
@ r9 ~ r11까지는 u, v 좌표
@ r12은 텍스쳐 포인터
@ 빈 레지스터는 r6, r7, r8, r9, r10, r11


@ 반시계 방향이 앞
@ 0, 1, 2
@ (01 x 02)
@ ((x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0))
@ 0, 1, O
@ O, 0, 1
@ E0 = v0, v1, 원점이 만드는 삼각형의 행렬식 = x0 * y1 - y0 * x1
@ E1 = v2, v0, 원점이 만드는 삼각형의 행렬식 = x2 * y0 - y2 * x0
@ dE0dx = y1 - y0
@ dE0dy = x0 - x1
@ dE1dx = y0 - y2
@ dE1dy = x2 - x0
@ determinant = dE0dy * dE1dx - dE0dx * dE1dy
@ (x0-x1) * (y0-y2) - (y1 - y0) * (x2 - x0)


	dE0dx	.req r0
	dE0dy	.req r1
	E0		.req r2
	dE1dx	.req r4
	dE1dy	.req r5
	E1		.req r6
	determinant	.req r7

	mul		r6, r5, r0 @ r6 = x2 * y0
	mul		r7, r4, r1 @ r7 = y2 * x0
	sub		E1, r6, r7
	mul		r7, r1, r2 @ r7 = x0 * y1
	mul		r8, r0, r3 @ r8 = y0 * x1
	sub		dE1dx, r0, r4 @ dE1dx = y0 - y2 (5,6,7,8)
	sub		dE1dy, r5, r1 @ dE1dy = x2 - x0 (4,5,6,7,8)
	sub		dE0dx, r2, r0 @ dE0dx = y1 - y0 (0,2,4,5,6,7,8)
	sub		dE0dy, r1, r3 @ dE0dy = x0 - x1 (0,1,2,3,4,5,6,7,8)

@ min_x, y가 타일 (0, 0) 기준으로 정의돼야함!
	sub		E0, r7, r8
	mla		E0, dE0dx, r10, E0 @ E0 += dE0dx * min_x
	mla		E0, dE0dy, r11, E0 @ E0 += dE0dy * min_y
	mla		E1, dE1dx, r10, E1 @ E1 += dE1dx * min_x
	mla		E1, dE1dy, r11, E1 @ E1 += dE1dy * min_y
	mul		r7, dE0dy, dE1dx
	mul		r8, dE0dx, dE1dy
	sub		determinant, r7, r8 @ determinant

	@ E0 += dE0dx * min_x + dE0dy * min_y

	@ free: r3, r8
	@ 이 다음에 해야할 일은?
	@ 1. 변에 대해 커버리지 비트셋 계산
	@ 2. 하나라도 0인 경우 처리 X
	@ 3. 결과를 스택에 저장하기 (VLA)
	bl		.tile_mask @ E0에 대해서 타일 마스크 계산 -> r3가 리턴 결과


@ 0,0에서 행렬식 E, 변화량 dEdx, dEdy를 받아 8x8 커버리지 마스크 계산
dEdx	.req r0
dEdy	.req r1
E		.req r2
mask	.req r3
rowMask	.req r8

@r3, r8만 free
.tile_mask:
	mov		r3, E @ E_max = E
	mov		r8, E @ E_min = E
	cmp		r0, #0 @ dEdx를 0과 비교
	addgt	r3, r3, dEdx
	addle	r8, r8, dEdx
	cmp		r1, #0 @ dEdy를 0과 비교
	addgt	r3, r3, dEdy
	addle	r8, r8, dEdy
	cmp		r3, #0 @ if (E_max < 0) return 0; // Empty coverage
	movlt	mask, #0x00000000
	bxlt	lr
	cmp		r8, #0 @ if (E_min > 0) return -1; // Full coverage
	movgt	mask, #0xFFFFFFFF
	bxgt	lr
	push	{E, lr}
	bl .row_mask
	mov mask, rowMask @ mask = row_mask(E0, dEdx, dEdy);
	add	E, E, dEdy, LSL #1 @ E += dEdy * 2, 두 줄 스킵(인터레이싱)
	bl .row_mask
	orr	mask, rowMask, mask, LSL #8 @ mask = (mask << 8) | row_mask(E, dEdx, dEdy);
	add	E, E, dEdy, LSL #1 @ E += dEdy * 2, 두 줄 스킵(인터레이싱)
	bl .row_mask
	orr	mask, rowMask, mask, LSL #8 @ mask = (mask << 8) | row_mask(E, dEdx, dEdy);
	add	E, E, dEdy, LSL #1 @ E += dEdy * 2, 두 줄 스킵(인터레이싱)
	bl .row_mask
	orr	mask, rowMask, mask, LSL #8 @ mask = (mask << 8) | row_mask(E, dEdx, dEdy);
	pop		{E, pc} @ dEdx, dEdy는 변경되지 않음(?)

base .req r5
.row_mask:
	cmp dEdx, #0 @ dEdx와 0을 비교
	blt .L11 @ dEdx < 0이라면 직선의 왼쪽이 내부
	bgt .L10 @ dEdx > 0이라면 직선의 오른쪽이 내부
	mov		rowMask, #0 @ 일단 0으로 초기화
	cmp		E, #0 @ dEdx == 0이라면 y축에 평행한 선임, top-left rule 적용
	cmpeq	dEdy, #0 @ dEdx != 0이라면 dEdy와 0을 비교
	movgt	rowMask, #0xFF @ if (E > 0 || (E == 0 && dEdy > 0)) rowMask = 0xFF;
	bx lr
.L10: @ 직선의 오른쪽이 내부 
	mov rowMask, #0x000000FF @ 행렬식
	mov base, E @ base = E
	add base, base, dEdx, LSL #2 @ base += dEdx * 4
	cmp base, dEdx @ base + dEdx * 4 < dEdx
	movlt rowMask, rowMask, LSR #4
	subge	base, base, dEdx, LSL #2 @ base -= dEdx * 4;
	adds base, base, dEdx @ base += dEdx;
	movlt rowMask, rowMask, LSR #2
	subge base, base, dEdx @ base -= dEdx;
	cmp	base, #0
	movlt rowMask, rowMask, LSR #1
	addlt base, base, dEdx @ base += dEdx;
	cmp	base, #0
	movlt rowMask, rowMask, LSR #1
	bx lr
.L11: @ 직선의 왼쪽이 내부
	mov rowMask, #0xFFFFFF00 @ 행렬식
	mov base, E @ base = E
	add base, base, dEdx, LSL #2 @ base += dEdx * 4
	cmp base, dEdx @ base + dEdx * 4 >= dEdx
	movge rowMask, rowMask, LSR #4
	sublt	base, base, dEdx, LSL #2 @ base -= dEdx * 4;
	adds base, base, dEdx @ base += dEdx;
	movge rowMask, rowMask, LSR #2
	sublt base, base, dEdx @ base -= dEdx;
	cmp	base, #0
	movge rowMask, rowMask, LSR #1
	addge base, base, dEdx @ base += dEdx;
	cmp	base, #0
	movge rowMask, rowMask, LSR #1
	bic	rowMask, rowMask, #0xFF @ rowMask &= 0xFF
	bx lr

.unreq	E
.unreq	dEdx
.unreq	dEdy
.unreq	mask
.unreq	rowMask
.unreq	base

.calculateCoverage:

.fillTile:



