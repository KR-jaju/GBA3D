
.extern gbavfx_vbo
.extern reciprocal

.section .iwram, "ax"
.global transformVertex_A
transformVertex_A:
	cmp r1, #0 @ if (count == 0)
	beq .L1 @ return;
	push {r4-r11,lr} @ 모든 레지스터를 저장해둠
	ldr r3, =gbavfx_vbo
	add r4, r3, #8192 @ vbo_depth
	ldr ip, [r4, #1024] @ size

	add r3, r3, ip, lsl #3 @u32* v(r4) = vertex_buffer + vertex_count * 4 * 2
	add r4, r4, ip @u8* depth = r5
.L2: @ while loop
matrix_mulmv:
	@ matrix, vector 포인터에 2개 현재 (r0, r2), vector는 유지함
	@ matrix, vector 값에 7개
	@ 덧셈 결과 저장에 4개, 총 13-1 = 12개
	@ 결과는 r10,r11,r12에 저장함함
	@ while loop밖에서 유지되는 레지스터는 5개(r0~r4)
	@ stmia	sp, {r0-r4} @ r1~r12에 값이 쓰이지만, while loop밖에는 r0~r4만 사용하므로 r1-r4, r0는 reciprocal을 위해
	push	{r0-r3}
	ldmia	r0, {r3, r5, lr} @ vector x, y z

	ldmia	r2!, {r6-r9} @ matrix 0 ~ 3
	smull	r10, r1, r3, r6 @ vec.x * matrix[0]
	smlal	r10, r1, r5, r7 @ vec.y * matrix[1]
	smlal	r10, r1, lr, r8 @ vec.z * matrix[2]
	mov		r10, r10, LSR #16 @ lo >> 16
	orr		r10, r10, r1, ASL #16 @ (lo >> 16) | (hi << 16)
	add		r10, r10, r9 @ x + matrix[3]

	ldmia	r2!, {r6-r9} @ matrix 4 ~ 7
	smull	r11, r1, r3, r6 @ vec.x * matrix[0]
	smlal	r11, r1, r5, r7 @ vec.y * matrix[1]
	smlal	r11, r1, lr, r8 @ vec.z * matrix[2]
	mov		r11, r11, LSR #16 @ lo >> 16
	orr		r11, r11, r1, ASL #16 @ (lo >> 16) | (hi << 16)
	add		r11, r11, r9 @ x + matrix[7]

	ldmia	r2!, {r6-r9} @ matrix 8 ~ 11
	smull	r12, r1, r3, r6 @ vec.x * matrix[0]
	smlal	r12, r1, r5, r7 @ vec.y * matrix[1]
	smlal	r12, r1, lr, r8 @ vec.z * matrix[2]
	mov		r12, r12, LSR #16 @ lo >> 16
	orr		r12, r12, r1, ASL #16 @ (lo >> 16) | (hi << 16)
	add		r12, r12, r9 @ x + matrix[11]

	@--------------행렬곱 끝
	mov		r0, r12
	mov		r9, r12, ASR #14
	bl		reciprocal @ reciprocal(post_z)
	mov		r5, r0
	pop		{r0-r3}
	@-------------z_reciprocal계산 완료
	
	strb	r9, [r4], #1 @ depth[0] = (post_z >> 14)
	smull 	r6, r7, r10, r5 @ post_x * z_reciprocal
	mov		r6, r6, LSR #15 @ lo >> 16
	orr		r6, r6, r7, LSL #17 @ (lo >> 16) | (hi << 16)
	mov		r6, r6, ASL #5 @ a = a*32
	add		r6, r6, r6, ASL #2 @ a = a * 32 + a * 128 = a * 160
	mov		r6, r6, LSR #16
	add		r6, r6, #120 @ post_x * z_reciprocal * 160 + 120

	smull 	r7, r8, r11, r5 @ post_y * z_reciprocal
	mov		r7, r7, LSR #15 @ lo >> 16
	orr		r7, r7, r8, LSL #17 @ (lo >> 16) | (hi << 16)
	mov		r7, r7, ASL #5
	add		r7, r7, r7, ASL #2 @ a = a * 160
	mov		r7, r7, LSR #16
	add		r7, r7, #80 @ post_y * z_reciprocal * 160 + 80

	add		r6, r6, #32768
	add		r7, r7, #32768
	mov		r6, r6, LSL #16
	mov		r6, r6, LSR #16
	orr		r6, r6, r7, LSL #16 @ v[0] 준비

	ldr		r7, [r0, #12] @ vertex.uv
	stmia	r3!, {r6, r7} @ v[0] = r6, v[1] = r7

	add		r0, r0, #16 @ sizeof(TestVertex) == 20
	subs	r1, r1, #1 @ count -= 1;
	bne		.L2
.L1:
	pop {r4-r11,lr}
	bx lr