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

#ifndef VAPPEARANCEWIDGET_H
#define VAPPEARANCEWIDGET_H

#include <Vortex/vortex_global.h>


//#include <QLayers/qlbutton.h>
#include <Vortex/vtabbar.h>
//#include <Vortex/vthemecombobox.h>

#include "vthemewidget.h"
#include "vstyleswidget.h"


namespace Vortex{

	class VAppearanceWidget : public QLayers::QLWidget
	{
		Q_OBJECT

	public:
		VAppearanceWidget(QWidget* parent = nullptr);

	private:
		void init_layout();

		VTabBar* m_tab_bar{ new VTabBar };

		QLWidget* m_tab_bar_divider{ new QLWidget };

		QLayers::QLLabel* m_theme_label{ new QLayers::QLLabel("Theme") };

		VThemeWidget* m_theme_widget{ new VThemeWidget };

		VStylesWidget* m_styles_widget{ new VStylesWidget };
	};
}

#endif // !VAPPEARANCEWIDGET_H
