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

// #include <VortexWidgets/vcombobox.h>

// #include <QEvent>
// #include <QListView>
// #include <QPainter>

// #include <Layers/lalgorithms.h>
// #include <Layers/lstring.h>

// #include <VortexWidgets/vcalculate.h>
// #include <VortexWidgets/vcomboboxitemdelegate.h>
// #include <VortexWidgets/vconvert.h>
// #include <VortexWidgets/vbox.h>

// using Layers::LAttribute;
// using Layers::LString;

// using Vortex::VComboBox;

// VComboBox::VComboBox(QWidget* parent) : QComboBox(parent)
// {
// 	setItemDelegate(new VComboBoxItemDelegate);

// 	view()->window()->installEventFilter(this);
// 	view()->window()->setAttribute(Qt::WA_TranslucentBackground);
// 	view()->window()->setWindowFlags(
// 		Qt::Popup | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
// 	view()->setMouseTracking(true);

// 	update();
// }

// bool VComboBox::is_view_positioned_above() const
// {
// 	return view()->window()->y() <= mapToGlobal(this->rect().topLeft()).y();
// }

// void VComboBox::setFixedHeight(int h)
// {
// 	QComboBox::setFixedHeight(h);

// 	update();
// }

// void VComboBox::setFixedSize(int w, int h)
// {
// 	VComboBox::setFixedSize(QSize(w, h));
// }

// void VComboBox::setFixedSize(const QSize& s)
// {
// 	QComboBox::setFixedSize(s);

// 	update();
// }

// void VComboBox::setFixedWidth(int w)
// {
// 	QComboBox::setFixedWidth(w);

// 	update();
// }

// void VComboBox::showPopup()
// {
// 	QComboBox::showPopup();

// 	if (VComboBoxItemDelegate* combobox_delegate =
// 		dynamic_cast<VComboBoxItemDelegate*>(itemDelegate()))
// 	{
// 		combobox_delegate->set_is_above_control(is_view_positioned_above());
// 	}
// }

// void VComboBox::update()
// {
// 	QString style_sheet =
// 		"QComboBox::drop-down { "
// 		"width: 0px; "
// 		"}";

// 	setStyleSheet(style_sheet);

// 	view()->setStyleSheet(
// 		"QAbstractItemView {"
// 		"background: transparent;"
// 		"border: none;"
// 		"}"

// 		"QAbstractItemView::item {"
// 		"height: " + QString::number(height()) + "px;"
// 		"}"
// 	);

// 	QWidget::update();
// }

// bool VComboBox::eventFilter(QObject* object, QEvent* event)
// {
// 	if (object == view()->window())
// 		if (event->type() == QEvent::Show || event->type() == QEvent::Hide)
// 			update();

// 	return false;
// }

// void VComboBox::paint_box(QPainter* painter)
// {
// 	if (!painter)
// 		return;

// 	auto sc = state_combo();

// 	int border_thickness = m_border_thickness->as<double>(sc);

// 	LCornerRadii border_cr;
// 	LCornerRadii fill_cr;

// 	border_cr.top_left = m_corner_radius->as<double>(sc);
// 	border_cr.top_right = border_cr.top_left;
// 	border_cr.bottom_left = border_cr.top_left;
// 	border_cr.bottom_right = border_cr.top_left;

// 	if (view()->window()->isVisible())
// 		if (is_view_positioned_above())
// 		{
// 			border_cr.top_left = 0;
// 			border_cr.top_right = 0;
// 		}
// 		else
// 		{
// 			border_cr.bottom_left = 0;
// 			border_cr.bottom_right = 0;
// 		}

// 	fill_cr.top_left = (border_thickness) ?
// 		inner_radius(border_cr.top_left, border_thickness) :
// 		border_cr.top_left;

// 	fill_cr.top_right = (border_thickness) ?
// 		inner_radius(border_cr.top_right, border_thickness) :
// 		border_cr.top_right;

// 	fill_cr.bottom_left = (border_thickness) ?
// 		inner_radius(border_cr.bottom_left, border_thickness) :
// 		border_cr.bottom_left;

// 	fill_cr.bottom_right = (border_thickness) ?
// 		inner_radius(border_cr.bottom_right, border_thickness) :
// 		border_cr.bottom_right;

// 	QRect border_rect = QRect(
// 		QPoint(0, 0),
// 		size() + lsize(1));

// 	QRect fill_rect = QRect(
// 		lpoint(border_thickness),
// 		size() + lsize(1) - lsize(border_thickness * 2));

// 	QPainterPath fill_path =
// 		QLBox::box_path(fill_rect, fill_cr);
// 	QPainterPath border_path =
// 		QLBox::box_path(border_rect, border_cr) - fill_path;

// 	/* Draw Border */
// 	if (border_thickness)
// 	{
// 		if (const auto& stops = m_border_fill->as_if<std::vector<LString>>(sc))
// 		{
// 			QLinearGradient border_fill_grad;

// 			border_fill_grad.setStart(border_rect.left(), 0);
// 			border_fill_grad.setFinalStop(border_rect.right() + 1, 0);
// 			//border_fill_grad.setStops(to_QGradientStops(*stops));

// 			painter->fillPath(border_path, border_fill_grad);
// 		}
// 		else
// 			painter->fillPath(border_path,
// 				QColor(QString::fromStdString(
// 						m_border_fill->as<LString>(sc).c_str())));
// 	}

// 	/* Draw Fill */
// 	if (auto stops = m_fill->as_if<std::vector<LString>>(sc))
// 	{
// 		QLinearGradient fill_gradient;

// 		fill_gradient.setStart(fill_rect.left(), 0);
// 		fill_gradient.setFinalStop(fill_rect.right() + 1, 0);
// 		//fill_gradient.setStops(to_QGradientStops(*stops));

// 		painter->fillPath(fill_path, fill_gradient);
// 	}
// 	else
// 		painter->fillPath(fill_path,
// 			QColor(QString::fromStdString(m_fill->as<LString>(sc).c_str())));
// }

// void VComboBox::paintEvent(QPaintEvent* event)
// {
// 	QPainter painter(this);
// 	painter.setRenderHint(QPainter::Antialiasing);

// 	paint_box(&painter);

// 	QFont item_font = font();

// 	const QFontMetrics& item_font_metrics = QFontMetrics(item_font);

// 	QPainterPath item_text_path;

// 	QString item_text = currentData(Qt::DisplayRole).toString();

// 	item_text_path.addText(
// 		QPoint(10, rect().center().y() + (item_font_metrics.height() / 2) - 2),
// 		item_font,
// 		item_text
// 	);

// 	painter.fillPath(item_text_path,
// 		QColor(QString::fromStdString(m_text_color->as<LString>().c_str())));
// }
