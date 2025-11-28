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

#ifndef VTABLEVIEW_H
#define VTABLEVIEW_H

#include <QHeaderView>
#include <QTableView>
#include <QStyledItemDelegate>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include "vsvgrenderer.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VTableView : public QTableView
{
	Q_OBJECT

public:
	VTableView(QWidget* parent = nullptr);

	void setItemDelegate(QAbstractItemDelegate* item_delegate);

	void update();

	void update_height();

private:
	// Layers::LAttribute* m_border_fill{
	// 	lMakeDefinableAttribute(this, "Border.Fill", "#a0a0a4") };

	// Layers::LAttribute* m_border_thickness{
	// 	lMakeDefinableAttribute(this, "Border.Thickness", 3.0) };

	// Layers::LAttribute* m_corner_radii_bottom_left{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Bottom Left", 5.0) };

	// Layers::LAttribute* m_corner_radii_bottom_right{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Bottom Right", 5.0) };

	// Layers::LAttribute* m_corner_radii_top_left{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Top Left", 5.0) };

	// Layers::LAttribute* m_corner_radii_top_right{
	// 	lMakeDefinableAttribute(this, "Corner Radii.Top Right", 5.0) };

	// Layers::LAttribute* m_fill{
	// 	lMakeDefinableAttribute(this, "Fill", "#ffffff") };

	// Layers::LAttribute* m_item_fill{
	// 	lMakeDefinableAttribute(this, "Item Fill", "#ffffff") };

	// Layers::LAttribute* m_text_color{
	// 	lMakeDefinableAttribute(this, "Text Color", "#000000") };


	QAbstractItemDelegate* m_table_delegate{ nullptr };

	int m_visible_row_limit{ 3 };
};
VORTEX_NAMESPACE_END

#endif // VTABLEVIEW_H
