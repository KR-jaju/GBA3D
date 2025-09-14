#include "game/entity/Mario.h"
#include "game/resource/model.h"
#include "gba/mode8/mode8.h"

#include "game/resource/animation.h"

Mario::Mario()
	: transform()
{
	this->animator.state.next_state = &Mario::animationEntry;
	this->animator.parameter = &this->control;
}

/*
1. 액션 실행
2. 트랜지션
*/
#include <cstdio>
char log4[100];
void	Mario::update()
{
    this->control.update();
    this->transform.x += this->control.velocity_x << 1;
    this->transform.z += this->control.velocity_z << 1;
	this->transform.yaw = this->control.yaw;
    sprintf(log4, "controller: %d %d", this->control.forward_vel, this->control.yaw);
}


void	Mario::render()
{

	u32	base_matrix[12];

	this->transform.update(base_matrix);
	this->animator.update(base_matrix, &mode8::context.matrix_slot[0][0]);
	mode8::drawIndexed(::vertices, ::vertex_count, ::indices, 0);
}


// void anim_and_audio_for_walk(struct MarioState *m) {
//     s32 val14;
//     struct Object *marioObj = m->marioObj;
//     s32 val0C = TRUE;
//     s16 targetPitch = 0;
//     f32 val04;

//     val04 = m->intendedMag > m->forwardVel ? m->intendedMag : m->forwardVel;

//     if (val04 < 4.0f) {
//         val04 = 4.0f;
//     }

//     if (m->quicksandDepth > 50.0f) {
//         val14 = (s32)(val04 / 4.0f * 0x10000);
//         set_mario_anim_with_accel(m, MARIO_ANIM_MOVE_IN_QUICKSAND, val14);
//         play_step_sound(m, 19, 93);
//         m->actionTimer = 0;
//     } else {
//         while (val0C) {
//             switch (m->actionTimer) {
//                 case 0:
//                     if (val04 > 8.0f) {
//                         m->actionTimer = 2;
//                     } else {
//                         //! (Speed Crash) If Mario's speed is more than 2^17.
//                         if ((val14 = (s32)(val04 / 4.0f * 0x10000)) < 0x1000) {
//                             val14 = 0x1000;
//                         }
//                         set_mario_anim_with_accel(m, MARIO_ANIM_START_TIPTOE, val14);
//                         play_step_sound(m, 7, 22);
//                         if (is_anim_past_frame(m, 23)) {
//                             m->actionTimer = 2;
//                         }

//                         val0C = FALSE;
//                     }
//                     break;

//                 case 1:
//                     if (val04 > 8.0f) {
//                         m->actionTimer = 2;
//                     } else {
//                         //! (Speed Crash) If Mario's speed is more than 2^17.
//                         if ((val14 = (s32)(val04 * 0x10000)) < 0x1000) {
//                             val14 = 0x1000;
//                         }
//                         set_mario_anim_with_accel(m, MARIO_ANIM_TIPTOE, val14);
//                         play_step_sound(m, 14, 72);

//                         val0C = FALSE;
//                     }
//                     break;

//                 case 2:
//                     if (val04 < 5.0f) {
//                         m->actionTimer = 1;
//                     } else if (val04 > 22.0f) {
//                         m->actionTimer = 3;
//                     } else {
//                         //! (Speed Crash) If Mario's speed is more than 2^17.
//                         val14 = (s32)(val04 / 4.0f * 0x10000);
//                         set_mario_anim_with_accel(m, MARIO_ANIM_WALKING, val14);
//                         play_step_sound(m, 10, 49);

//                         val0C = FALSE;
//                     }
//                     break;

//                 case 3:
//                     if (val04 < 18.0f) {
//                         m->actionTimer = 2;
//                     } else {
//                         //! (Speed Crash) If Mario's speed is more than 2^17.
//                         val14 = (s32)(val04 / 4.0f * 0x10000);
//                         set_mario_anim_with_accel(m, MARIO_ANIM_RUNNING, val14);
//                         play_step_sound(m, 9, 45);
//                         targetPitch = tilt_body_running(m);

//                         val0C = FALSE;
//                     }
//                     break;
//             }
//         }
//     }

//     marioObj->oMarioWalkingPitch =
//         (s16) approach_s32(marioObj->oMarioWalkingPitch, targetPitch, 0x800, 0x800);
//     marioObj->header.gfx.angle[0] = marioObj->oMarioWalkingPitch;
// }