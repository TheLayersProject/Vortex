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

#ifndef VCHECKBOX_H
#define VCHECKBOX_H

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <VortexCore/vstatepool.h>
#include "vlabel.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VCheckBox : public QWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	VCheckBox(QWidget* parent = nullptr);

	bool is_checked() const;

	void set_state(const QString& state);

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init_layout();

	VStatePool* m_check_states{
		new VStatePool("Check", { "Checked", "Unchecked" }) };

	VLabel* m_check_label{
		new VLabel(std::make_unique<VGraphic>(":/images/check.svg", QSize(18, 14))) };
};
VORTEX_NAMESPACE_END

#endif // VCHECKBOX_H
