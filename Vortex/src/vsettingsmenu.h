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

#ifndef VSETTINGSMENU_H
#define VSETTINGSMENU_H

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <Vortex/vortex_global.h>

#include <QLayers/qlgraphic.h>
#include <QLayers/qlwidget.h>

namespace Vortex{

	class VSettingsTab;
	class VThemesWidget;

	class VSettingsMenu : public QLayers::QLWidget
	{
		Q_OBJECT

	public:
		VSettingsMenu(QWidget* parent = nullptr);

		void add_settings_tab(const QLayers::QLGraphic& icon, const QString& label_text);

		int largest_tab_index() const;

		int recommended_minimum_tab_width() const;

		VThemesWidget* themes_widget() const;

	private:
		void init_layout();

		QVBoxLayout* m_sidebar_layout = new QVBoxLayout;

		QList<VSettingsTab*> m_settings_tabs;

		QLWidget* m_sidebar{ new QLWidget };

		VThemesWidget* m_themes_widget;
	};
}

#endif // !VSETTINGSMENU_H
