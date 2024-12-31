/*
 * Copyright (C) 2023 The Layers Project
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

#include "vsettingstab.h"

#include <QIntValidator>
#include <QMouseEvent>
#include <QLayers/qllabel.h>

using QLayers::QLGraphic;
using QLayers::QLStatePool;
using Vortex::VSettingsTab;

VSettingsTab::VSettingsTab(
	const QLGraphic& icon, const QString& label_text, QWidget* parent) :
	m_icon_label{ new QLayers::QLLabel(icon) },
	m_text_label { new QLayers::QLLabel(label_text) },
	QLWidget(parent)
{
	init_attributes();
	init_layout();
	add_state_pool(m_select_states);

	m_select_states->set_state("Unselected");

	connect(this, &VSettingsTab::clicked, [this]
		{
			m_select_states->set_state("Selected");
		});

	installEventFilter(this);
	setMouseTracking(true);
	setFixedHeight(60);

	set_object_name("Setting Tab");

	m_icon_label->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_icon_label->set_object_name("Icon Label");

	m_text_label->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_text_label->set_object_name("Text Label");
	m_text_label->set_font_size(14);
}

void VSettingsTab::init_attributes()
{
	m_corner_radii_top_left->set_value(5.0);
	m_corner_radii_bottom_left->set_value(5.0);
	m_fill->set_value("#c0c0c0");
	m_fill->create_state("Selected", "#ffffff");

	m_icon_label->graphic()->svg_renderer()->color()->set_value("#a0a0a4");
	m_icon_label->graphic()->svg_renderer()->color()->create_state(
		"Selected", "#000000");

	m_text_label->text_color()->set_value("#a0a0a4");
	m_text_label->text_color()->create_state("Selected", "#000000");
}

int VSettingsTab::recommended_minimum_width()
{
	return 18 + m_icon_label->sizeHint().width() + 12 + m_text_label->sizeHint().width() + 18;
}

QLStatePool* VSettingsTab::select_states() const
{
	return m_select_states;
}

void VSettingsTab::set_disabled(bool cond)
{
	m_disabled = cond;
}

bool VSettingsTab::eventFilter(QObject* object, QEvent* event)
{
	if (!m_disabled)
	{
		if (event->type() == QEvent::MouseButtonPress)
		{
			QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

			if (mouse_event->button() & Qt::LeftButton)
			{
				emit clicked();
			}
		}
	}

	return false;
}

//void VSettingsTab::resizeEvent(QResizeEvent* event)
//{
//    int minimum_width = 18 + m_icon_label->width() + 12 + m_text_label->width() + 18;
//
//    if (width() < minimum_width)
//        emit under_minimum_width();
//    else
//        emit over_minimum_width();
//}

void VSettingsTab::init_layout()
{
	main_layout->setContentsMargins(18, 0, 18, 0);
	main_layout->setSpacing(12);
	main_layout->addWidget(m_icon_label);
	main_layout->addWidget(m_text_label);

	setLayout(main_layout);
}
