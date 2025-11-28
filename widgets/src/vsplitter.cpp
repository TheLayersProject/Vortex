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

#include <VortexWidgets/vsplitter.h>

using Vortex::VSplitter;

VSplitter::VSplitter(QWidget* parent) :
	QSplitter(parent)
{
	init();
}

VSplitter::VSplitter(Qt::Orientation orientation, QWidget* parent) :
	QSplitter(orientation, parent)
{
	init();
}

void VSplitter::init()
{
	setObjectName("Splitter");
	setHandleWidth(20);
}
