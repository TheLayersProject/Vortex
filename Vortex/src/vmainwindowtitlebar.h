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

#ifndef VMAINWINDOWTITLEBAR_H
#define VMAINWINDOWTITLEBAR_H

#include <QLayers/qlayers_global.h>

#include <Vortex/vtabbar.h>

namespace Vortex{
	class VMainWindowTitlebar : public QLayers::QLWidget
	{
		Q_OBJECT

	public:
		VMainWindowTitlebar(QWidget* parent = nullptr);

		VTabBar* menu_tab_bar() const;

		QLayers::QLButton* settings_button() const;
		QLayers::QLButton* minimize_button() const;
		QLayers::QLButton* maximize_button() const;
		QLayers::QLButton* exit_button() const;

	protected:
		void init_layout();

	private:
		QHBoxLayout* main_layout = new QHBoxLayout;

		QLayers::QLButton* m_settings_button{
			new QLayers::QLButton(
				QLayers::QLGraphic(":/images/settings.svg", QSize(20, 20))) };

		QLayers::QLButton* m_minimize_button{
			new QLayers::QLButton(
				QLayers::QLGraphic(":/images/minimize.svg", QSize(20, 20))) };

		QLayers::QLButton* m_maximize_button{
			new QLayers::QLButton(
				QLayers::QLGraphic(":/images/maximize.svg", QSize(20, 20))) };

		QLayers::QLButton* m_exit_button{
			new QLayers::QLButton(
				QLayers::QLGraphic(":/images/exit.svg", QSize(20, 20))) };

		VTabBar* m_menu_tab_bar{ new VTabBar };
	};
}

#endif // !VMAINWINDOWTITLEBAR_H
