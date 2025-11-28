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

#ifndef VMENUBAR_H
#define VMENUBAR_H

#include <QMenuBar>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VMenuBar : public QMenuBar
{
	Q_OBJECT

public:
	VMenuBar(QWidget* parent = nullptr);

	Layers::LAttribute* selected_text_color() const;

	Layers::LAttribute* text_color() const;

	void update();

private:
	//QString build_stylesheet();

	// Layers::LAttribute* m_selected_text_color{
	// 	lMakeDefinableAttribute(this, "selected_text_color", "#c0c0c0") };

	// Layers::LAttribute* m_text_color{
	// 	lMakeDefinableAttribute(this, "Text Color", "#a0a0a4") };
};
VORTEX_NAMESPACE_END

#endif // VMENUBAR_H
