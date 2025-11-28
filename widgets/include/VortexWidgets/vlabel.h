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

#ifndef VLABEL_H
#define VLABEL_H

#include <QLabel>
#include <QTimer>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include "vgraphic.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VLabel : public QLabel
{
	Q_OBJECT

public:
	VLabel(QWidget* parent = nullptr);

	VLabel(const QString& text, QWidget* parent = nullptr);

	VLabel(std::unique_ptr<VGraphic> graphic, QWidget* parent = nullptr);

	~VLabel();

	VGraphic* graphic() const;

	void reset();

	void set_bold(bool enable = true);

	void set_font_size(int size);

	void set_font_size_f(qreal size);

	void set_graphic(std::unique_ptr<VGraphic> graphic);

	void set_italic(bool enable = true);

	void set_left_padding(qreal padding);

	void setMaximumWidth(int maxw);

	virtual QSize sizeHint() const override;

	Layers::LAttribute* text_color() const;

	void update();

protected:
	bool event(QEvent* e) override;
	void paintEvent(QPaintEvent* event) override;

private:
	void init();
	//void init_attributes();

	int m_frame{ 0 };

	qreal m_left_padding{ 0.0 };

	std::unique_ptr<VGraphic> m_graphic;

	// Layers::LAttribute* m_text_color{
	// 	lMakeDefinableAttribute(this, "Text Color", "#000000") };

	QMetaObject::Connection m_repaint_connection;

	QTimer m_timer;
};
VORTEX_NAMESPACE_END

#endif // VLABEL_H
