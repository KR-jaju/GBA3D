.extern _ZN5mode87contextE
.extern _ZN5fixed6sincosEj

@ void	mode8::setCamera(i32 x, i32 y, i32 z, i32 yaw, i32 pitch); // 카메라 정보 설정
@ view matrix 생성,
@ yaw, pitch 저장

@ yaw는 -32768 ~ 32768
@ pitch는 -16384 ~ 16383

@ 0일 때 

.section .iwram, "ax"
.global _ZN5mode89setCameraEiiiii
_ZN5mode89setCameraEiiiii:
	push	{r4-r11, r14} @ 9 * 4 바이트
	ldr		r9, =_ZN5mode87contextE

	ldr		r4, [sp, #36] @ TODO : 5번째 인자 (pitch) 로드 오프셋

	mov		r8, #960
	mov		r5, r3, LSL #16
	mov		r5, r5, LSR #16

	mul		r5, r8, r5 @ yaw * 960
	mov		r5, r5, ASR #16 @ 정수 단위로, r5 = x_offset
	mov		r8, #320
	add		r7, r4, #16384 @ -16384 ~ 16383 -> 0 ~ 32768
	mul		r6, r7, r8 @ (pitch + 90도) * 160
	mov		r6, r6, ASR #15 @ 정수 단위로, r6 = y_offset
	mov		r7, #1200
	mla		r5, r7, r6, r5 @ r5 = x_offset + y_offset * 1200
	str		r5, [r9, #0x0BF0] @ context->background_offset = r5

	rsb		r5, r0, #0 @ r5 = -x
	rsb		r6, r1, #0 @ r6 = -y
	rsb		r7, r2, #0 @ r7 = -z

	mov		r0, r3 @ yaw
	bl		_ZN5fixed6sincosEj
	mov		r8, r0 @ r8 = (sin | cos)
	mov		r0, r4 @ pitch
	bl		_ZN5fixed6sincosEj

	add		r12, r9, #0x0BA0 @ view_matrix
	
	mov		r2, r0, ASR #16 @ sin_pitch
	mov		r0, r0, LSL #16
	mov		r3, r0, ASR #16 @ cos_pitch
	mov		r0, r8, ASR #16 @ sin_yaw
	mov		r8, r8, LSL #16
	mov		r1, r8, ASR #16 @ cos_yaw

	mul		r8, r0, r3 @ r8 = sin_yaw * cos_pitch
	mov		r8, r8, ASR #14
	mov		r9, r2 @ r9 = sin_pitch
	mul		r10, r1, r3 @ r10 = cos_yaw * cos_pitch
	mov		r10, r10, ASR #14

	mov		r0, r5 @ r0 = -x
	mov		r1, r6 @ r1 = -y
	mov		r14, r7 @ r14 = -z

	mul		r11, r8, r0 @ (-x) * mat[2, 0]
	mla		r11, r9, r1, r11 @ (-y) * mat[2, 1]
	mla		r11, r10, r14, r11 @ (-z) * mat[2, 2]
	mov		r11, r11, ASR #14

	mul		r4, r8, r9 @ r4 = r8 * r9
	mov		r4, r4, ASR #14
	rsb		r4, r4, #0 @ r4 = -r4
	mul		r5, r8, r8 @ r5 = r8 * r8
	mla		r5, r10, r10, r5 @ r5 += r10 * r10
	mov		r5, r5, ASR #14
	mul		r6, r9, r10 @ r6 = r9 * r10
	mov		r6, r6, ASR #14
	rsb		r6, r6, #0
	mul		r7, r0, r4
	mla		r7, r1, r5, r7
	mla		r7, r14, r6, r7	@ r7 = r0 * r4 + r1 * r5 + r14 * r6
	mov		r7, r7, ASR #14

	rsb		r2, r8, #0 @ r2 = -r8
	mul		r3, r0, r10
	mla		r3, r14, r2, r3 @ r3 = r0 * r10 + r14 * r2
	mov		r3, r3, ASR #14
	mov		r0, r10
	mov		r1, #0

	stmia	r12, {r0-r11} @ save matrix

	pop		{r4-r11, r14}
	bx		lr