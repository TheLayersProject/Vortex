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

#ifndef VSLIDER_H
#define VSLIDER_H

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <QWidget>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VSlider : public QWidget
{
	Q_OBJECT

public:
	VSlider(QWidget* parent = nullptr);

	VSlider(int limit, QWidget* parent = nullptr);

	void set_limit(int limit);

	Layers::LAttribute* value();

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init();
	//void init_attributes();
	void init_layout();

	void update_handle_pos();

	Layers::LAttribute* m_value{ new Layers::LAttribute("value", 0.0) };

	QWidget* m_bar{ new QWidget };
	QWidget* m_handle{ new QWidget(this) };

	int m_limit{ 99 };
	double m_value_on_click{ 0.0 };

	bool m_dragging_handle{ false };

	bool m_is_decimal_slider;

	QPoint m_mouse_click_position{ QPoint() };
};
VORTEX_NAMESPACE_END

#endif // VSLIDER_H
