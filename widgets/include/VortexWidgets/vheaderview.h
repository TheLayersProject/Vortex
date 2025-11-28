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

#ifndef VHEADERVIEW_H
#define VHEADERVIEW_H

#include <QHeaderView>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

//#include "vstylable.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VHeaderView : public QHeaderView
{
	Q_OBJECT

public:
	VHeaderView(Qt::Orientation orientation, QWidget* parent = nullptr);

	void update();

private:
	// Layers::LAttribute* m_border_fill{
	// 	lMakeDefinableAttribute(this, "Border.Fill", "#a0a0a4") };

	// Layers::LAttribute* m_border_thickness{
	// 	lMakeDefinableAttribute(this, "Border.Thickness", 0.0) };

	// Layers::LAttribute* m_corner_radii_bottom_left{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Bottom Left", 0.0) };

	// Layers::LAttribute* m_corner_radii_bottom_right{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Bottom Right", 0.0) };

	// Layers::LAttribute* m_corner_radii_top_left{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Top Left", 2.0) };

	// Layers::LAttribute* m_corner_radii_top_right{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Top Right", 2.0) };

	// Layers::LAttribute* m_fill{
	// 	lMakeDefinableAttribute(this, "Fill", "#808080") };

	// Layers::LAttribute* m_text_color{
	// 	lMakeDefinableAttribute(this, "Text Color", "#000000") };

};
VORTEX_NAMESPACE_END

#endif // VHEADERVIEW_H  

