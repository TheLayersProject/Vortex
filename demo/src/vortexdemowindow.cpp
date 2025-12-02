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

#include "vortexdemowindow.h"

#include <VortexWidgets/vgraphic.h>

#include "vortexdemo.h"

using Vortex::VGraphic;

VortexDemoWindow::VortexDemoWindow(QWidget* parent) :
	VMainWindow(parent)
{
	std::unique_ptr<VGraphic> logo_graphic =
		std::make_unique<VGraphic>(":/images/vortex_logo.svg", QSize(35, 35));
	logo_graphic->svg_renderer()->exclude_from_theme("black_holes");
	logo_graphic->svg_renderer()->exclude_from_theme("stars");

	VortexDemo* vortex_demo = new VortexDemo;

	open_central_widget(vortex_demo, std::move(logo_graphic), "Vortex");

	setWindowIcon(QIcon("demo/vortex.ico"));
}
