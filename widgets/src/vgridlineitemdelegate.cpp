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

#include <VortexWidgets/vgridlineitemdelegate.h>

#include <QPainter>

#include <Layers/lstring.h>
#include <Layers/lstyle.h>
#include <VortexCore/vboxstyle.h>

using Layers::LAttribute;
using Layers::LString;

using Vortex::VGridlineItemDelegate;

VGridlineItemDelegate::VGridlineItemDelegate(QObject* parent) :
	QStyledItemDelegate(parent)
{
	setObjectName("Cells");
}

// LAttribute* VGridlineItemDelegate::grid_fill() const
// {
// 	return m_grid_fill;
// }

// LAttribute* VGridlineItemDelegate::grid_thickness() const
// {
// 	return m_grid_thickness;
// }

void VGridlineItemDelegate::paint(
	QPainter* painter,
	const QStyleOptionViewItem& option,
	const QModelIndex& index) const
{
	QStyledItemDelegate::paint(painter, option, index);

	QColor grid_fill = QColor(Qt::black);

	double grid_thickness = 1.0;

	Layers::LStyle* style = Vortex::get_widget_lstyle(this);

	if (style)
	{
		LAttribute* grid_fill_attr =
			style->find_attribute("Grid.Fill");
		LAttribute* grid_thickness_attr =
			style->find_attribute("Grid.Thickness");

		if (grid_fill_attr)
		{
			grid_fill = QColor(
				QString::fromStdString(grid_fill_attr->as<LString>().c_str()));
		}

		if (grid_thickness_attr)
		{
			grid_thickness = grid_thickness_attr->as<double>();
		}
	}

	if (index.row() < index.model()->rowCount() - 1)
	{
		QRect border_rect_bottom = QRect(
			option.rect.x(),
			option.rect.y() + option.rect.height() - grid_thickness,
			option.rect.width(),
			grid_thickness
		);
		painter->fillRect(border_rect_bottom, grid_fill);
	}

	if (index.column() < index.model()->columnCount() - 1)
	{
		QRect border_rect_right = QRect(
			option.rect.x() + option.rect.width() - grid_thickness,
			option.rect.y(),
			grid_thickness,
			option.rect.height()
		);
		painter->fillRect(border_rect_right, grid_fill);
	}
}
