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

#ifndef VSETTINGSTAB_H
#define VSETTINGSTAB_H

#include <QHBoxLayout>

#include <Vortex/vortex_global.h>

#include <QLayers/qllabel.h>
#include <QLayers/qlwidget.h>

namespace Vortex{
	class VThemesWidget;

	class VSettingsTab : public QLayers::QLWidget
	{
		Q_OBJECT

	signals:
		void clicked();

	public:
		VSettingsTab(
			const QLayers::QLGraphic& icon,
			const QString& label_text, QWidget* parent = nullptr);

		int recommended_minimum_width();

		QLayers::QLStatePool* select_states() const;

		void set_disabled(bool cond = true);

	protected:
		bool eventFilter(QObject* object, QEvent* event) override;

		void init_attributes();

		//void resizeEvent(QResizeEvent* event);

	private:
		void init_layout();

		QHBoxLayout* main_layout{ new QHBoxLayout };

		bool m_disabled{ false };

		QLayers::QLLabel* m_icon_label;

		QLayers::QLLabel* m_text_label;

		QLayers::QLStatePool* m_select_states {
			new QLayers::QLStatePool("Select", { "Selected", "Unselected" }) };
	};
}

#endif // !VSETTINGSTAB_H
