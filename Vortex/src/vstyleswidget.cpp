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

#include "vstyleswidget.h"

#include <QVBoxLayout>

#include <Layers/lstyle.h>
#include <QLayers/qlcheckbox.h>
#include <Vortex/vapplication.h>
#include <Vortex/vstylebutton.h>

using Layers::LStyle;
using Layers::LStyleList;
using QLayers::QLCheckBox;
using Vortex::VStylesWidget;

VStylesWidget::VStylesWidget(QWidget* parent) : QLWidget(parent)
{
	init_layout();
	init_style_scroller();
	set_object_name("Styles Widget");

	m_options_bar->set_object_name("Options Bar");
	m_options_bar->setFixedHeight(50);

	m_style_scroller->set_object_name("Style Scroller");

	m_style_scroller_widget->set_object_name("Style Scroller Widget");
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
			QLCheckBox* check_box = new QLCheckBox;

			LStyleList active_styles = lController.active_styles();

			auto it = std::find(active_styles.begin(), active_styles.end(), style);
			if (it != active_styles.end())
			{
				check_box->set_state("Checked");
			}

			connect(check_box, &QLCheckBox::clicked,
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
