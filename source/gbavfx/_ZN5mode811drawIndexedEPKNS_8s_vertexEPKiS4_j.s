@ .extern gbavfx_drawSkinned
.extern reciprocal_u16
.extern _ZN5mode87contextE

@ void mode8::drawIndexed(TestVertex const* vertices, i32 const* vertex_count, i32 const* indices, u32 texture_id);

@ 1. prepare pointer to ptb
@ 2. loop vertex_count
@ 3. loop vertices
@ 4. prepare matrix
@ 5. transform vertex
@ 6. perspective divide
@ 7. add to ptb (vertex calculation done)

@ r0 = vertices
@ r1 = vertex_count (per bone)
@ r2 = indices
@ r3 = texture_id

.section .iwram, "ax"
.global	_ZN5mode811drawIndexedEPKNS_8s_vertexEPKiS4_j
_ZN5mode811drawIndexedEPKNS_8s_vertexEPKiS4_j:
	ldr		r12, [r1], #4 @ r12 = vertex_count[0]
	cmp 	r12, #0 @ if vertex_count == 0?
	beq 	.L5 @ return;
	push	{r1-r11, lr} @ store (vertex_count, indices, texture_id and others)
@ prepare pointer to ptb (post transform buffer(vertex, face))
	ldr 	r3, =_ZN5mode87contextE @ r3 = &context;
	ldr		r4, [r3, #0x0BF8] @ r4 = context->ptb_top
	add		r5, r3, #0x0600 @ r5 = &context->matrix_slot
	mov		r6, r0 @ r6 = vertices
.L0: @ loop bones
@ ------------------------------ vertex transformation ------------------------------------------------------------
@ free registers = (r0, r1, r2, r3, r7, r8, r9, r10, r11, r14(lr))
@ used registers = (r4, r5, r6, r12(ip))
	@ r4 = &context->ptb_top
	@ r5 = &context->matrix_slot
	@ r6 = vertices
	@ r12 = vertex count(loop variable)
@ stack = (vertex_count, indices, texture_id, ...)

.L1: @ loop vertices
@ ------------------------------------------------------------ matrix multiplication ------------------------------------------------------------
	ldmia r6!, {r1, r3, r7} @ vector x, y, z
	@ x 계산하기 (1행)
	ldmia r5!, {r8, r9, r10, r11} @ matrix[0, 0:3]
	mul	r8, r1, r8 @ r8 = matrix[0, 0] * x
	mla r8, r9, r3, r8 @ r8 += matrix[0, 1] * y
	mla r8, r10, r7, r8 @ r8 += matrix[0, 2] * z
	add r8, r11, r8, ASR #15 @ r8 = (r8 >> 15) + matrix[0, 3]

	@ y 계산하기 (2행)
	ldmia r5!, {r9, r10, r11, r14} @ matrix[1, 0:3]
	mul	r9, r1, r9 @ r9 = matrix[1, 0] * x
	mla r9, r10, r3, r9 @ r9 += matrix[1, 1] * y
	mla r9, r11, r7, r9 @ r9 += matrix[1, 2] * z
	add r9, r14, r9, ASR #15 @ r9 = (r9 >> 15) + matrix[1, 3]

	@ z 계산하기 (3행)
	ldmia r5!, {r0, r10, r11, r14} @ matrix[2, 0:3]
	mul	r0, r1, r0 @ r0 = matrix[2, 0] * x
	mla r0, r10, r3, r0 @ r0 += matrix[2, 1] * y
	mla r0, r11, r7, r0 @ r0 += matrix[2, 2] * z
	add r0, r14, r0, ASR #15 @ r0 = (r0 >> 15) + matrix[2, 3]

@ 문서에 의하면 r8, r9, r0은 소수부 8비트의 부호있는 고정소수점 값으로 분류됨

@ free registers = ()
@ used registers = (r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12(ip), r14(lr))
@ stack = (vertex_count, indices, texture_id, ...)
@ ------------------------------------------------------------ matrix multiplication ------------------------------------------------------------

@ free registers = (r1, r2, r3, r7, r10, r11, r14(lr))
@ used registers = (r0, r4, r5, r6, r8, r9, r12(ip))
@ r0 = post transform z
@ r4 = &context->ptb_top
@ r5 = &context->matrix_slot
@ r6 = vertices
@ r8 = post transform x
@ r9 = post transform y
@ r12 = vertex count(loop variable)
@ ------------------------------ Calculate 1/z ------------------------------
	@ input : r0
	@ used : r1, r2
	@ output : r0

	cmp		r0, #1
	movlt	r0, #1 @ clamp z
	mov		r7, r0, ASR #6 @ z의 소수부를 2진수 2자리만 남김
	cmp		r7, #0xFF @ 정수부가 64를 넘기면 제한 (총 8비트)
	movgt	r7, #0xFF @ clamp z
	bl	reciprocal_u16 @ reciprocal_u16(post transform z)
@ ------------------------------ Calculate 1/z ------------------------------

	@ 2^31 / (a * 2^8) = 2^31/a * 2^23 -> 소수부가 23비트인 상태임

	@ post transform x (8bit integer, 8bit fraction), 1/z (23bit fraction)
	smull r1, r2, r8, r0 @ post transform x * 1/z (31bit fraction), 소수점을 6비트로 옮겨야하므로, >>25
	mov r1, r1, LSR #25 @ lo >> 24
	orr r1, r1, r2, LSL #7 @ (lo >> 24) | (hi << 8) (7bit fraction)
	@ 왼쪽으로 6비트 오버 쉬프트 (a * 64인 상태)
	add r1, r1, r1, ASR #2 @ a * 64 + a * 16 = a * 80
	add r1, r1, #120 @ 120 + post transform x * 1/z * 80

	@ post transform y (8bit integer, 8bit fraction), 1/z (17bit integer, 15bit fraction)
	smull r2, r3, r9, r0 @ post transform y * 1/z (31bit fraction), 소수점을 6비트로 옮겨야하므로, >>25
	mov r2, r2, LSR #25 @ lo >> 24
	orr r2, r2, r3, LSL #7 @ (lo >> 24) | (hi << 8) (7bit fraction)
	@ 왼쪽으로 6비트 오버 쉬프트 (a * 64인 상태)
	add		r2, r2, r2, ASR #2 @ a * 64 + a * 16 = a * 80
	rsb		r2, r2, #80 @ 80 - post transform y * 1/z * 80

	@ remap x, y
	@ pack x(12bit), y(12bit), z(8bit) in 4 bytes
	@ r1, r2는 -2048 ~ 2047 안에 있다고 가정
	add		r1, r1, #2048 @ -2048 ~ 2047 -> 0 ~ 4096 (x), 정점 정렬 때문에 양수로 맞춰야함.
	add		r2, r2, #2048 @ -2048 ~ 2047 -> 0 ~ 4096 (y)
	orr		r7, r7, r1, LSL #8 @ 중간 12비트 (x), (왼쪽으로 8비트 쉬프트 하므로 최상위 8비트를 제외한 (32 - 8 - 12) = 12비트를 truncated해야함)
	orr		r7, r7, r2, LSL #20 @ 상위 12비트 (y), no truncation needed

	ldr		r8, [r6], #4 @ read vertex uv, move to next
	stmia	r4!, {r7, r8} @ append to ptb (v[0] = r7, v[1] = r8)
	subs	ip, ip, #1 @ ip -= 1;
	subne	r5, r5, #48 @ r5 = &context->matrix_slot[n] 위에서 읽으면서 (12 * 4 = )48바이트 증가됐으므로 그만큼 줄임
	bne		.L1 @ while (ip > 0)
@ ------------------------------ vertex transformation end (per bone) ------------------------------------------------------------
@ stack = (vertex_count, indices, texture_id, ...)
	ldr r2, [sp] @ r2 = vertex_count
	ldr ip, [r2], #4 @ r2 = *(vertex_count++);
	cmp ip, #0
	strne r2, [sp] @ store vertex_count
	bne .L0 @ if r2 != 0, loop
@ ------------------------------ vertex transformation end (per drawcall) ------------------------------------------------------------
@ free registers = (r0, r1, r2, r3, r5, r6, r7, r8, r9, r10, r11, r12(ip), r14(lr))
@ used registers = (r4)
@ r4 = &context->ptb_top
	ldr		r0, =_ZN5mode87contextE @ r0 = context (&context->ordering_table)
	str		r4, [r0, #0x0BF8] @ context->ptb_top = ptb_top;
	add		r4, r0, #0x0C00 @ r4 = &context->ptb
@ ------------------------------ add face to ptb ------------------------------------------------------------
@ free registers = (r1, r2, r3, r5, r6, r7, r8, r9, r10, r11, r12(ip), r14(lr))
@ used registers = (r0, r4)
@ r0 = &context (&context->ordering_table)
@ r4 = &context->ptb
@ stack = (vertex_count, indices, texture_id, ...)
	add	sp, sp, #4 @ pop vertex_count
@ stack = (indices, texture_id, ...)
	pop		{r1, r2} @ r1 = indices, r2 = texture_id
@ stack = (...)

	add		r14, r0, #0x2C00 @ r14 = &context->face_buffer
	ldr		r3, [r0, #0x0BFC] @ r3 = context->fb_top

	ldmia	r1!, {r5, r6, r7} @ r5 = i0, r6 = i1, r7 = i2
	cmp		r5, #-1 @ terminator found
	beq		.L5 @ if i0 == -1, return
.L2: @ loop indices
	ldr		r8, [r4, r5, LSL #3] @ r9 = v[i0 * 2]
	ldr		r9, [r4, r6, LSL #3] @ r10 = v[i1 * 2]
	ldr		r10, [r4, r7, LSL #3] @ r11 = v[i2 * 2]

	@ r9, r10, r11에는 x, y, z가 패킹돼있음. 정렬은 y순서가 작은 순서대로, 같다면 x가 작은 순서대로 (z는 덤)
	@ pseudo-lexicographical order
	cmp		r8, r9 @ if 0 > 1
	eorge	r5, r6, r5
	eorge	r6, r5, r6
	eorge	r5, r6, r5 @ swap(i0, i1); (xor swap)

	@ v0과 v1을 정렬한다.

	cmp		r9, r10
	cmplt	r8, r10
	orrge	r5, r5, r7, LSL #16 @ r5 = (i2 | i0)
	orrlt	r5, r5, r6, LSL #16 @ r5 = (i1 | i0)
	movlt	r6, r7 @ r6 = i2

	@ 1. v1 >= v2인 경우, (v0, v2간의 순서는 모르나, v0이 작은 것으로 간주), v1 순으로 정렬된다.
	@ 2. v1 < v2 && v0 < v2인 경우, v2가 가장 큰 값이 된다. v0, v1, v2순으로 정렬된다.
	@ 3. v1 < v2 && v0 > v2인 경우는 발생할 수 없다.

	cmp		r9, r10
	cmpge	r8, r10
	movge	r5, r5, ROR #16 @ (i2 | i0) -> (i0 | i2)
	@ 1. v1 < v2인 경우, 아무것도 하지 않는다. (이미 정렬됨)
	@ 2. v1 >= v2 && v0 >= v2인 경우, v2, v0, v1순으로 정렬된다.
	@ 3. v1 >= v2 && v0 < v2인 경우, v0, v2, v1순으로 정렬된다.

	@ if(!(B && C)) { swap(i1, i2); }
	@ 1. b false -> ge이 나옴
	@ 2. b true, c false -> ge이 나옴
	@ 3. b true, c true -> lt가 나옴
	@ if(!(B || C)) { swap (i0, i1); }
	@ 1. b true(lt) -> false
	@ 2. b false, c true(lt) -> false
	@ 3. b false, c false -> true

	orr		r6, r6, r2, LSL #16 @ ((texture_id << 16) | i2);

@ free registers = (r7, r11, r12(ip))
@ used registers = (r0, r1, r2, r3, r4, r5, r6, r8, r9, r10, r14(lr))
@ r0 = &context (&context->ordering_table)
@ r1 = indices
@ r3 = &context->fb_top
@ r4 = &context->ptb_top
@ r5 = (i1 | i0)
@ r6 = i2
@ r8 = v0
@ r9 = v1
@ r10 = v2
@ r14 = &context->face_buffer

@ dx02, dy01도 마찬가지로 구하고
	and		r7, r8, #0xFF @ r7 = v0.z
	and		r11, r9, #0xFF @ r11 = v1.z
	add		r7, r7, r11 @ r7 = v0.z + v1.z
	and		r11, r10, #0xFF @ r11 = v2.z
	add		r7, r7, r11 @ r7 = v0.z + v1.z + v2.z

	@ r7 = approximate depth of triangle
	cmp		r7, #3
	ble		.L3 @ continue;

	mov		r12, r8, LSL #12
	mov		r12, r12, LSR #20 @ r12 = v0.x
	mov		r8, r8, LSR #20 @ r8 = v0.y

	mov		r2, r9, LSL #12 @ r2 = 1.x << 20
	rsb		r2, r12, r2, LSR #20 @ r2 = v1.x - v0.x
	rsb		r11, r8, r10, LSR #20 @ r11 = v2.y - v0.y
	mul		r2, r11, r2 @ dx01 * dy02

	mov		r11, r10, LSL #12 @ r11 = 2.x << 12
	rsb		r11, r12, r11, LSR #20 @ r11 = 2.x - 0.x
	rsb		r10, r8, r9, LSR #20 @ r10 = 1.y - 0.y = dy01
	mul		r10, r11, r10 @ dx02 * dy01

	cmp		r2, r10 @ if(dx01 * dy02 <= dx02 * dy01)
	bge		.L3 @ continue; @ cull if winding order == clockwise
	
@ free registers = (r2, r8, r9, r10, r11, r12(ip))
@ used registers = (r0, r1, r3, r4, r5, r6, r7, r14(lr))
@ r0 = &context (&context->ordering_table)
@ r1 = indices
@ r3 = &context->fb_top
@ r4 = &context->ptb_top
@ r5 = (i1 | i0)
@ r6 = i2
@ r7 = approximate depth of triangle
@ stack = (vertex_count, indices, texture_id, ...)
	mov		r7, r7, LSL #1 @ r7 = z * sizeof(uint16_t)
	ldrsh	r11, [r0, r7] @ r11 = ordering_table[z]
	orr		r6, r6, r11, LSL #21 @ r6 = (next << 21) | (i2)
	sub		r11, r3, r14 @ r11 = fb_top - face_buffer
	mov		r11, r11, LSR #3 @ r11 = face_id
	strh	r11, [r0, r7] @ ordering_table[z] = face_id
	stmia	r3!, {r5, r6} @ *(fb_top++) = face;
.L3:
	ldmia	r1!, {r5, r6, r7} @ r5 = i0, r6 = i1, r7 = i2
	cmp		r5, #-1
	bne		.L2 @ if i0 != -1, continue
	str		r3, [r0, #0x0BFC] @ context->fb_top = fb_top
.L4:
	@ stack = (...)
	pop		{r4-r11, lr} @ restore r4-r11, lr
.L5:
	bx		lr
