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

#include "vappearancewidget.h"

#include <Layers/lcontroller.h>
#include <Vortex/vapplication.h>

using Layers::LTheme;

using QLayers::QLButton;
//using Vortex::VThemeComboBox;
using Vortex::VAppearanceWidget;

VAppearanceWidget::VAppearanceWidget(QWidget* parent) : QLWidget(parent)
{
	init_layout();
	set_object_name("Appearance Widget");

	m_tab_bar->add_tab("Theme");
	m_tab_bar->add_tab("Styles");
	m_tab_bar->set_current_index(0);
	m_tab_bar->setMinimumHeight(40);

	for (Vortex::VTab* tab : m_tab_bar->tabs())
		tab->hide_close_button();

	connect(m_tab_bar, &VTabBar::index_changed,
		[this](int prev_index, int new_index)
		{
			if (new_index == 0 && !m_theme_widget->isVisible())
			{
				m_theme_widget->show();
				m_styles_widget->hide();
			}
			else if (new_index == 1 && !m_styles_widget->isVisible())
			{
				m_theme_widget->hide();
				m_styles_widget->show();
			}
		});

	m_tab_bar_divider->set_object_name("Dividers");
	m_tab_bar_divider->setFixedHeight(3);

	m_theme_label->set_object_name("Theme Label");
	m_theme_label->set_font_size(15);

	m_styles_widget->hide();

	//m_theme_combobox->set_object_name("Theme Combobox");

	//for (auto& _theme : lController.themes())
	//	m_theme_combobox->add_theme(_theme.second);

	//for (int i = 0; i < m_theme_combobox->count(); i++)
	//	if (m_theme_combobox->itemData(i).value<LTheme*>() == activeTheme())
	//	{
	//		m_theme_combobox->setCurrentIndex(i);
	//		break;
	//	}

	//connect(vApp, &VApplication::theme_added,
	//	[this](LTheme* theme)
	//	{
	//		m_theme_combobox->add_theme(theme, true);
	//	});

	//connect(m_theme_combobox, &VThemeComboBox::currentIndexChanged,
	//	[this] {
	//		vApp->apply_theme(
	//		m_theme_combobox->currentData().value<LTheme*>());
	//	});
}

//VThemeComboBox* VAppearanceWidget::theme_combobox() const
//{
//	return m_theme_combobox;
//}

void VAppearanceWidget::init_layout()
{
	QHBoxLayout* tab_bar_layout = new QHBoxLayout;
	tab_bar_layout->addWidget(m_tab_bar);
	tab_bar_layout->addStretch();
	tab_bar_layout->setSpacing(0);
	tab_bar_layout->setContentsMargins(8, 6, 8, 0);

	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addLayout(tab_bar_layout);
	main_layout->addWidget(m_tab_bar_divider);
	main_layout->addWidget(m_theme_widget);
	main_layout->addWidget(m_styles_widget);
	//main_layout->addStretch();
	setLayout(main_layout);
	main_layout->activate();
}
