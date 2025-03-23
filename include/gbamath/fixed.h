#pragma once

#include "common.h"

namespace fixed
{
	/**
	 * @param {f} Q16.16 (unsigned)
	 * @returns Q16.16 (unsigned)
	 */
	u32	sqrt(u32 f);
	/**
	 * @param {angle} Q16.16 (unsigned)
	 * @returns (Q1.14 | Q1.14), 0 ~ 15bit -> cosine, 16 ~ 31bit -> sine
	 */
	u32	sincos(u32 angle);
}
