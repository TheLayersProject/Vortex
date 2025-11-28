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

#include <VortexWidgets/vbutton.h>

#include <QMouseEvent>
#include <VortexCore/vboxstyle.h>
#include <VortexWidgets/vgraphic.h>

using Layers::LAttribute;
using Vortex::VLabel;
using Vortex::VButton;

VButton::VButton(std::unique_ptr<VGraphic> graphic, const QString& text, QWidget* parent) :
	m_graphic_label{ new VLabel(std::move(graphic)) },
	m_text_label{ new VLabel(text) },
	QWidget(parent)
{
	init();
	
	//m_corner_radii_top_left->set_value(7.0);
	//m_corner_radii_top_right->set_value(7.0);
	//m_corner_radii_bottom_left->set_value(7.0);
	//m_corner_radii_bottom_right->set_value(7.0);
}

VButton::VButton(std::unique_ptr<VGraphic> graphic, QWidget* parent) :
	m_graphic_label{ new VLabel(std::move(graphic)) },
	QWidget(parent)
{
	init();
}

VButton::VButton(const QString& text, QWidget* parent) :
	m_text_label{ new VLabel(text) },
	QWidget(parent)
{
	init();

	//m_corner_radii_top_left->set_value(7.0);
	//m_corner_radii_top_right->set_value(7.0);
	//m_corner_radii_bottom_left->set_value(7.0);
	//m_corner_radii_bottom_right->set_value(7.0);
}

VButton::VButton(
	std::unique_ptr<VGraphic> graphic,
	std::unique_ptr<VGraphic> graphic_after,
	QWidget* parent) :
	m_graphic_label{ new VLabel(std::move(graphic)) },
	m_graphic_after_label{ new VLabel(std::move(graphic_after)) },
	QWidget(parent)
{
	init();
}

bool VButton::disabled() const
{
	return m_disabled;
}

VLabel* VButton::graphic_label() const
{
	return m_graphic_label;
}

QHBoxLayout* VButton::layout() const
{
	return m_main_layout;
}

void VButton::set_disabled(bool cond)
{
	m_disabled = cond;

	if (m_disabled)
	{
		if (m_button_opacity->opacity() != 0.25)
			m_button_opacity->setOpacity(0.25);
	}
	else if (!m_disabled)
	{
		if (m_button_opacity->opacity() != 1.0)
			m_button_opacity->setOpacity(1.0);
	}
}

void VButton::set_font_size(int size)
{
	if (m_text_label)
		m_text_label->set_font_size(size);
}

void VButton::set_font_size_f(qreal size)
{
	if (m_text_label)
		m_text_label->set_font_size_f(size);
}

void VButton::set_padding(int padding)
{
	m_main_layout->setContentsMargins(padding, padding, padding, padding);
}

void VButton::set_padding(int left, int top, int right, int bottom)
{
	m_main_layout->setContentsMargins(left, top, right, bottom);
}

void VButton::set_pointing_hand_cursor(bool use_cursor)
{
	m_use_pointing_hand_cursor = use_cursor;
}

VLabel* VButton::text_label() const
{
	return m_text_label;
}

void VButton::toggle_graphics()
{
	if (m_graphic_after_label)
	{
		if (m_graphic_label->isVisible())
		{
			m_graphic_label->hide();
			m_graphic_after_label->show();
		}
		else
		{
			m_graphic_label->show();
			m_graphic_after_label->hide();
		}
	}
}

bool VButton::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::MouseButtonPress || event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			if (!m_disabled)
				emit clicked();

			toggle_graphics();
		}
	}
	else if (event->type() == QEvent::Enter)
	{
		if (!m_disabled)
		{
			m_select_states->set_state("Selected");

			if (m_use_pointing_hand_cursor)
			{
				setCursor(Qt::PointingHandCursor);
			}
		}
	}
	else if (event->type() == QEvent::Leave)
	{
		m_select_states->set_state("Unselected");

		unsetCursor();
	}

	QWidget::eventFilter(object, event);

	return false;
}

void VButton::init()
{
	init_layout();
	setMinimumSize(40, 40);
	installEventFilter(this);
	//add_state_pool(m_select_states);

	Vortex::add_state_pool(this, m_select_states);

	m_select_states->set_state("Unselected");

	m_button_opacity->setOpacity(1.0);
	setGraphicsEffect(m_button_opacity);

	if (m_graphic_label)
	{
		m_graphic_label->setAlignment(Qt::AlignCenter);
		m_graphic_label->setObjectName("Graphic");

		// m_graphic_label->graphic()->svg_renderer()->color()->set_value(
		// 	"#808080");
		//m_graphic_label->graphic()->svg_renderer()->color()->create_state(
		//	"Selected", "#c0c0c0");

		//Layers::lMake<LAttribute>(
		//	m_graphic_label->graphic()->svg_renderer()->color(),
		//	"Selected", "#c0c0c0");
	}

	if (m_graphic_after_label)
	{
		m_graphic_after_label->setAlignment(Qt::AlignCenter);
		m_graphic_after_label->setObjectName("Graphic After");
		m_graphic_after_label->hide();

		// m_graphic_after_label->graphic()->svg_renderer()->color()->set_value(
		// 	"#808080");
		//m_graphic_after_label->graphic()->svg_renderer()->color()->create_state(
		//	"Selected", "#c0c0c0");

		//Layers::lMake<LAttribute>(
		//	m_graphic_after_label->graphic()->svg_renderer()->color(),
		//	"Selected", "#c0c0c0");
	}

	if (m_text_label)
		m_text_label->setObjectName("Text Label");
}

void VButton::init_layout()
{
	if (m_graphic_label)
		m_main_layout->addWidget(m_graphic_label);

	if (m_graphic_after_label)
		m_main_layout->addWidget(m_graphic_after_label);

	if (m_text_label)
		m_main_layout->addWidget(m_text_label);

	setLayout(m_main_layout);
}
