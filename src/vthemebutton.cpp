/*
 * Copyright (C) 2025 The Layers Project
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

#include <Vortex/vthemebutton.h>

#include <QMouseEvent>
#include <QVBoxLayout>

#include <QLayers/boxstyle.h>

using Layers::LAttributeMap;
using Layers::LString;
using Layers::LStyle;
using Layers::LTheme;
using Layers::LVariant;
using QLayers::QLLabel;
using Vortex::VThemeButton;

VThemeButton::VThemeButton(LTheme* theme, QWidget* parent) :
	m_name_label{ new QLLabel(theme->object_name().c_str()) },
	m_publisher_label{ new QLLabel(theme->publisher().c_str()) },
	QWidget(parent)
{
	init_layout();
	installEventFilter(this);
	setFixedHeight(60);
	//set_corner_radii(5.0);
	//border_thickness()->set_value(2.0);

	m_name_label->set_bold();
	m_name_label->setObjectName("Theme Name Label");

	m_publisher_label->set_font_size_f(10.5);
	m_publisher_label->setObjectName("Theme Publisher Label");

	init_style(theme);
}

bool VThemeButton::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		setCursor(Qt::PointingHandCursor);
	}
	else if (event->type() == QEvent::Leave)
	{
		unsetCursor();
	}
	else if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
			emit clicked();
	}

	return false;
}

// void VThemeButton::paintEvent(QPaintEvent* event)
// {
//     // Explicitly tell the style to draw PE_Widget for us
//     QStyleOption opt;
//     opt.initFrom(this);
    
//     QPainter painter(this);
//     style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    
//     // Let base class handle the rest
//     QWidget::paintEvent(event);
// }

void VThemeButton::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->addWidget(m_name_label, Qt::AlignLeft);
	main_layout->addWidget(m_publisher_label, Qt::AlignLeft);
	main_layout->setContentsMargins(17, 9, 6, 8);
	main_layout->setSpacing(0);
	setLayout(main_layout);
}

void VThemeButton::init_style(LTheme* theme)
{
	LStyle* style = new LStyle;

	LAttributeMap attributes = theme->attributes();

	if (attributes.count("Foreground"))
	{
		// LVariant foreground_val = attributes["Foreground"]->value();

		// m_name_label->text_color()->set_value(foreground_val);
		// m_publisher_label->text_color()->set_value(foreground_val);

		auto name_label_style = std::make_unique<LStyle>();
		name_label_style->set_object_name("Theme Name Label");
		name_label_style->add_child(std::make_unique<Layers::LAttribute>(
			"Text Color", attributes["Foreground"]->value()));
		
		auto publisher_label_style = std::make_unique<LStyle>();
		publisher_label_style->set_object_name("Theme Publisher Label");
		publisher_label_style->add_child(std::make_unique<Layers::LAttribute>(
			"Text Color", attributes["Foreground"]->value()));
		
		style->add_child(std::move(name_label_style));
		style->add_child(std::move(publisher_label_style));
	}

	if (attributes.count("Primary"))
		style->add_child(std::make_unique<Layers::LAttribute>(
			"Fill", attributes["Primary"]->value()));

	if (attributes.count("Tertiary"))
	{
		style->add_child(std::make_unique<Layers::LAttribute>(
			"Border.Thickness", 2.0));
		style->add_child(std::make_unique<Layers::LAttribute>(
			"Border.Fill", attributes["Tertiary"]->value()));
	}

	style->add_child(std::make_unique<Layers::LAttribute>(
		"Corner Radii.Top Left", 5.0));

	style->add_child(std::make_unique<Layers::LAttribute>(
		"Corner Radii.Top Right", 5.0));

	style->add_child(std::make_unique<Layers::LAttribute>(
		"Corner Radii.Bottom Left", 5.0));

	style->add_child(std::make_unique<Layers::LAttribute>(
		"Corner Radii.Bottom Right", 5.0));

	QLayers::apply_layers_style(this, style);

	update();
}
