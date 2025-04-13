#include "gba/audio/audio.h"
#include "gba/gbadef.h"

namespace audio
{
	void	init()
	{
		REG_TIMER1 = (0xBF89 << 16) | TIMER_ENABLE_BIT | TIMER_INTERRUPT_REQUEST_BIT | TIMER_FREQUENCY_1_BIT;
	}
}
