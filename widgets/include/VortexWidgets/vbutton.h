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

#ifndef VBUTTON_H
#define VBUTTON_H

#include <QGraphicsOpacityEffect>
#include <QHBoxLayout>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <VortexCore/vstatepool.h>
#include "vlabel.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VButton : public QWidget
{
	Q_OBJECT

signals:
	void clicked();

public:
	VButton(std::unique_ptr<VGraphic> graphic, const QString& text,
		QWidget* parent = nullptr);

	VButton(std::unique_ptr<VGraphic> graphic, QWidget* parent = nullptr);

	VButton(const QString& text, QWidget* parent = nullptr);

	VButton(
		std::unique_ptr<VGraphic> graphic,
		std::unique_ptr<VGraphic> graphic_after,
		QWidget* parent = nullptr);

	bool disabled() const;

	VLabel* graphic_label() const;

	QHBoxLayout* layout() const;

	void set_disabled(bool cond = true);

	void set_font_size(int size);
	
	void set_font_size_f(qreal size);

	void set_padding(int padding);

	void set_padding(int left, int top, int right, int bottom);

	void set_pointing_hand_cursor(bool use_cursor = true);

	VLabel* text_label() const;

	void toggle_graphics();

protected:
	virtual bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init();
	void init_layout();

	QHBoxLayout* m_main_layout{ new QHBoxLayout };

	QGraphicsOpacityEffect* m_button_opacity{ new QGraphicsOpacityEffect };

	bool m_disabled{ false };
	bool m_use_pointing_hand_cursor{ false };

	VLabel* m_graphic_label{ nullptr };
	VLabel* m_graphic_after_label{ nullptr };

	VLabel* m_text_label{ nullptr };

	VStatePool* m_select_states{
		new VStatePool("Select", { "Selected", "Unselected" }) };
};
VORTEX_NAMESPACE_END

#endif // VBUTTON_H
