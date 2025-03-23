#pragma once

#include "common.h"

namespace fixed
{

	/**
	 * @param {f} Q15.16
	 * @returns Q15.16
	 */
	i32	sqrt(i32 f);
	/**
	 * @param {angle} Q16.16 (unsigned)
	 * @returns (Q0.15 | Q0.15), 0 ~ 15bit -> cosine, 16 ~ 31bit -> sine
	 */
	u32	sincos(u32 angle);
}
