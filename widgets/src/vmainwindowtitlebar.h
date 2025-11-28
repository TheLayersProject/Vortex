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

#ifndef VMAINWINDOWTITLEBAR_H
#define VMAINWINDOWTITLEBAR_H

#include <VortexWidgets/vtabbar.h>

namespace Vortex{
	class VMainWindowTitlebar : public QWidget
	{
		Q_OBJECT

	public:
		VMainWindowTitlebar(QWidget* parent = nullptr);

		VTabBar* menu_tab_bar() const;

		VButton* settings_button() const;
		VButton* minimize_button() const;
		VButton* maximize_button() const;
		VButton* exit_button() const;

	protected:
		void init_layout();

	private:
		QHBoxLayout* main_layout = new QHBoxLayout;

		VButton* m_settings_button{
			new VButton(
				std::make_unique<VGraphic>(":/images/settings.svg", QSize(20, 20))) };

		VButton* m_minimize_button{
			new VButton(
				std::make_unique<VGraphic>(":/images/minimize.svg", QSize(20, 20))) };

		VButton* m_maximize_button{
			new VButton(
				std::make_unique<VGraphic>(":/images/maximize.svg", QSize(20, 20))) };

		VButton* m_exit_button{
			new VButton(
				std::make_unique<VGraphic>(":/images/exit.svg", QSize(20, 20))) };

		VTabBar* m_menu_tab_bar{ new VTabBar };
	};
}

#endif // !VMAINWINDOWTITLEBAR_H
