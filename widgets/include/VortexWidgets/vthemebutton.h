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

#ifndef VTHEMEBUTTON_H
#define VTHEMEBUTTON_H

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <Layers/ltheme.h>

#include <VortexWidgets/vlabel.h>
//#include <QLayers/qlwidget.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VThemeButton : public QWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	VThemeButton(Layers::LTheme* theme, QWidget* parent = nullptr);

protected:
	bool eventFilter(QObject* object, QEvent* event) override;
	//void paintEvent(QPaintEvent* event) override;

private:
	void init_layout();
	void init_style(Layers::LTheme* theme);

	VLabel* m_name_label;
	VLabel* m_publisher_label;
};
VORTEX_NAMESPACE_END

#endif // VTHEMEBUTTON_H
