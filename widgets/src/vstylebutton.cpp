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

#include <VortexWidgets/vstylebutton.h>

#include <QMouseEvent>
#include <QVBoxLayout>

#include <Layers/lstyle.h>

using Layers::LAttributeMap;
using Layers::LString;
using Layers::LStyle;
using Layers::LVariant;
using Vortex::VLabel;
using Vortex::VStyleButton;

VStyleButton::VStyleButton(LStyle* style, QWidget* parent) :
	m_name_label{ new VLabel(style->object_name().c_str()) },
	m_publisher_label{ new VLabel(style->publisher().c_str()) },
	QWidget(parent)
{
	init_layout();
	//init_style(theme);
	installEventFilter(this);
	setFixedHeight(60);
	setObjectName("Style Button");
	//set_corner_radii(5.0);
	//border_thickness()->set_value(2.0);

	m_name_label->set_bold();
	m_name_label->setObjectName("Name Label");

	m_publisher_label->set_font_size_f(10.5);
	m_publisher_label->setObjectName("Publisher Label");
}

bool VStyleButton::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		setCursor(Qt::PointingHandCursor);
	}
	else if (event->type() == QEvent::Leave)
	{
		unsetCursor();
	}
	else if (
		event->type() == QEvent::MouseButtonPress ||
		event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
			emit clicked();
	}

	return false;
}

void VStyleButton::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->addWidget(m_name_label, Qt::AlignLeft);
	main_layout->addWidget(m_publisher_label, Qt::AlignLeft);
	main_layout->setContentsMargins(17, 9, 6, 8);
	main_layout->setSpacing(0);
	setLayout(main_layout);
}

//void VStyleButton::init_style(LTheme* theme)
//{
//	LAttributeMap attributes = theme->attributes();
//
//	if (attributes.count("Foreground"))
//	{
//		LVariant foreground_val = attributes["Foreground"]->value();
//
//		m_name_label->text_color()->set_value(foreground_val);
//		m_publisher_label->text_color()->set_value(foreground_val);
//	}
//
//	if (attributes.count("Primary"))
//		fill()->set_value(attributes["Primary"]->value());
//
//	if (attributes.count("Tertiary"))
//		border_fill()->set_value(attributes["Tertiary"]->value());
//}
