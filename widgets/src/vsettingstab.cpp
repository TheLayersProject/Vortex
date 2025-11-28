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

#include "vsettingstab.h"

#include <QIntValidator>
#include <QMouseEvent>
#include <VortexCore/vboxstyle.h>
#include <VortexWidgets/vlabel.h>

using Vortex::VGraphic;
using Vortex::VStatePool;
using Vortex::VSettingsTab;

VSettingsTab::VSettingsTab(
	std::unique_ptr<VGraphic> icon, const QString& label_text, QWidget* parent) :
	m_icon_label{ new VLabel(std::move(icon)) },
	m_text_label { new VLabel(label_text) },
	QWidget(parent)
{
	//init_attributes();
	init_layout();
	Vortex::add_state_pool(this, m_select_states);

	m_select_states->set_state("Unselected");

	connect(this, &VSettingsTab::clicked, [this]
		{
			m_select_states->set_state("Selected");
		});

	installEventFilter(this);
	setMouseTracking(true);
	setFixedHeight(60);

	setObjectName("Setting Tab");

	m_icon_label->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_icon_label->setObjectName("Icon Label");

	m_text_label->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_text_label->setObjectName("Text Label");
	m_text_label->set_font_size(14);
}

// void VSettingsTab::init_attributes()
// {
// 	m_corner_radii_top_left->set_value(5.0);
// 	m_corner_radii_bottom_left->set_value(5.0);
// 	m_fill->set_value("#c0c0c0");
// 	//Layers::lMake<LAttribute>(m_fill, "Selected", "#ffffff");
// 	//m_fill->create_state("Selected", "#ffffff");

// 	m_icon_label->graphic()->svg_renderer()->color()->set_value("#a0a0a4");
// 	//Layers::lMake<LAttribute>(
// 	//	m_icon_label->graphic()->svg_renderer()->color(),
// 	//	"Selected", "#000000");
// 	//m_icon_label->graphic()->svg_renderer()->color()->create_state(
// 	//	"Selected", "#000000");

// 	m_text_label->text_color()->set_value("#a0a0a4");
// 	//Layers::lMake<LAttribute>(m_text_label->text_color(), "Selected", "#000000");
// 	//m_text_label->text_color()->create_state("Selected", "#000000");
// }

int VSettingsTab::recommended_minimum_width()
{
	return 18 + m_icon_label->sizeHint().width() + 12 + m_text_label->sizeHint().width() + 18;
}

VStatePool* VSettingsTab::select_states() const
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
