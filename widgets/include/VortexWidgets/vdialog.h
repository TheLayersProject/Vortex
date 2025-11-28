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

#ifndef VDIALOG_H
#define VDIALOG_H

#include <QDialog>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include "vbutton.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VDialog : public QDialog
{
	Q_OBJECT

public:
	VDialog(const QString& title = "Dialog", QWidget* parent = nullptr);

	void set_icon(std::unique_ptr<VGraphic> icon);

	void setLayout(QLayout* layout);

	void update();

protected:
#ifdef _WIN32
	virtual bool nativeEvent(
		const QByteArray& eventType, void* message, qintptr* result) override;
#endif

	//virtual void paintEvent(QPaintEvent* event) override;

	QVBoxLayout* m_main_layout{ new QVBoxLayout };

private:
	//void init_attributes();
	void init_layout();
	void init_titlebar();

	bool m_hovering{ false };

	QHBoxLayout* m_titlebar_layout = new QHBoxLayout;

	QWidget* m_titlebar{ new QWidget };

	VLabel* m_icon_label{ nullptr };

	VLabel* m_title_label{ nullptr };

	VButton* m_exit_button = new VButton(
		std::make_unique<VGraphic>(":/images/exit.svg", QSize(20, 20)));
};

/*!
	Moves *upper_widget* to the center of *lower_widget*.
*/
VORTEX_WIDGETS_EXPORT void center(QWidget* upper_widget, QWidget* lower_widget);

VORTEX_NAMESPACE_END

#endif // VDIALOG_H
