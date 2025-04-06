#include "game/component/MarioControl.h"

#include "game/sm64.h"
#include "gba/io/Controller.h"
#include "gba/math/fixed.h"
#include <cmath>

static i32 approach_i32(i32 current, i32 target, i32 inc, i32 dec) {
    if (current < target) {
        current += inc;
        if (current > target) {
            current = target;
        }
    } else {
        current -= dec;
        if (current < target) {
            current = target;
        }
    }
    return current;
}

MarioControl::MarioControl()
	: yaw(0), intended_mag(0), intended_yaw(0), squish_timer(0),
	  forward_vel(0), velocity_x(0), velocity_y(0), velocity_z(0)
{
    this->action = ACT_FLAG_MOVING;
}

void	MarioControl::update()
{
	if (this->action == ACT_UNINITIALIZED)
		return;
	
	// gMarioState->marioObj->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
	// mario_reset_bodystate(gMarioState);
	// update_mario_inputs(gMarioState);
	// mario_handle_special_floors(gMarioState);
	// mario_process_interactions(gMarioState);

    this->updateInputs();

	// If Mario is OOB, stop executing actions.
	// if (gMarioState->floor == NULL) {
	// 	return 0;
	// }
    

	// The function can loop through many action shifts in one frame,
	// which can lead to unexpected sub-frame behavior. Could potentially hang
	// if a loop of actions were found, but there has not been a situation found.
    // switch (this->action & ACT_GROUP_MASK)
    // {
    // // case ACT_GROUP_STATIONARY:
    // //     this->actGroupStationary();
    // //     break;
    // case ACT_GROUP_MOVING:
    //     this->actGroupMoving();
    //     break;
    // }
    this->actGroupMoving();
	// bool	loop = false;
	// do
	// {
	// 	switch (this->action & ACT_GROUP_MASK) {
	// 		case ACT_GROUP_STATIONARY:
	// 			loop = this->actGroupStationary();
	// 			break;
	// 		case ACT_GROUP_MOVING:
	// 			loop = this->actGroupMoving();
	// 			break;
	// 		// case ACT_GROUP_AIRBORNE:
	// 		// 	loop = mario_execute_airborne_action(gMarioState);
	// 		// 	break;
	// 		// case ACT_GROUP_SUBMERGED:
	// 		// 	loop = mario_execute_submerged_action(gMarioState);
	// 		// 	break;
	// 		// case ACT_GROUP_CUTSCENE:
	// 		// 	loop = mario_execute_cutscene_action(gMarioState);
	// 		// 	break;
	// 		// case ACT_GROUP_AUTOMATIC:
	// 		// 	loop = mario_execute_automatic_action(gMarioState);
	// 		// 	break;
	// 		// case ACT_GROUP_OBJECT:
	// 		// 	loop = mario_execute_object_action(gMarioState);
	// 		// 	break;
	// 	}
	// } while(loop);

	// sink_mario_in_quicksand(gMarioState);
	// squish_mario_model(gMarioState);
	// set_submerged_cam_preset_and_spawn_bubbles(gMarioState);
	// update_mario_health(gMarioState);
	// update_mario_info_for_cam(gMarioState);
	// mario_update_hitbox_and_cap_model(gMarioState);

	// Both of the wind handling portions play wind audio only in
	// non-Japanese releases.
	// if (gMarioState->floor->type == SURFACE_HORIZONTAL_WIND)
	// {
	// 	spawn_wind_particles(0, (gMarioState->floor->force << 8));
	// }

	// if (gMarioState->floor->type == SURFACE_VERTICAL_WIND) {
	// 	spawn_wind_particles(1, 0);
	// }
	// play_infinite_stairs_music();
	// gMarioState->marioObj->oInteractStatus = 0;
}

void	MarioControl::updateInputs()
{

    // update_mario_button_inputs(m);
    this->updateJoystickInputs();
    // update_mario_geometry_inputs(m);
}

void	MarioControl::updateJoystickInputs()
{
    Controller *controller = &g_controller;
	i32 mag = (controller->stick_mag * controller->stick_mag) >> 14; // Q7.8, 64 * mag^2
    //  >> (6 + 8)
	if (this->squish_timer == 0)
		this->intended_mag = mag >> 1;
	else
		this->intended_mag = mag >> 3;

	if (intended_mag != 0)
		this->intended_yaw = controller->stick_angle; // 카메라가 필요하다
	else
		this->intended_yaw = this->yaw;
}

