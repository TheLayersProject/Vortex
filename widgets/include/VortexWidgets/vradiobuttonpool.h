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

#ifndef VRADIOBUTTONPOOL_H
#define VRADIOBUTTONPOOL_H

#include <QList>
#include <QObject>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

VORTEX_NAMESPACE_BEGIN
class VRadioButton;

class VORTEX_WIDGETS_EXPORT VRadioButtonPool : public QObject
{
	Q_OBJECT

public:
	VRadioButtonPool(QList<VRadioButton*> radio_buttons);

	void set_active(VRadioButton* button);

private:
	VRadioButton* m_active_button{ nullptr };

	QList<VRadioButton*> m_radio_buttons;
};
VORTEX_NAMESPACE_END

#endif // VRADIOBUTTONPOOL_H
