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

#ifndef VCONVERT_H
#define VCONVERT_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>

#include <QGradientStops>

#include "vortex_core_global.h"
#include "vortex_core_export.h"

#include <Layers/lstring.h>

VORTEX_NAMESPACE_BEGIN

inline VORTEX_CORE_EXPORT
QGradientStops to_QGradientStops(const QStringList& stops)
{
	QGradientStops q_gradient_stops;

	for (const auto& stop : stops)
	{
		QStringList parts = stop.split(':');
		if (parts.size() != 2)
		{
			std::cerr << "Invalid gradient stop format: " << stop.toStdString() << std::endl;
			continue;
		}

		bool ok;
		qreal position = parts[0].toDouble(&ok);
		if (!ok)
		{
			std::cerr << "Invalid position in gradient stop: " << parts[0].toStdString() << std::endl;
			continue;
		}

		QColor color(parts[1]);
		if (!color.isValid())
		{
			std::cerr << "Invalid color in gradient stop: " << parts[1].toStdString() << std::endl;
			continue;
		}

		q_gradient_stops.append(QGradientStop(position, color));
	}

	return q_gradient_stops;
}

inline VORTEX_CORE_EXPORT
QGradientStops to_QGradientStops(const Layers::LStringList& stops)
{
	QStringList qstring_stops;
	for (const auto& stop : stops)
		qstring_stops.append(QString::fromStdString(stop.c_str()));
	
	return to_QGradientStops(qstring_stops);
}

inline VORTEX_CORE_EXPORT
Layers::LStringList to_LStringList(const QStringList& qstring_list)
{
	Layers::LStringList lstring_list;

	for (const auto& str : qstring_list)
		lstring_list.push_back(
			Layers::LString(str.toStdString().c_str()));

	return lstring_list;
}

VORTEX_NAMESPACE_END

#endif // !QLCONVERT_H
