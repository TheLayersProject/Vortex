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

#ifndef VRADIOBUTTON_H
#define VRADIOBUTTON_H

#include <QWidget>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <VortexCore/vstatepool.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VRadioButton : public QWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	VRadioButton(QWidget* parent = nullptr);

	VStatePool* status_states() const;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

	void paintEvent(QPaintEvent* event) override;

private:
	// Layers::LAttribute* m_active_dot_fill{
	// 	lMakeDefinableAttribute(this, "Active.Dot.Fill", "#000000") };

	// Layers::LAttribute* m_border_fill{
	// 	lMakeDefinableAttribute(this, "Border.Fill", "#a0a0a4") };

	// Layers::LAttribute* m_border_thickness{
	// 	lMakeDefinableAttribute(this, "Border.Thickness", 3.0) };

	// Layers::LAttribute* m_fill{
	// 	lMakeDefinableAttribute(this, "Fill", "#808080") };

	// Layers::LAttribute* m_margin{
	// 	lMakeDefinableAttribute(this, "Margin", 10.0) };

	VStatePool* m_select_states{
		new VStatePool("Select", { "Selected", "Unselected" }) };

	VStatePool* m_status_states{
		new VStatePool("Status", { "Active", "Inactive" }) };
};
VORTEX_NAMESPACE_END

#endif // VRADIOBUTTON_H
