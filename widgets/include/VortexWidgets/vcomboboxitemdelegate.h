// /*
//  * Copyright (C) 2025 Huntr Software LLC
//  *
//  * This file is part of Vortex.
//  *
//  * Vortex is free software: you can redistribute it and/or modify
//  * it under the terms of the GNU Lesser General Public License as published by
//  * the Free Software Foundation, either version 3 of the License, or
//  * (at your option) any later version.
//  *
//  * Vortex is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
//  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  * GNU Lesser General Public License for more details.
//  *
//  * You should have received a copy of the GNU Lesser General Public License
//  * along with Vortex. If not, see <https://www.gnu.org/licenses/>.
//  */

// #ifndef VCOMBOBOXITEMDELEGATE_H
// #define VCOMBOBOXITEMDELEGATE_H

// #include <QPainterPath>
// #include <QStyledItemDelegate>

// #include <Layers/lattribute.h>

// #include "vortex_global.h"
// #include "vortex_export.h"

// #include "vstylable.h"
// #include "vstatepool.h"

// VORTEX_NAMESPACE_BEGIN
// class VORTEX_WIDGETS_EXPORT VComboBoxItemDelegate :
// 	public QStyledItemDelegate
// {
// 	Q_OBJECT

// public:
// 	VComboBoxItemDelegate(QObject* parent = nullptr);

// 	QPainterPath background_path(
// 		const QStyleOptionViewItem& option,
// 		const QModelIndex& index) const;

// 	Layers::LAttribute* corner_radius() const;

// 	Layers::LAttribute* fill() const;

// 	virtual void paint(QPainter* painter,
// 		const QStyleOptionViewItem& option,
// 		const QModelIndex& index) const override;

// 	void set_is_above_control(bool condition = true);

// 	Layers::LAttribute* text_color() const;

// private:
// 	bool m_is_above_control{ false };

// 	VStatePool* m_select_states{
// 		new VStatePool("Status", { "Selected", "Unselected" }) };
// };
// VORTEX_NAMESPACE_END

// #endif // VCOMBOBOXITEMDELEGATE_H  
