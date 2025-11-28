/*
 * Copyright (C) 2025 Huntr Software LLC
 *
 * This file is part of Vortex.
 *
 * Vortex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Vortex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Vortex. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VCALCULATE_H
#define VCALCULATE_H

#include <cmath>

#include "vortex_core_global.h"
#include "vortex_core_export.h"

VORTEX_NAMESPACE_BEGIN

VORTEX_CORE_EXPORT inline double round(double d)
{
	return floor(d + 0.5);
}

VORTEX_CORE_EXPORT inline bool is_even(int i)
{
	if (i % 2) return false;

	return true;
}

VORTEX_CORE_EXPORT inline double inner_radius(int outer_radius, int thickness)
{
	double value = outer_radius - thickness;

	if (value < 0.0)
		return 0.0;

	return value;
}

VORTEX_NAMESPACE_END

#endif // VCALCULATE_H
