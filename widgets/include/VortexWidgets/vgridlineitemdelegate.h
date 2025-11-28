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

#ifndef VGRIDLINEITEMDELEGATE_H
#define VGRIDLINEITEMDELEGATE_H

#include <QStyledItemDelegate>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VGridlineItemDelegate : public QStyledItemDelegate
{
	Q_OBJECT

signals:
	void changed();

public:
	VGridlineItemDelegate(QObject* parent = nullptr);

	Layers::LAttribute* grid_fill() const;

	Layers::LAttribute* grid_thickness() const;

	virtual void paint(QPainter* painter,
		const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;

	using QStyledItemDelegate::sizeHint;
	using QStyledItemDelegate::createEditor;
	using QStyledItemDelegate::setEditorData;
	using QStyledItemDelegate::setModelData;
	using QStyledItemDelegate::updateEditorGeometry;

private:
	// Layers::LAttribute* m_grid_fill{
	// 	lMakeDefinableAttribute(this, "Grid.Fill", "#808080") };

	// Layers::LAttribute* m_grid_thickness{
	// 	lMakeDefinableAttribute(this, "Grid.Thickness", 3.0) };
};
VORTEX_NAMESPACE_END

#endif // VGRIDLINEITEMDELEGATE_H  
