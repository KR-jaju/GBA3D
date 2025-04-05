// #include "InputState.h"

// void	pollInput(InputState *state)
// {
// 	state->prev = state->curr;
//     state->curr = ~REG_KEYINPUT & KEY_MASK;

// 	state->h_raw = ((state->curr >> KEY_RIGHT_IDX) & 1) - ((state->curr >> KEY_LEFT_IDX) & 1);
// 	state->v_raw = ((state->curr >> KEY_UP_IDX) & 1) - ((state->curr >> KEY_DOWN_IDX) & 1);

// 	if (state->h_raw != 0 || state->v_raw != 0)
// 		state->stick_mag = 1;
// 	else
// 		state->stick_mag = 0;
// 	state->stick_angle = 0;
// 	if (state->h_raw == 1) {
// 		state->stick_angle += 16384;
// 		state->stick_angle += state->v_raw * -8192;
// 	} else {
// 		state->stick_angle += -16384;
// 		state->stick_angle += (state->v_raw) * (state->h_raw + 2) * 8192;
// 	}
// }