bool	MarioControl::actGroupMoving()
{
	bool cancel;

    // if (check_common_moving_cancels(m))
    //     return true;

    // if (mario_update_quicksand(m, 0.25f))
	// 	return true;
    this->actWalking();
    /* clang-format off */
    // switch (this->action) {
        // case ACT_WALKING:                  cancel = this->actWalking();                  break;
        // case ACT_HOLD_WALKING:             cancel = act_hold_walking(m);             break;
        // case ACT_HOLD_HEAVY_WALKING:       cancel = act_hold_heavy_walking(m);       break;
        // case ACT_TURNING_AROUND:           cancel = act_turning_around(m);           break;
        // case ACT_FINISH_TURNING_AROUND:    cancel = act_finish_turning_around(m);    break;
        // case ACT_BRAKING:                  cancel = act_braking(m);                  break;
        // case ACT_RIDING_SHELL_GROUND:      cancel = act_riding_shell_ground(m);      break;
        // case ACT_CRAWLING:                 cancel = act_crawling(m);                 break;
        // case ACT_BURNING_GROUND:           cancel = act_burning_ground(m);           break;
        // case ACT_DECELERATING:             cancel = act_decelerating(m);             break;
        // case ACT_HOLD_DECELERATING:        cancel = act_hold_decelerating(m);        break;
        // case ACT_BUTT_SLIDE:               cancel = act_butt_slide(m);               break;
        // case ACT_STOMACH_SLIDE:            cancel = act_stomach_slide(m);            break;
        // case ACT_HOLD_BUTT_SLIDE:          cancel = act_hold_butt_slide(m);          break;
        // case ACT_HOLD_STOMACH_SLIDE:       cancel = act_hold_stomach_slide(m);       break;
        // case ACT_DIVE_SLIDE:               cancel = act_dive_slide(m);               break;
        // case ACT_MOVE_PUNCHING:            cancel = act_move_punching(m);            break;
        // case ACT_CROUCH_SLIDE:             cancel = act_crouch_slide(m);             break;
        // case ACT_SLIDE_KICK_SLIDE:         cancel = act_slide_kick_slide(m);         break;
        // case ACT_HARD_BACKWARD_GROUND_KB:  cancel = act_hard_backward_ground_kb(m);  break;
        // case ACT_HARD_FORWARD_GROUND_KB:   cancel = act_hard_forward_ground_kb(m);   break;
        // case ACT_BACKWARD_GROUND_KB:       cancel = act_backward_ground_kb(m);       break;
        // case ACT_FORWARD_GROUND_KB:        cancel = act_forward_ground_kb(m);        break;
        // case ACT_SOFT_BACKWARD_GROUND_KB:  cancel = act_soft_backward_ground_kb(m);  break;
        // case ACT_SOFT_FORWARD_GROUND_KB:   cancel = act_soft_forward_ground_kb(m);   break;
        // case ACT_GROUND_BONK:              cancel = act_ground_bonk(m);              break;
        // case ACT_DEATH_EXIT_LAND:          cancel = act_death_exit_land(m);          break;
        // case ACT_JUMP_LAND:                cancel = act_jump_land(m);                break;
        // case ACT_FREEFALL_LAND:            cancel = act_freefall_land(m);            break;
        // case ACT_DOUBLE_JUMP_LAND:         cancel = act_double_jump_land(m);         break;
        // case ACT_SIDE_FLIP_LAND:           cancel = act_side_flip_land(m);           break;
        // case ACT_HOLD_JUMP_LAND:           cancel = act_hold_jump_land(m);           break;
        // case ACT_HOLD_FREEFALL_LAND:       cancel = act_hold_freefall_land(m);       break;
        // case ACT_TRIPLE_JUMP_LAND:         cancel = act_triple_jump_land(m);         break;
        // case ACT_BACKFLIP_LAND:            cancel = act_backflip_land(m);            break;
        // case ACT_QUICKSAND_JUMP_LAND:      cancel = act_quicksand_jump_land(m);      break;
        // case ACT_HOLD_QUICKSAND_JUMP_LAND: cancel = act_hold_quicksand_jump_land(m); break;
        // case ACT_LONG_JUMP_LAND:           cancel = act_long_jump_land(m);           break;
    // }
    /* clang-format on */

    // if (!cancel && (m->input & INPUT_IN_WATER)) {
    //     m->particleFlags |= PARTICLE_WAVE_TRAIL;
    //     m->particleFlags &= ~PARTICLE_DUST;
    // }

    return cancel;
}


