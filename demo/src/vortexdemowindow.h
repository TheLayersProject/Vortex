/*
 * Copyright (C) 2023 The Layers Project
 *
 * This file is part of the Vortex Demo application.
 *
 * Vortex Demo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Vortex Demo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Vortex Demo. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VORTEXDEMOWINDOW_H
#define VORTEXDEMOWINDOW_H

#include <VortexWidgets/vmainwindow.h>

class VortexDemoWindow : public Vortex::VMainWindow
{
	Q_OBJECT

public:
	VortexDemoWindow(QWidget* parent = nullptr);

private:
};

#endif // VORTEXDEMOWINDOW_H
