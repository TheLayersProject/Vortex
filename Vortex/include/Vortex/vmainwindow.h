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

#ifndef VMAINWINDOW_H
#define VMAINWINDOW_H

#include <QVBoxLayout>

#include <QLayers/qlwidget.h>

#include "vortex_global.h"
#include "vortex_export.h"

VORTEX_NAMESPACE_BEGIN
class VMainWindowTitlebar;

class VORTEX_EXPORT VMainWindow : public QLayers::QLWidget
{
	Q_OBJECT

public:
	VMainWindow(QWidget* parent = nullptr);

	void open_central_widget(QWidget* central_widget, const QString& tab_text);

	void open_central_widget(
		QWidget* central_widget, const QLayers::QLGraphic& tab_icon_graphic,
		const QString& tab_text);

	virtual void update() override;

protected:
#ifdef _WIN32
	virtual bool nativeEvent(
		const QByteArray& eventType, void* message, qintptr* result) override;
#endif

private slots:
	void new_theme_clicked();

private:
	void init_attributes();
	void init_layout();
	void init_titlebar_connections();

	void _open_central_widget(QWidget* central_widget);

	void set_active_central_widget(QWidget* central_widget);

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

	VMainWindowTitlebar* m_titlebar;

	QLWidget* m_separator{ new QLWidget };

	QList<QWidget*> m_central_widgets;
};
VORTEX_NAMESPACE_END

#endif // !VMAINWINDOW_H
