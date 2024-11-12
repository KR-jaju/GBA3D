@ .extern gbavfx_vbo
@ .extern gbavfx_vbo_size

@ .extern reciprocal

@ .section .iwram, "ax"
@ .global addFace_A
@ addFace_A:
@ 	ldr ip, =gbavfx_vbo_size
@ 	ldr ip, [ip]
@ 	ldr r3, =gbavfx_vbo
@ 	add r4, r3, #8192 @ vbo_depth

@ 	add r3, r3, ip, lsl #3 @u32* v(r4) = vertex_buffer + vertex_count * 4 * 2
@ 	add r4, r4, ip @u8* depth = r5
@ 	ldr r5, =gbavfx_fbo
@ 	ldr ip, [r5, #8192] @WARNING WARING -- 임의의 값! 계산해야함! ---------- fbo_size
@ 	add	r5, r5, ip, LSL #1 @ gbavfx_fbo + fbo_size * 2

@ 	cmp r1, #0 @ if (face_count == 0)
@ 	beq .L1 @ return;
@ .L1:
@ 	ldmia r0!, {r6, r7, r8}



@ 	bx		lr