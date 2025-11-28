/*
 * Copyright (C) 2023 The Layers Project
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

#ifndef VTAB_H
#define VTAB_H

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <VortexCore/vstatepool.h>
#include <VortexWidgets/vbutton.h>
#include <VortexWidgets/vlabel.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VTab : public QWidget
{
	Q_OBJECT

signals:
	void clicked();

	void closed();

public:
	VTab(std::unique_ptr<VGraphic> icon,
		const QString& text, QWidget* parent = nullptr);

	VTab(const QString& text, QWidget* parent = nullptr);

	VButton* close_button() const;

	void hide_close_button();

	VLabel* icon_label() const;

	void set_icon(std::unique_ptr<VGraphic> icon);

	void set_text(const QString& text);

	VStatePool* status_states() const;

	VLabel* text_label() const;

protected:
	bool event(QEvent* e) override;

private:
	void init();
	//void init_attributes();
	void init_layout();

	QHBoxLayout* main_layout = new QHBoxLayout;

	VButton* m_close_button
		{ new VButton(
			std::make_unique<VGraphic>(":/images/tab_exit.svg", QSize(16, 17))) };

	VLabel* m_icon_label{ nullptr };

	VLabel* m_text_label{ nullptr };

	VStatePool* m_status_states
		{ new VStatePool("Status", { "Active", "Inactive" })};
};
VORTEX_NAMESPACE_END

#endif // !VTAB_H