bool	MarioControl::actWalking()
{
	// Vec3f startPos;
    // s16 startYaw = m->faceAngle[1];

    // mario_drop_held_object(m);

    // if (should_begin_sliding(m)) {
        // return set_mario_action(m, ACT_BEGIN_SLIDING, 0);
    // }

    // if (m->input & INPUT_FIRST_PERSON) {
        // return begin_braking_action(m);
    // }

    // if (m->input & INPUT_A_PRESSED) {
    //     return set_jump_from_landing(m);
    // }

    // if (check_ground_dive_or_punch(m)) {
    //     return TRUE;
    // }

    // if (m->input & INPUT_UNKNOWN_5) {
    //     return begin_braking_action(m);
    // }

    // if (analog_stick_held_back(m) && m->forwardVel >= 16.0f) {
    //     return set_mario_action(m, ACT_TURNING_AROUND, 0);
    // }

    // if (m->input & INPUT_Z_PRESSED) {
    //     return set_mario_action(m, ACT_CROUCH_SLIDE, 0);
    // }

    // m->actionState = 0;

    // vec3f_copy(startPos, m->pos);
	this->updateWalkingSpeed();
    // this
    // switch (perform_ground_step(m)) {
    //     case GROUND_STEP_LEFT_GROUND:
    //         set_mario_action(m, ACT_FREEFALL, 0);
    //         set_mario_animation(m, MARIO_ANIM_GENERAL_FALL);
    //         break;

    //     case GROUND_STEP_NONE:
    //         anim_and_audio_for_walk(m);
    //         if (m->intendedMag - m->forwardVel > 16.0f) {
    //             m->particleFlags |= PARTICLE_DUST;
    //         }
    //         break;

    //     case GROUND_STEP_HIT_WALL:
    //         push_or_sidle_wall(m, startPos);
    //         m->actionTimer = 0;
    //         break;
    // }
    // check_ledge_climb_down(m);
    // tilt_body_walking(m, startYaw);
	return false;
}

void	MarioControl::updateWalkingSpeed()
{
	i32	target_speed = std::min(this->intended_mag, 32 * 256);

	// if (m->quicksandDepth > 10.0f) {
    //     targetSpeed *= 6.25 / m->quicksandDepth;
    // }

    if (this->intended_mag == 0) // ACT_BRAKING
        this->forward_vel = approach_i32(forward_vel, 0, 2 * 256, 2 * 256);

    // {
    //     i16 dyaw = (i16)(this->intended_yaw - this->yaw);

    //     if ((dyaw < -0x471C || dyaw > 0x471C) && this->forward_vel >= 16 * 256)

    // }

    if (this->forward_vel == 0)
        this->yaw = this->intended_yaw;
	if (this->forward_vel < 0)
        this->forward_vel = std::min(this->forward_vel + 282, 0); // += 1.1f
	else if (this->forward_vel < target_speed)
		this->forward_vel += 282 - this->forward_vel / 43; // 1.1f - vel / 43
	else //if (m->floor->normal.y >= 0.95f)
        this->forward_vel = std::max(this->forward_vel - 256, 0);
	
	if (this->forward_vel > 12288) // 48.0f
		this->forward_vel = 12288;
	this->yaw = this->intended_yaw - approach_i32((i16)(this->intended_yaw - this->yaw), 0, 0x800, 0x800);
	this->applySlopeAccel();
}

void	MarioControl::applySlopeAccel()
{
	// f32 slopeAccel;

    // struct Surface *floor = m->floor;
    // f32 steepness = sqrtf(floor->normal.x * floor->normal.x + floor->normal.z * floor->normal.z);

    // UNUSED f32 normalY = floor->normal.y;
    // s16 floorDYaw = m->floorAngle - m->faceAngle[1];

    // if (mario_floor_is_slope(m)) {
    //     s16 slopeClass = 0;

    //     if (m->action != ACT_SOFT_BACKWARD_GROUND_KB && m->action != ACT_SOFT_FORWARD_GROUND_KB) {
    //         slopeClass = mario_get_floor_class(m);
    //     }

    //     switch (slopeClass) {
    //         case SURFACE_CLASS_VERY_SLIPPERY:
    //             slopeAccel = 5.3f;
    //             break;
    //         case SURFACE_CLASS_SLIPPERY:
    //             slopeAccel = 2.7f;
    //             break;
    //         default:
    //             slopeAccel = 1.7f;
    //             break;
    //         case SURFACE_CLASS_NOT_SLIPPERY:
    //             slopeAccel = 0.0f;
    //             break;
    //     }

    //     if (floorDYaw > -0x4000 && floorDYaw < 0x4000) {
    //         m->forwardVel += slopeAccel * steepness;
    //     } else {
    //         m->forwardVel -= slopeAccel * steepness;
    //     }
    // }
	// m->slideYaw = m->faceAngle[1];
    // m->slideVelX = m->forwardVel * sins(m->faceAngle[1]);
    // m->slideVelZ = m->forwardVel * coss(m->faceAngle[1]);

	i32 sin = fixed::sincos(this->yaw);
	i32 cos = (sin << 16) >> 16;
	sin >>= 16;
	this->velocity_x = (this->forward_vel * sin) >> 14;
	this->velocity_y = 0;
	this->velocity_z = (this->forward_vel * cos) >> 14;

	// mario_update_moving_sand(m);
    // mario_update_windy_ground(m);
}
