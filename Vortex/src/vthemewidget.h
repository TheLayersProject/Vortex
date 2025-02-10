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

#ifndef VTHEMEWIDGET_H
#define VTHEMEWIDGET_H

#include <Vortex/vortex_global.h>

#include <QVBoxLayout>
#include <QLayers/qllabel.h>
#include <QLayers/qlscrollarea.h>
#include <QLayers/qlwidget.h>

namespace Vortex {
	class VThemeWidget : public QLayers::QLWidget
	{
		Q_OBJECT

	public:
		VThemeWidget(QWidget* parent = nullptr);

	private:
		void init_layout();
		void init_theme_scroller();

		void update_active_theme_displayer();

		QLWidget* m_options_bar{ new QLWidget };

		QLWidget* m_active_theme_displayer{ new QLWidget };

		QLayers::QLLabel* m_theme_label{ new QLayers::QLLabel("Theme") };
		QLayers::QLLabel* m_publisher_label{ new QLayers::QLLabel("Publisher") };

		QLayers::QLScrollArea* m_theme_scroller{ new QLayers::QLScrollArea };
		QWidget* m_theme_scroller_widget{ new QWidget };
		QVBoxLayout* theme_buttons_vbox{ new QVBoxLayout };
	};
}

#endif // !VTHEMEWIDGET_H
