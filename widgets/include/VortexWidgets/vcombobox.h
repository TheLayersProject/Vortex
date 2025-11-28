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

// #ifndef VCOMBOBOX_H
// #define VCOMBOBOX_H

// #include <QComboBox>
// #include <QPainterPath>

// #include <Layers/lattribute.h>

// #include "vortex_global.h"
// #include "vortex_export.h"

// #include "vpaint.h"
// //#include "vstylable.h"

// VORTEX_NAMESPACE_BEGIN
// class VORTEX_WIDGETS_EXPORT VComboBox : public QComboBox
// {
// 	Q_OBJECT

// public:
// 	VComboBox(QWidget* parent = nullptr);

// 	Layers::LAttribute* border_fill() const;

// 	Layers::LAttribute* border_thickness() const;

// 	Layers::LAttribute* corner_radius() const;

// 	Layers::LAttribute* fill() const;

// 	void setFixedHeight(int h);

// 	void setFixedSize(const QSize& s);

// 	void setFixedSize(int w, int h);

// 	void setFixedWidth(int w);

// 	virtual void showPopup() override;

// 	Layers::LAttribute* text_color() const;

// 	void update();

// protected:
// 	virtual bool eventFilter(QObject* object, QEvent* event) override;

// 	bool is_view_positioned_above() const;

// 	void paint_box(QPainter* painter);

// 	virtual void paintEvent(QPaintEvent* event) override;

// 	// Layers::LAttribute* m_border_fill{
// 	// 	lMakeDefinableAttribute(this, "Border.Fill", "#a0a0a4") };

// 	// Layers::LAttribute* m_border_thickness{
// 	// 	lMakeDefinableAttribute(this, "Border.Thickness", 0.0) };

// 	// Layers::LAttribute* m_corner_radius{
// 	// 	lMakeDefinableAttribute(this, "Corner Radius", 4.0) };

// 	// Layers::LAttribute* m_fill{
// 	// 	lMakeDefinableAttribute(this, "Fill", "#31323b") };

// 	// Layers::LAttribute* m_text_color{
// 	// 	lMakeDefinableAttribute(this, "Text Color", "#e1e1e1") };
// };
// VORTEX_NAMESPACE_END

// #endif // VCOMBOBOX_H
