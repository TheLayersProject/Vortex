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

#ifndef VSTYLEBUTTON_H
#define VSTYLEBUTTON_H

#include "vortex_global.h"
#include "vortex_export.h"

#include <QLayers/qllabel.h>
#include <QLayers/qlwidget.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_EXPORT VStyleButton : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	VStyleButton(Layers::LStyle* style, QWidget* parent = nullptr);

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_layout();
	//void init_style(Layers::LTheme* theme);

	QLayers::QLLabel* m_name_label;
	QLayers::QLLabel* m_publisher_label;
};
VORTEX_NAMESPACE_END

#endif // VSTYLEBUTTON_H
