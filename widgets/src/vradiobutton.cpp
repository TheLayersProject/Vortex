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

#include "VortexWidgets/vradiobutton.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

#include <Layers/lstring.h>
#include <VortexCore/vboxstyle.h>

using Layers::LAttribute;
using Layers::LString;

using Vortex::VRadioButton;
using Vortex::VStatePool;

VRadioButton::VRadioButton(QWidget* parent) : QWidget(parent)
{
	Vortex::add_state_pool(this, m_status_states);
	installEventFilter(this);
	setFixedSize(40, 40);

	m_status_states->set_state("Inactive");
}

VStatePool* VRadioButton::status_states() const
{
	return m_status_states;
}

bool VRadioButton::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress)
		if (static_cast<QMouseEvent*>(event)->button() & Qt::LeftButton)
			emit clicked();

	return false;
}

void VRadioButton::paintEvent(QPaintEvent* event)
{
	// QPainter painter(this);
	// painter.setRenderHint(QPainter::Antialiasing);

	// auto sc = state_combo();

	// int border_thickness = m_border_thickness->as<double>(sc);
	// qreal margin = m_margin->as<qreal>(sc);

	// qreal radius_h = (width() / 2) - margin;
	// qreal radius_v = (height() / 2) - margin;

	// // Fill
	// QPainterPath fill_path;
	// fill_path.addEllipse(rect().center(),
	// 	radius_h - border_thickness, radius_v - border_thickness);

	// painter.fillPath(fill_path,
	// 	QColor(QString::fromStdString(m_fill->as<LString>(sc).c_str())));

	// // Border
	// QPainterPath border_path;
	// border_path.addEllipse(rect().center(),
	// 	radius_h, radius_v);
	// border_path = border_path - fill_path;

	// if (border_thickness)
	// 	painter.fillPath(border_path,
	// 		QColor(QString::fromStdString(m_border_fill->as<LString>(sc).c_str())));

	// // Active Dot
	// // TEMP: Disabled
	// //if (std::find(s.begin(), s.end(), "Active") != s.end())
	// //{
	// //	QPainterPath active_dot_path;
	// //	active_dot_path.addEllipse(rect().center(),
	// //		radius_h * 0.385, radius_v * 0.385);

	// //	painter.fillPath(active_dot_path,
	// //		QColor(QString::fromStdString(
	// //			m_active_dot_fill->as<LString>(d).c_str())));
	//}
}