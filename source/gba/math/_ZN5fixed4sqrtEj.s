@ 
@ @param {f} Q16.16 (unsigned)
@ @returns Q16.16 (unsigned)
@ u32	sqrt(u32 f);

.global _ZN5fixed4sqrtEj
_ZN5fixed4sqrtEj:
	push	{lr}
	mov		r1, #0 @ l = 0
	cmp		r0, #0x10000 @ f < 1(Q16.16) ?
	movlt	r2, #0x10000 @ r = 1
	cmpge	r0, #0x01000000 @ 256(Q16.16) <= f ?
	movge	r2, #0x01000000 @ 
	addle	r2, r0, #1 @ r = f + delta

	add		r3, r1, r2
	mov		r3, r3, LSR #1 @ r3 = (l + r) / 2
	cmp		r1, r3 @ l == m
	beq		.L1
.L0:
	umull	r12, r14, r3, r3 @ m^2
	cmp		r14, r0, LSR #16 @ 높은 자리 비교
	cmpeq	r12, r0, LSL #16 @ 낮은 자리 비교
	@ 높은 자리 비교에서 우위가 정해지지 않을 경우, 낮은 자리까지 비교하기
	movls	r1, r3 @ l = m
	movhi	r2, r3 @ r = m
	add		r3, r1, r2
	mov		r3, r3, LSR #1 @ r3 = (l + r) / 2
	cmp		r1, r3 @ l != m
	bne		.L0
.L1:
	mov		r0, r3
	pop		{pc}