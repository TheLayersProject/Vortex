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

#ifndef VTHEMEWIDGET_H
#define VTHEMEWIDGET_H

#include <VortexWidgets/vortex_widgets_global.h>

#include <QVBoxLayout>
#include <Layers/ltheme.h>
#include <VortexWidgets/vbutton.h>
#include <VortexWidgets/vscrollarea.h>

namespace Vortex {
	class VThemeWidget : public QWidget
	{
		Q_OBJECT

	public:
		VThemeWidget(QWidget* parent = nullptr);

	private:
		void add_theme_button(Layers::LTheme* theme);
		void init_layout();
		void init_theme_scroller();

		void update_active_theme_displayer();

		QWidget* m_options_bar{ new QWidget };

		QWidget* m_active_theme_displayer{ new QWidget };

		VLabel* m_theme_label{ new VLabel("Theme") };
		VLabel* m_publisher_label{ new VLabel("Publisher") };

		VScrollArea* m_theme_scroller{ new VScrollArea };
		QWidget* m_theme_scroller_widget{ new QWidget };
		QVBoxLayout* theme_buttons_vbox{ new QVBoxLayout };

		VButton* m_theme_directories_button{ new VButton(
			std::make_unique<VGraphic>(":/images/theme_directories_icon.svg", QSize(25, 22))
		) };
	};
}

#endif // !VTHEMEWIDGET_H
