#pragma once

namespace gba
{
	typedef void					(*t_isr)(void);
	typedef struct s_audio_context	t_audio_context;
	typedef struct s_track			t_track;
	
	void	init();
	void	setInterruptHandler(InterruptID id, t_isr handler);
}//3 + 9 + 7 = 19