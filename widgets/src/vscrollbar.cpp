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

#include <VortexWidgets/vscrollbar.h>

#include <Layers/lstring.h>

using Layers::LAttribute;
using Layers::LString;

using Vortex::VScrollBar;

VScrollBar::VScrollBar(QWidget* parent) : QScrollBar(parent)
{
	setObjectName("ScrollBar");
	update();
}

// LAttribute* VScrollBar::background_color() const
// {
// 	return m_background_color;
// }

// LAttribute* VScrollBar::corner_radii_bottom_left() const
// {
// 	return m_corner_radii_bottom_left;
// }

// LAttribute* VScrollBar::corner_radii_bottom_right() const
// {
// 	return m_corner_radii_bottom_right;
// }

// LAttribute* VScrollBar::corner_radii_top_left() const
// {
// 	return m_corner_radii_top_left;
// }

// LAttribute* VScrollBar::corner_radii_top_right() const
// {
// 	return m_corner_radii_top_right;
// }

// LAttribute* VScrollBar::handle_color() const
// {
// 	return m_handle_color;
// }

// LAttribute* VScrollBar::handle_corner_radii_bottom_left() const
// {
// 	return m_handle_corner_radii_bottom_left;
// }

// LAttribute* VScrollBar::handle_corner_radii_bottom_right() const
// {
// 	return m_handle_corner_radii_bottom_right;
// }

// LAttribute* VScrollBar::handle_corner_radii_top_left() const
// {
// 	return m_handle_corner_radii_top_left;
// }

// LAttribute* VScrollBar::handle_corner_radii_top_right() const
// {
// 	return m_handle_corner_radii_top_right;
// }

void VScrollBar::update()
{
	// QString o = (orientation() == Qt::Horizontal) ?
	// 	"horizontal" : "vertical";

	// QString style_sheet =
	// 	"QScrollBar:" + o + " {"
	// 	"background: " +
	// 		QString::fromStdString(m_background_color->as<LString>().c_str()) + ";"
	// 	"border-top-left-radius: " +
	// 		QString::number(m_corner_radii_top_left->as<double>()) + "px;"
	// 	"border-top-right-radius: " +
	// 		QString::number(m_corner_radii_top_right->as<double>()) + "px;"
	// 	"border-bottom-left-radius: " +
	// 		QString::number(m_corner_radii_bottom_left->as<double>()) + "px;"
	// 	"border-bottom-right-radius: " +
	// 		QString::number(m_corner_radii_bottom_right->as<double>()) + "px;"
	// 	"margin: 0px 0px 0px 0px;";

	// if (orientation() == Qt::Horizontal)
	// 	style_sheet += "height: 40px;";
	// else
	// 	style_sheet += "width: 40px;";

	// style_sheet += "}";

	// style_sheet +=
	// 	"QScrollBar::handle:" + o + " {"
	// 	"background: " +
	// 		QString::fromStdString(m_handle_color->as<LString>().c_str()) + ";"
	// 	"border-top-left-radius: " +
	// 		QString::number(m_handle_corner_radii_top_left->as<double>()) + "px;"
	// 	"border-top-right-radius: " +
	// 		QString::number(m_handle_corner_radii_top_right->as<double>()) + "px;"
	// 	"border-bottom-left-radius: " +
	// 		QString::number(m_handle_corner_radii_bottom_left->as<double>()) + "px;"
	// 	"border-bottom-right-radius: " +
	// 		QString::number(m_handle_corner_radii_bottom_right->as<double>()) + "px;"
	// 	"margin: 7px 7px 7px 7px;";
		
	// if (orientation() == Qt::Horizontal)
	// 	style_sheet += "min-width: 26px;";
	// else
	// 	style_sheet += "min-height: 26px;";

	// style_sheet += "}";

	// style_sheet +=
	// 	"QScrollBar::add-line:" + o + " {"
	// 	"border: none;"
	// 	"background: none;"
	// 	"}"
	// 	"QScrollBar::sub-line:" + o + " {"
	// 	"height: 0px;"
	// 	"width: 0px;"
	// 	"border: none;"
	// 	"background: none;"
	// 	"}"
	// 	"QScrollBar:up-arrow:" + o + ", QScrollBar::down-arrow:" + o + " {"
	// 	"border: none;"
	// 	"background: none;"
	// 	"color: none;"
	// 	"}"
	// 	"QScrollBar::add-page:" + o + ", QScrollBar::sub-page:" + o + " {"
	// 	"background: none;"
	// 	"}";

	//setStyleSheet(style_sheet);
}
