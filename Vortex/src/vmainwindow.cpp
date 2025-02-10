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

#include <Vortex/vmainwindow.h>

#ifdef _WIN32
#include <Windows.h>
#include <windowsx.h>
#endif

#include <QIcon>
#include <QPainterPath>
#include <Layers/lstring.h>
#include <QLayers/qlcalculate.h>
#include <Vortex/vapplication.h>

#include "vmainwindowtitlebar.h"
#include "vsettingsmenu.h"

using Layers::LString;

using Vortex::VSettingsMenu;
using Vortex::VMainWindowTitlebar;
using Vortex::VMainWindow;

VMainWindow::VMainWindow(QWidget* parent) :
	m_titlebar{ new VMainWindowTitlebar },
	QLWidget(parent)
{
	init_attributes();
	init_layout();
	init_titlebar_connections();
	resize(1000, 700);
	set_object_name("Main Window");
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

	connect(m_titlebar->menu_tab_bar(), &VTabBar::index_changed,
		[this](int prev_index, int new_index)
		{
			if (QWidget* prev_widget = (prev_index != -1) ?
				m_central_widgets[prev_index] : nullptr)
			{
				prev_widget->hide();
			}

			if (QWidget* new_widget = (new_index != -1) ?
				m_central_widgets[new_index] : nullptr)
			{
				new_widget->show();
			}
		});

	connect(m_titlebar->menu_tab_bar(), &VTabBar::tab_closed,
		[this](int i)
		{
			m_central_widgets.takeAt(i)->deleteLater();

			if (m_central_widgets.isEmpty())
				vApp->quit();
		});

	m_separator->set_object_name("Separator");
	m_separator->setFixedHeight(3);

	apply_definition(lController.find_definition(path()));
}

void VMainWindow::open_central_widget(
	QWidget* central_widget, const QString& tab_text)
{
	m_titlebar->menu_tab_bar()->add_tab(tab_text);

	_open_central_widget(central_widget);
}

void VMainWindow::open_central_widget(
	QWidget* central_widget, const QLayers::QLGraphic& tab_icon_graphic,
	const QString& tab_text)
{
	m_titlebar->menu_tab_bar()->add_tab(tab_icon_graphic, tab_text);

	_open_central_widget(central_widget);
}

void VMainWindow::update()
{
	if (isMaximized())
		m_main_layout->setContentsMargins(0, 0, 0, 0);
	else
	{
		int border_thickness = m_border_thickness->as<double>();

		m_main_layout->setContentsMargins(
			border_thickness + m_margins_left->as<double>(),
			border_thickness + m_margins_top->as<double>(),
			border_thickness + m_margins_right->as<double>(),
			border_thickness + m_margins_bottom->as<double>());
	}

	QWidget::update();
}

#ifdef _WIN32
bool VMainWindow::nativeEvent(
	const QByteArray& eventType, void* message, qintptr* result)
{
	MSG* msg = static_cast<MSG*>(message);

	if (msg->message == WM_NCHITTEST)
	{
		if (isMaximized())
			return false;

		*result = 0;
		const LONG borderWidth =
			border_thickness()->as<qreal>() * devicePixelRatio();
		RECT winrect;
		GetWindowRect(reinterpret_cast<HWND>(winId()), &winrect);

		// must be short to correctly work with multiple monitors
		short x = msg->lParam & 0x0000FFFF;
		short y = (msg->lParam & 0xFFFF0000) >> 16;

		bool resizeWidth = minimumWidth() != maximumWidth();
		bool resizeHeight = minimumHeight() != maximumHeight();

		if (resizeWidth)
		{
			//left border
			if (x >= winrect.left && x < winrect.left + borderWidth)
			{
				*result = HTLEFT;
			}
			//right border
			if (x < winrect.right && x >= winrect.right - borderWidth)
			{
				*result = HTRIGHT;
			}
		}
		if (resizeHeight)
		{
			//bottom border
			if (y < winrect.bottom && y >= winrect.bottom - borderWidth)
			{
				*result = HTBOTTOM;
			}
			//top border
			if (y >= winrect.top && y < winrect.top + borderWidth)
			{
				*result = HTTOP;
			}
		}
		if (resizeWidth && resizeHeight)
		{
			//bottom left corner
			if (x >= winrect.left && x < winrect.left + borderWidth &&
				y < winrect.bottom && y >= winrect.bottom - borderWidth)
			{
				*result = HTBOTTOMLEFT;
			}
			//bottom right corner
			if (x < winrect.right && x >= winrect.right - borderWidth &&
				y < winrect.bottom && y >= winrect.bottom - borderWidth)
			{
				*result = HTBOTTOMRIGHT;
			}
			//top left corner
			if (x >= winrect.left && x < winrect.left + borderWidth &&
				y >= winrect.top && y < winrect.top + borderWidth)
			{
				*result = HTTOPLEFT;
			}
			//top right corner
			if (x < winrect.right && x >= winrect.right - borderWidth &&
				y >= winrect.top && y < winrect.top + borderWidth)
			{
				*result = HTTOPRIGHT;
			}
		}

		if (m_titlebar == QApplication::widgetAt(QCursor::pos()))
		{
			*result = HTCAPTION;
			return true;
		}

		if (*result != 0)
			return true;
	}

	return false;
}
#endif

void VMainWindow::init_attributes()
{
	m_border_thickness->set_value(15.0);
	m_border_fill->set_value(std::vector<LString>({ "0:#3a3c42", "1:#42454d" }));
	m_corner_radii_top_left->set_value(10.0);
	m_corner_radii_top_right->set_value(10.0);
	m_corner_radii_bottom_left->set_value(10.0);
	m_corner_radii_bottom_right->set_value(10.0);

	m_separator->fill()->set_value("#25272b");
}

void VMainWindow::init_layout()
{
	int margin = border_thickness()->as<double>();

	m_main_layout->setContentsMargins(margin, margin, margin, margin);
	m_main_layout->setSpacing(0);
	m_main_layout->addWidget(m_titlebar);
	m_main_layout->addWidget(m_separator);

	setLayout(m_main_layout);
}

void VMainWindow::init_titlebar_connections()
{
	connect(m_titlebar->settings_button(), &QLayers::QLButton::clicked,
		[this]
		{
			VSettingsMenu* settings_menu = new VSettingsMenu;

			open_central_widget(settings_menu,
				QLayers::QLGraphic(":/images/settings_animated.svg", QSize(24, 24)),
				"Settings");
		});

	connect(m_titlebar->minimize_button(), &QLayers::QLButton::clicked,
		[this]
		{
			showMinimized();
		});

	connect(m_titlebar->maximize_button(), &QLayers::QLButton::clicked,
		[this]
		{
			if (isMaximized())
				showNormal();
			else
				showMaximized();

			update();
		});

	connect(m_titlebar->exit_button(), &QLayers::QLButton::clicked,
		[this] { qApp->quit(); });
}

void VMainWindow::_open_central_widget(QWidget* central_widget)
{
	if (LDefinable* central_themeable =
		dynamic_cast<LDefinable*>(central_widget))
	{
		if (definition())
			central_themeable->apply_definition(definition()->find_item(
				central_widget->objectName().toStdString().c_str()));
	}

	m_central_widgets.append(central_widget);
	m_main_layout->addWidget(central_widget);

	set_active_central_widget(central_widget);
}

void VMainWindow::set_active_central_widget(QWidget* central_widget)
{
	if (m_central_widgets.contains(central_widget))
		m_titlebar->menu_tab_bar()->set_current_index(
			m_central_widgets.indexOf(central_widget));
}
