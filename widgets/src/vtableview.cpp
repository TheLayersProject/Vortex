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

#include <VortexWidgets/vtableview.h>

#include <QPainter>

#include <VortexWidgets/vheaderview.h>
#include <VortexWidgets/vgridlineitemdelegate.h>

#include <Layers/lstring.h>

using Layers::LString;

using Vortex::VGridlineItemDelegate;
using Vortex::VSvgRenderer;
using Vortex::VTableView;

VTableView::VTableView(QWidget* parent) : QTableView(parent)
{
	update();

	//setItemDelegate(new VGridlineItemDelegate);

	setHorizontalHeader(new VHeaderView(Qt::Horizontal));

	horizontalHeader()->setStretchLastSection(true);
	horizontalHeader()->setMinimumHeight(40);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	setShowGrid(false);
	verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
	verticalHeader()->setDefaultSectionSize(48);
	verticalHeader()->hide();
}

// QList<QLStylable*> VTableView::child_qlstylables(Qt::FindChildOptions options)
// {
// 	QList<QLStylable*> child_qlstylables =
// 		QLStylable::child_qlstylables(options);

// 	if (QLStylable* child_themeable_item_delegate =
// 		dynamic_cast<QLStylable*>(itemDelegate()))
// 	{
// 		child_qlstylables.append(child_themeable_item_delegate);

// 		if (options == Qt::FindChildrenRecursively)
// 		{
// 			QList<QObject*> delegate_child_objects =
// 				itemDelegate()->findChildren<QObject*>(options);

// 			for (QObject* delegate_child_object : delegate_child_objects)
// 				if (QLStylable* child_themeable =
// 					dynamic_cast<QLStylable*>(delegate_child_object))
// 				{
// 					child_qlstylables.append(child_themeable);
// 				}
// 		}
// 	}

// 	return child_qlstylables;
// }

void VTableView::setItemDelegate(QAbstractItemDelegate* item_delegate)
{
	if (VGridlineItemDelegate* themeable_item_delegate =
		dynamic_cast<VGridlineItemDelegate*>(item_delegate))
	{
		connect(themeable_item_delegate, &VGridlineItemDelegate::changed,
			[this] { QWidget::update(); });
	}
	
	QTableView::setItemDelegate(item_delegate);
}

void VTableView::update()
{
	// QString style_sheet =
	// 	"QTableView {"
	// 	"background: " +
	// 		QString::fromStdString(m_fill->as<LString>().c_str()) + ";"
	// 	"border: " + QString::number(m_border_thickness->as<double>()) + "px "
	// 		"solid " +
	// 			QString::fromStdString(m_border_fill->as<LString>().c_str()) + ";"
	// 	"border-top-left-radius: " +
	// 		QString::number(m_corner_radii_top_left->as<double>()) + "px;"
	// 	"border-top-right-radius: " +
	// 		QString::number(m_corner_radii_top_right->as<double>()) + "px;"
	// 	"border-bottom-left-radius: " +
	// 		QString::number(m_corner_radii_bottom_left->as<double>()) + "px;"
	// 	"border-bottom-right-radius: " +
	// 		QString::number(m_corner_radii_bottom_right->as<double>()) + "px;"
	// 	"color: " +
	// 		QString::fromStdString(m_text_color->as<LString>().c_str()) + ";"
	// 	"}"

	// 	"QTableView::item {"
	// 	"background: " +
	// 		QString::fromStdString(m_item_fill->as<LString>().c_str()) + ";"
	// 	"}";

	// setStyleSheet(style_sheet);

	QWidget::update();
}

void VTableView::update_height()
{
	int visible_row_count = model()->rowCount() < m_visible_row_limit ?
		model()->rowCount() : m_visible_row_limit;

	//int new_height = m_border_thickness->as<double>() * 2;
	int new_height = 2;

	new_height += horizontalHeader()->height();

	for (auto i = visible_row_count; i--;)
		new_height += verticalHeader()->sectionSize(i);

	setMaximumHeight(new_height);
}
