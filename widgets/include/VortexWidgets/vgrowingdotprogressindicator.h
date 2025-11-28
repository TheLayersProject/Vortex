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

#ifndef VGROWINGDOTPROGRESSINDICATOR_H
#define VGROWINGDOTPROGRESSINDICATOR_H

#include <QTimer>
#include <QWidget>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VGrowingDotProgressIndicator : public QWidget
{
	Q_OBJECT

signals:
	void timeout();

public:
	VGrowingDotProgressIndicator(QWidget* parent = nullptr);

	~VGrowingDotProgressIndicator();

	void start(int msec);

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QTimer* m_progress_timer{ new QTimer };
	QTimer* m_update_timer{ new QTimer };

	QMetaObject::Connection m_progress_timer_timeout_connection;
	QMetaObject::Connection m_update_timer_timeout_connection;

	// Layers::LAttribute* m_color{
	// 	lMakeDefinableAttribute(this, "Color", "#c0c0c0") };
};
VORTEX_NAMESPACE_END

#endif // VGROWINGDOTPROGRESSINDICATOR_H
