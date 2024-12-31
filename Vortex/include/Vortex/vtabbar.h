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

#ifndef VTABBAR_H
#define VTABBAR_H

#include <QHBoxLayout>

#include <QLayers/qlwidget.h>

#include "vortex_global.h"
#include "vortex_export.h"

#include "vtab.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_EXPORT VTabBar : public QLayers::QLWidget
{
	Q_OBJECT

signals:
	void index_changed(int old_index, int new_index);

	void tab_closed(int index);

public:
	VTabBar(QWidget* parent = nullptr);

	void add_tab(const QLayers::QLGraphic& icon, const QString& text);

	void add_tab(const QString& text);

	int current_index() const;

	void set_current_index(int index);

	QList<VTab*> tabs() const;

private:
	void _add_tab(VTab* tab);

	void init_layout();

	int m_current_index{ -1 };

	QList<VTab*> m_tabs;

	QHBoxLayout* m_tab_layout{ new QHBoxLayout };
};
VORTEX_NAMESPACE_END

#endif // !VTABBAR_H
