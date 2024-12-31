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

#include "vortex_global.h"
#include "vortex_export.h"

#include <QLayers/qlbutton.h>
#include <QLayers/qllabel.h>
#include <QLayers/qlstatepool.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_EXPORT VTab : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void clicked();

	void closed();

public:
	VTab(const QLayers::QLGraphic& icon,
		const QString& text, QWidget* parent = nullptr);

	VTab(const QString& text, QWidget* parent = nullptr);

	QLayers::QLButton* close_button() const;

	void hide_close_button();

	QLayers::QLLabel* icon_label() const;

	QLayers::QLStatePool* status_states() const;

	QLayers::QLLabel* text_label() const;

protected:
	bool eventFilter(QObject* object, QEvent* event) override;

private:
	void init();
	void init_attributes();
	void init_layout();

	QHBoxLayout* main_layout = new QHBoxLayout;

	QLayers::QLButton* m_close_button
		{ new QLayers::QLButton(
			QLayers::QLGraphic(":/images/tab_exit.svg", QSize(16, 17))) };

	QLayers::QLLabel* m_icon_label{ nullptr };

	QLayers::QLLabel* m_text_label{ nullptr };

	QLayers::QLStatePool* m_status_states
		{ new QLayers::QLStatePool("Status", { "Active", "Inactive" })};
};
VORTEX_NAMESPACE_END

#endif // !VTAB_H
