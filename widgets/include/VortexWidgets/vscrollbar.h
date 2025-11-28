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

#ifndef VSCROLLBAR_H
#define VSCROLLBAR_H

#include <QScrollBar>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VScrollBar : public QScrollBar
{
	Q_OBJECT

public:
	VScrollBar(QWidget* parent = nullptr);

	Layers::LAttribute* background_color() const;

	Layers::LAttribute* corner_radii_bottom_left() const;

	Layers::LAttribute* corner_radii_bottom_right() const;

	Layers::LAttribute* corner_radii_top_left() const;

	Layers::LAttribute* corner_radii_top_right() const;

	Layers::LAttribute* handle_color() const;

	Layers::LAttribute* handle_corner_radii_bottom_left() const;

	Layers::LAttribute* handle_corner_radii_bottom_right() const;

	Layers::LAttribute* handle_corner_radii_top_left() const;

	Layers::LAttribute* handle_corner_radii_top_right() const;

	void update();

private:
	// Layers::LAttribute* m_background_color{
	// 	lMakeDefinableAttribute(this, "Background Color", "#a0a0a4") };

	// Layers::LAttribute* m_corner_radii_bottom_left{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Bottom Left", 0.0) };

	// Layers::LAttribute* m_corner_radii_bottom_right{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Bottom Right", 0.0) };

	// Layers::LAttribute* m_corner_radii_top_left{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Top Left", 0.0) };

	// Layers::LAttribute* m_corner_radii_top_right{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Top Right", 0.0) };

	// Layers::LAttribute* m_handle_color{
	// 	lMakeDefinableAttribute(this, "Handle Color", "#ffffff") };

	// Layers::LAttribute* m_handle_corner_radii_bottom_left{
	// 	lMakeDefinableAttribute(this, "Handle Corner Radii.Bottom Left", 5.0) };

	// Layers::LAttribute* m_handle_corner_radii_bottom_right{
	// 	lMakeDefinableAttribute(this, "Handle Corner Radii.Bottom Right", 5.0) };

	// Layers::LAttribute* m_handle_corner_radii_top_left{
	// 	lMakeDefinableAttribute(this, "Handle Corner Radii.Top Left", 5.0) };

	// Layers::LAttribute* m_handle_corner_radii_top_right{
	// 	lMakeDefinableAttribute(this, "Handle Corner Radii.Top Right", 5.0) };
};
VORTEX_NAMESPACE_END

#endif // VSCROLLBAR_H
