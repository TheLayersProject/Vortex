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

#include "vstyleswidget.h"

#include <QVBoxLayout>

#include <Layers/lstyle.h>
#include <VortexWidgets/vcheckbox.h>
#include <VortexCore/vapplication.h>
#include <VortexWidgets/vstylebutton.h>

using Layers::LStyle;
using Layers::LStyleList;
using Vortex::VCheckBox;
using Vortex::VStylesWidget;

VStylesWidget::VStylesWidget(QWidget* parent) : QWidget(parent)
{
	init_layout();
	init_style_scroller();
	setObjectName("Styles Widget");

	m_options_bar->setObjectName("Options Bar");
	m_options_bar->setFixedHeight(50);

	m_style_scroller->setObjectName("Style Scroller");

	m_style_scroller_widget->setObjectName("Style Scroller Widget");
}

void VStylesWidget::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addWidget(m_options_bar);
	main_layout->addWidget(m_style_scroller);
	setLayout(main_layout);
}

void Vortex::VStylesWidget::init_style_scroller()
{
	for (auto& _style : lController.styles())
	{
		LStyle* style = _style.second;

		if (!style->publisher().empty())
		{
			VCheckBox* check_box = new VCheckBox;

			LStyleList active_styles = lController.active_custom_styles();

			auto it = std::find(active_styles.begin(), active_styles.end(), style);
			if (it != active_styles.end())
			{
				check_box->set_state("Checked");
			}

			connect(check_box, &VCheckBox::clicked,
				[this, style]
				{
					vApp->toggle_style(style->object_name());
				});

			VStyleButton* style_button = new VStyleButton(style);

			connect(style_button, &VStyleButton::clicked,
				[this, style, check_box]
				{
					if (vApp->toggle_style(style->object_name()))
					{
						check_box->set_state("Checked");
					}
					else
					{
						check_box->set_state("Unchecked");
					}
				});

			QHBoxLayout* style_option_hbox = new QHBoxLayout;
			style_option_hbox->setContentsMargins(0, 0, 0, 0);
			style_option_hbox->addWidget(check_box);
			style_option_hbox->addWidget(style_button);

			style_buttons_vbox->addLayout(style_option_hbox);
		}
	}

	style_buttons_vbox->addStretch();

	m_style_scroller_widget->setLayout(style_buttons_vbox);
	m_style_scroller->setWidget(m_style_scroller_widget);
}
