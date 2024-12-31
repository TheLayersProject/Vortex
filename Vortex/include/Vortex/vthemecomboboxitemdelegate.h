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

#ifndef VTHEMECOMBOBOXITEMDELEGATE_H
#define VTHEMECOMBOBOXITEMDELEGATE_H

#include "vortex_global.h"
#include "vortex_export.h"

#include <QLayers/qlcomboboxitemdelegate.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_EXPORT VThemeComboBoxItemDelegate :
	public QLayers::QLComboBoxItemDelegate
{
	Q_OBJECT

signals:
	void mouse_moved(QPoint cursor_pos);

public:
	virtual bool editorEvent(QEvent* event,
		QAbstractItemModel* model,
		const QStyleOptionViewItem& option,
		const QModelIndex& index) override;

	virtual void paint(QPainter* painter,
		const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

private:
	QImage m_caution_image{ QImage(":/images/caution.png") };
};
VORTEX_NAMESPACE_END

#endif // VTHEMECOMBOBOXITEMDELEGATE_H
