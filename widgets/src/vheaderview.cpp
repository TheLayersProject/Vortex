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

#include <VortexWidgets/vheaderview.h>

#include <QPainter>

#include <Layers/lstring.h>

using Layers::LString;

using Vortex::VHeaderView;

VHeaderView::VHeaderView(Qt::Orientation orientation, QWidget* parent) :
	QHeaderView(orientation, parent)
{
	update();

	if (orientation == Qt::Horizontal)
		setObjectName("Horizontal Header");
	else
		setObjectName("Vertical Header");
}

void VHeaderView::update()
{
	// setStyleSheet(
	// 	"QHeaderView {"
	// 	"background: " +
	// 		QString::fromStdString(m_fill->as<LString>().c_str()) + ";"
	// 	"border-top-left-radius: "
	// 		+ QString::number(m_corner_radii_top_left->as<double>()) + "px;"
	// 	"border-top-right-radius: "
	// 		+ QString::number(m_corner_radii_top_right->as<double>()) + "px;"
	// 	"border-bottom-left-radius: "
	// 		+ QString::number(m_corner_radii_bottom_left->as<double>()) + "px;"
	// 	"border-bottom-right-radius: "
	// 		+ QString::number(m_corner_radii_bottom_right->as<double>()) + "px;"
	// 	"color: " +
	// 		QString::fromStdString(m_text_color->as<LString>().c_str()) + ";"
	// 	"}"

	// 	"QHeaderView::section {"
	// 	"background: transparent;"
	// 	"}"
	// );

	QWidget::update();
}
