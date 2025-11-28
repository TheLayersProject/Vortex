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

#ifndef VSCROLLAREA_H
#define VSCROLLAREA_H

#include <QScrollArea>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include "vscrollbar.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VScrollArea : public QScrollArea
{
	Q_OBJECT

public:
	VScrollArea(QWidget* parent = nullptr);

	void setWidget(QWidget* w);

private:
	VScrollBar* m_horizontal_scrollbar{ new VScrollBar };
	VScrollBar* m_vertical_scrollbar{ new VScrollBar };
};
VORTEX_NAMESPACE_END

#endif // VSCROLLAREA_H
