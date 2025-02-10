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

#ifndef VSTYLESWIDGET_H
#define VSTYLESWIDGET_H

#include <QVBoxLayout>
#include <QLayers/qlscrollarea.h>
#include <QLayers/qlwidget.h>

#include <Vortex/vortex_global.h>

namespace Vortex {

	class VStylesWidget : public QLayers::QLWidget
	{
		Q_OBJECT

	public:
		VStylesWidget(QWidget* parent = nullptr);

	private:
		void init_layout();
		void init_style_scroller();

		QLWidget* m_options_bar{ new QLWidget };

		QLayers::QLScrollArea* m_style_scroller{ new QLayers::QLScrollArea };
		QLWidget* m_style_scroller_widget{ new QLWidget };
		QVBoxLayout* style_buttons_vbox{ new QVBoxLayout };
	};
}

#endif // !VSTYLESWIDGET_H
