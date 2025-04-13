.extern _ZN5mode87contextE

.section .iwram, "ax"
.global _ZN5mode84initEv
_ZN5mode84initEv:
	@ --------------- context init ---------------------
	ldr		r0, =_ZN5mode87contextE @ r0 = &context
	mov		r1, #0
	str		r1, [r0, #0x0BF4] @ context->vblank_counter = 0

	add		r1, r0, #0x0C00 @ r1 = &context->post_transform_buffer
	str		r1, [r0, #0x0BF8] @ init ptb_top

	add		r1, r0, #0x2C00 @ r2 = &context->face_buffer
	str		r1, [r0, #0x0BFC] @ init fb_top

	@ --------------- context init ---------------------
	bx		lr

