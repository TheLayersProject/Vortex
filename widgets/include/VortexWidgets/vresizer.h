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

#ifndef VRESIZER_H
#define VRESIZER_H

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <VortexCore/vstatepool.h>
#include "vsvgrenderer.h"

#include <QWidget>

VORTEX_NAMESPACE_BEGIN
enum class VORTEX_WIDGETS_EXPORT QLSizeDimension { Width, Height };

class VORTEX_WIDGETS_EXPORT VResizer : public QWidget
{
	Q_OBJECT

public:
	VResizer(QLSizeDimension resize_dimension, QWidget* parent = nullptr);

	void set_widget(QWidget* widget, int lower_limit, int upper_limit);

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

	virtual void paintEvent(QPaintEvent* event) override;

private:
	QLSizeDimension m_resize_dimension;

	VSvgRenderer* m_icon_svg{ nullptr };

	QSize m_icon_size;

	VStatePool* m_select_states
		{ new VStatePool("Select", { "Selected", "Unselected" }) };

	QPoint m_click_pos;
	QSize m_click_size;

	QWidget* m_widget{ nullptr };

	int m_lower_limit{ 0 };
	int m_upper_limit{ 1000 };
};
VORTEX_NAMESPACE_END

#endif // VRESIZER_H
