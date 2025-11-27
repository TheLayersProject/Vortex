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

#ifndef VSETTINGSMENU_H
#define VSETTINGSMENU_H

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <Vortex/vortex_global.h>

#include <QWidget>
#include <QLayers/qlgraphic.h>

namespace Vortex{

	class VSettingsTab;
	class VAppearanceWidget;

	class VSettingsMenu : public QWidget
	{
		Q_OBJECT

	public:
		VSettingsMenu(QWidget* parent = nullptr);

		void add_settings_tab(std::unique_ptr<QLayers::QLGraphic> icon, const QString& label_text);

		int largest_tab_index() const;

		int recommended_minimum_tab_width() const;

		VAppearanceWidget* appearance_widget() const;

	private:
		void init_layout();

		QVBoxLayout* m_sidebar_layout = new QVBoxLayout;

		QList<VSettingsTab*> m_settings_tabs;

		QWidget* m_sidebar{ new QWidget };

		VAppearanceWidget* m_appearance_widget;
	};
}

#endif // !VSETTINGSMENU_H
