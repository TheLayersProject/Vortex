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

#include "vthemewidget.h"

#include <QGraphicsOpacityEffect>
#include <VortexCore/vboxstyle.h>
#include <VortexCore/vapplication.h>
#include <VortexWidgets/vthemebutton.h>
#include <VortexWidgets/vthemedirectoriesdialog.h>

using Layers::LTheme;
using Vortex::VButton;
using Vortex::VThemeWidget;
using Vortex::VThemeDirectoriesDialog;

VThemeWidget::VThemeWidget(QWidget* parent) : QWidget(parent)
{
	init_layout();
	init_theme_scroller();
	setObjectName("Theme Widget");
	update_active_theme_displayer();

	m_options_bar->setObjectName("Options Bar");
	m_options_bar->setFixedHeight(50);

	m_active_theme_displayer->setObjectName("Active Theme Displayer");
	m_active_theme_displayer->setFixedSize(300, 40);

	m_theme_directories_button->setObjectName("Theme Directories Button");
	m_theme_directories_button->setFixedSize(40, 40);
	m_theme_directories_button->set_pointing_hand_cursor();
	m_theme_directories_button->layout()->setContentsMargins(0, 0, 0, 0);

	connect(m_theme_directories_button, &VButton::clicked,
		[this]
		{
			VThemeDirectoriesDialog theme_directories_dialog = VThemeDirectoriesDialog();

			Vortex::center(&theme_directories_dialog, window());

			if (theme_directories_dialog.exec())
			{
				// ?
			}
		});

	m_theme_scroller->setObjectName("Theme Scroller");
	//m_theme_scroller->viewport()->setAutoFillBackground(false);
	//m_theme_scroller->widget()->setAutoFillBackground(false);

	m_theme_label->setObjectName("Theme Label");
	m_theme_label->set_bold();

	QGraphicsOpacityEffect* publisher_opacity = new QGraphicsOpacityEffect;
	publisher_opacity->setOpacity(0.6);

	m_publisher_label->setGraphicsEffect(publisher_opacity);
	m_publisher_label->setObjectName("Publisher Label");
	m_publisher_label->set_font_size_f(10.5);

	lController.on_theme_added(
		[this](LTheme* theme)
		{
			add_theme_button(theme);
		});
}

void VThemeWidget::init_layout()
{
	QVBoxLayout* active_theme_displayer_layout = new QVBoxLayout;
	active_theme_displayer_layout->setContentsMargins(5, 2, 5, 2);
	active_theme_displayer_layout->setSpacing(0);
	active_theme_displayer_layout->addWidget(m_theme_label);
	active_theme_displayer_layout->addWidget(m_publisher_label);
	m_active_theme_displayer->setLayout(active_theme_displayer_layout);

	QHBoxLayout* options_bar_layout = new QHBoxLayout;
	options_bar_layout->setContentsMargins(8, 0, 8, 0);
	options_bar_layout->setSpacing(10);
	options_bar_layout->addWidget(m_active_theme_displayer);
	options_bar_layout->addWidget(m_theme_directories_button);
	options_bar_layout->addStretch();
	m_options_bar->setLayout(options_bar_layout);

	theme_buttons_vbox->addStretch();

	m_theme_scroller_widget->setLayout(theme_buttons_vbox);
	m_theme_scroller->setWidget(m_theme_scroller_widget);

	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->setSpacing(0);
	main_layout->addWidget(m_options_bar);
	main_layout->addWidget(m_theme_scroller);
	//main_layout->addStretch();
	setLayout(main_layout);
}

void VThemeWidget::init_theme_scroller()
{
	for (auto& [theme_id, theme] : lController.themes())
	{
		add_theme_button(theme.get());
	}
}

void VThemeWidget::add_theme_button(LTheme* theme)
{
	VThemeButton* theme_button = new VThemeButton(theme);
	theme_buttons_vbox->insertWidget(theme_buttons_vbox->count() - 1, theme_button);

	theme_button->setStyle(qApp->style());

	qDebug() << "Theme Button Style Type:" << theme_button->style()->metaObject()->className();

	connect(theme_button, &VThemeButton::clicked,
		[this, theme]
		{
			vApp->apply_theme(theme);

			Vortex::update_all_styled_widgets();
			update_active_theme_displayer();
		});
}

void VThemeWidget::update_active_theme_displayer()
{
	LTheme* theme = lController.active_theme();

	m_theme_label->setText(theme->object_name().c_str());

	m_publisher_label->setText(theme->publisher().c_str());
}
