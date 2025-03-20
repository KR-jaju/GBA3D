@ .extern gbavfx_vbo
@ .extern reciprocal


@ @	(Vertex const*,
@ @	i32 const* vertex_count,
@ @	i32 const* indices,
@ @	u32 face_count,
@ @	u32 texture_id,
@ @	i32 bone_count)

@ .section .iwram, "ax"
@ .global gbavfx_drawSkinned
@ gbavfx_drawSkinned:
@ 	cmp r1, #0 @ if (count == 0)
@ 	beq .L4 @ return;
@ 	push	{r2-r11, lr} @ r2, r3은 매개변수 저장을 위해

@ 	ldr		r3, =gbavfx_vbo
@ 	add		r4, r3, #8192 @ depth
@ 	ldr		ip, [r4, #1024] @ size
@ 	add		lr, ip, r1 @ vbo.size += vertex_count
@ 	str		lr, [r4, #1024]
@ 	add		r3, r3, ip, LSL #3
@ 	add		r4, r4, ip
@ 	push	{r3, r4} @ vertices, depth

@ 	@ ldr		r5, [r1] @ bone count
 
	
@ .bone_loop_begin: @ while (bone_count > 0)
@ 	sub		r7, r6, r5 @ bone
@ 	push	{r2, r5, r6}
@ 	@ ldr		r12, [r1, r5] @ vertec_count
@ 	ldr		r12, [r1], #4 @ vertex_count
@ 	@ ldr		r2, [r2, r7, LSL #2] @ matrix
@ 	add		r2, r2, r7, LSL #5 @ matrix[idx] == matrix + idx * (8 + 4) * 4
@ 	add		r2, r2, r7, LSL #4 @ matrix + idx * (12 * 4byte)
@ 	cmp		r12, #0 @ vertex_left
@ 	ble		.transform_end
@ .transform_begin: @ while loop
@ 	push	{r0-r3, r12} 
@ 	ldmia	r0, {r3, r5, lr} @ vector x, y, z

@ 	ldmia	r2!, {r6-r9} @ matrix 0 ~ 3				5 cycles
@ 	smull	r10, r1, r3, r6 @ vec.x * matrix[0]		(2 ~ 6) cycles
@ 	smlal	r10, r1, r5, r7 @ vec.y * matrix[1]		(3 ~ 7) cycles
@ 	smlal	r10, r1, lr, r8 @ vec.z * matrix[2]		(3 ~ 7) cycles
@ 	mov		r10, r10, LSR #16 @ lo >> 16				(1) cycles
@ 	orr		r10, r10, r1, ASL #16 @ (lo >> 16) | (hi << 16)	(1) cycles
@ 	add		r10, r10, r9 @ x + matrix[3]				(1) cycles

@ 	@ total 16~28 cycles

@ 	ldmia	r2!, {r6-r9} @ matrix 4 ~ 7
@ 	smull	r11, r1, r3, r6 @ vec.x * matrix[0]
@ 	smlal	r11, r1, r5, r7 @ vec.y * matrix[1]
@ 	smlal	r11, r1, lr, r8 @ vec.z * matrix[2]
@ 	mov		r11, r11, LSR #16 @ lo >> 16
@ 	orr		r11, r11, r1, ASL #16 @ (lo >> 16) | (hi << 16)
@ 	add		r11, r11, r9 @ x + matrix[7]

@ 	ldmia	r2!, {r6-r9} @ matrix 8 ~ 11
@ 	smull	r12, r1, r3, r6 @ vec.x * matrix[0]
@ 	smlal	r12, r1, r5, r7 @ vec.y * matrix[1]
@ 	smlal	r12, r1, lr, r8 @ vec.z * matrix[2]
@ 	mov		r12, r12, LSR #16 @ lo >> 16
@ 	orr		r12, r12, r1, ASL #16 @ (lo >> 16) | (hi << 16)
@ 	add		r12, r12, r9 @ x + matrix[11]

@ 	@--------------행렬곱 끝
@ 	cmp		r12, #16384
@ 	movge	r0, r12
@ 	movlt	r0, #16384
@ 	mov		r9, r0, ASR #14
@ 	bl		reciprocal @ reciprocal(post_z)
@ 	mov		r5, r0
@ 	pop		{r0-r3, r12}
@ 	@-------------z_reciprocal계산 완료
	
@ 	strb	r9, [r4], #1 @ depth[0] = (post_z >> 14)
@ 	smull 	r6, r7, r10, r5 @ post_x * z_reciprocal
@ 	mov		r6, r6, LSR #15 @ lo >> 16
@ 	orr		r6, r6, r7, LSL #17 @ (lo >> 16) | (hi << 16)
@ 	mov		r6, r6, ASL #5 @ a = a*32
@ 	add		r6, r6, r6, ASL #2 @ a = a * 32 + a * 128 = a * 160
@ 	mov		r6, r6, LSR #16
@ 	add		r6, r6, #120 @ post_x * z_reciprocal * 160 + 120

@ 	smull 	r7, r8, r11, r5 @ post_y * z_reciprocal
@ 	mov		r7, r7, LSR #15 @ lo >> 16
@ 	orr		r7, r7, r8, LSL #17 @ (lo >> 16) | (hi << 16)
@ 	mov		r7, r7, ASL #5
@ 	add		r7, r7, r7, ASL #2 @ a = a * 160
@ 	mov		r7, r7, LSR #16
@ 	add		r7, r7, #80 @ post_y * z_reciprocal * 160 + 80

@ 	add		r6, r6, #32768
@ 	add		r7, r7, #32768
@ 	mov		r6, r6, LSL #16
@ 	mov		r6, r6, LSR #16
@ 	orr		r6, r6, r7, LSL #16 @ v[0] 준비

@ 	ldr		r7, [r0, #12] @ vertex.uv
@ 	stmia	r3!, {r6, r7} @ v[0] = r6, v[1] = r7

@ 	add		r0, r0, #16 @ sizeof(TestVertex) == 20
@ 	subs	r12, r12, #1 @ count -= 1;
@ 	bne		.transform_begin
@ .transform_end:
@ 	pop		{r2, r5, r6}
@ 	subs	r5, r5, #1 @bone_count -= 1;
@ 	bne		.bone_loop_begin
@ .bone_loop_end:

@ 	@----------------------------------------add Face----------------------------
@ .L3:
@ 	pop		{r3, r4} @ v, depth
@ 	pop		{r0, r1} @ indices, face_count
@ 	ldr		r2, [sp, #36] @ texture_id ????????????????????????

@ 	ldr		r5, =gbavfx_fbo @ f
@ 	add		r6, r5, #8192
@ 	ldr		r6, [r6] @ size
@ 	add		r5, r5, r6, LSL #2 @ f + size * 4
	
@ 	cmp		r1, #0
@ 	beq		.L1
@ .L5: @while
@ 	ldmia	r0!, {r7, r8, r9} @i0, i1, i2
@ 	ldr		r11, [r3, r7, LSL #3] @ v[i0 * 2]
@ 	ldr		ip, [r3, r8, LSL #3] @ v[i1 * 2]
@ 	ldr		lr, [r3, r9, LSL #3] @ v[i2 * 2]

@ 	cmp		r11, ip @ if (a >= b)
@ 	eorge	r7, r8, r7
@ 	eorge	r8, r8, r7
@ 	eorge	r7, r8, r7 @ swap(i0, i1);
@ 	@------------
@ 	cmp		ip, lr
@ 	cmplt	r11, lr
@ 	orrge	r7, r7, r9, LSL #16 @ 스왑해서 a와 c의 인덱스가 합쳐짐
@ 	orrlt	r7, r7, r8, LSL #16 @ 스왑하지 않고 a와 b의 인덱스가 합쳐짐
@ 	movlt	r8, r9 @ 스왑하지 않고 r9 -> r8
@ 	@-------------
@ 	cmp		ip, lr @ B
@ 	cmpge	r11, lr @ C
@ 	movge	r7, r7, ROR #16 @ a와 b를 스왑해야하는 경우 스왑
	
@ 	@ if(!(B && C)) { swap(i1, i2); }
@ 	@ 1. b false -> ge이 나옴
@ 	@ 2. b true, c false -> ge이 나옴
@ 	@ 3. b true, c true -> lt가 나옴
@ 	@ if(!(B || C)) { swap (i0, i1); }
@ 	@ 1. b true(lt) -> false
@ 	@ 2. b false, c true(lt) -> false
@ 	@ 3. b false, c false -> true
	
@ @---------------r9 is free now----------------
@ .L7:
@ 	mov		r9, r11, LSL #16
@ 	mov		r9, r9, LSR #16 @ x0
@ 	mov		r11, r11, LSR #16 @ y0

@ 	mov		r10, ip, LSL #16 @ x1
@ 	rsb		r10, r9, r10, LSR #16 @ r10 = dx01
@ 	mov		ip, ip, LSR #16 @ y1
@ 	orr		ip, ip, lr, LSL #16 @ ip = (x2 | y1)
@ 	rsb		lr, r11, lr, LSR #16 @ lr = dy02
@ 	mul		r10, lr, r10 @ dx01 * dy02
@ 	@--------r9, r11(x), r10(res), ip(x2 | y1), lr
	
@ 	rsb		lr, r9, ip, LSR #16 @ dx02
@ 	mov		ip, ip, LSL #16
@ 	rsb		ip, r11, ip, LSR #16 @dy01
@ 	mul		ip, lr, ip @ dx01 * dy02

@ 	cmp		r10, ip @ if(dx01 * dy02 <= dx02 * dy01)
@ 	ble		.L6 @ continue;
@ .L8: @--------swap END---------------
@ 	mov		r10, r7, LSL #16
@ 	mov		r10, r10, LSR #16 @ i0
@ 	mov		r11, r7, LSR #16 @ i1
@ 	ldrb	r10, [r4, r10] @ depth[i0]
@ 	ldrb	r11, [r4, r11] @ depth[i1]
@ 	add		r10, r10, r11
@ 	ldrb	r11, [r4, r8] @ depth[i2]
@ 	add		r10, r10, r11 @ z
@ 	cmp		r10, #3 @ sum of three zs is less than 3?
@ 	ble		.L6 @ continue
@ 	ldr		r9, =ordering_table
@ 	mov		r10, r10, LSL #1 @ z <<= 1; @ alignment!
@ 	ldrsh	r11, [r9, r10] @ ordering_table[z]
@ 	orr		r8, r8, r11, LSL #21 @ (next << 21)
@ 	orr		r8, r8, r2, LSL #16 @ (texture_id << 16)
@ 	mov		r11, r6, LSR #1 @ idx >> 1
@ 	strh	r11, [r9, r10] @ ordering_table[z] = idx >> 1
@ 	@ str		r7, [r5], #4 @ *f = (i1 << 16) | (i0); f += 1;
@ 	@ str		r8, [r5], #4 @ *f = ((next << 21) | (texture << 16) | i2); f += 1;
@ 	stmia	r5!, {r7, r8}

@ 	add		r6, r6, #2 @ idx += 2;

@ .L6:
@ 	subs	r1, r1, #1
@ 	bne		.L5
@ .L1:
@ 	ldr		r5, =gbavfx_fbo
@ 	add		r5, r5, #8192
@ 	str		r6, [r5] @ gbavfx_fbo.size = idx;
@ 	pop		{r4-r11,lr}
@ .L4:
@ 	bx lr