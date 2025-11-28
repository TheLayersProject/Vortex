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

#include <VortexWidgets/vlabel.h>

#include <QPainter>

#include <Layers/lstring.h>
#include <Layers/lstyle.h>
#include <VortexCore/vboxstyle.h>
#include <VortexCore/vfont.h>

using Layers::LAttribute;
using Layers::LString;

using Vortex::VGraphic;
using Vortex::VLabel;
//using Vortex::QLStylable;

VLabel::VLabel(QWidget* parent) :
	QLabel(parent)
{
	init();
}

VLabel::VLabel(const QString& text, QWidget* parent) :
	QLabel(text, parent)
{
	init();
}

//VLabel::VLabel(std::unique_ptr<VGraphic> graphic, QWidget* parent) :
//	m_graphic{ std::move(graphic) },
//	QLabel(parent)
//{
//	init();
//
//	if (m_graphic->svg_renderer())
//	{
//		// Set this VLabel as the parent of the QWebEngineView
//		m_graphic->svg_renderer()->setParent(this);
//		//m_repaint_connection =
//		//	connect(m_graphic->svg_renderer(), &VSvgRenderer::repaintNeeded,
//		//		[this] { QWidget::update(); });
//	}
//	else if (m_graphic->image_sequence())
//	{
//		connect(&m_timer, &QTimer::timeout, [this]
//			{ QWidget::update(); });
//
//		m_timer.start(17);
//	}
//
//	setMinimumSize(m_graphic->size());
//}

VLabel::VLabel(std::unique_ptr<VGraphic> graphic, QWidget* parent) :
	m_graphic{ std::move(graphic) },
	QLabel(parent)
{
	init();

	if (m_graphic->svg_renderer())
	{
		m_repaint_connection =
			connect(m_graphic->svg_renderer(), &VSvgRenderer::repaintNeeded,
				[this] { QWidget::update(); });
	}
	else if (m_graphic->image_sequence())
	{
		connect(&m_timer, &QTimer::timeout, [this]
			{ QWidget::update(); });

		m_timer.start(17);
	}

	setMinimumSize(m_graphic->size());
}

VLabel::~VLabel()
{
	disconnect(m_repaint_connection);
}

// QList<QLStylable*> VLabel::child_qlstylables(Qt::FindChildOptions options)
// {
// 	QList<QLStylable*> child_qldefinables;

// 	if (m_graphic && m_graphic->svg_renderer())
// 		child_qldefinables.append(m_graphic->svg_renderer());

// 	return child_qldefinables;
// }

VGraphic* VLabel::graphic() const
{
	return m_graphic.get();
}

void VLabel::reset()
{
	if (m_graphic)
	{
		m_graphic.reset();

		disconnect(m_repaint_connection);
	}

	setText("");
}

void VLabel::set_bold(bool enable)
{
	QFont f = font();
	f.setBold(enable);
	setFont(f);
}

void VLabel::set_font_size(int size)
{
	QFont f = font();

	f.setPointSize(size + V_FONT_OFFSET);

	setFont(f);
}

void VLabel::set_font_size_f(qreal size)
{
	QFont f = font();

	f.setPointSizeF(size + V_FONT_OFFSET);

	setFont(f);
}

void VLabel::set_graphic(std::unique_ptr<VGraphic> graphic)
{
	reset();

	m_graphic = std::move(graphic);

	if (m_graphic->svg_renderer())
	{
		m_repaint_connection =
			connect(m_graphic->svg_renderer(), &VSvgRenderer::repaintNeeded,
				[this] { QWidget::update(); });
	}
	else if (m_graphic->image_sequence())
	{
		connect(&m_timer, &QTimer::timeout, [this]
			{ QWidget::update(); });

		m_timer.start(17);
	}

	setMinimumSize(m_graphic->size());
}

void VLabel::set_italic(bool enable)
{
	QFont f = font();
	f.setItalic(enable);
	setFont(f);
}

void VLabel::set_left_padding(qreal padding)
{
	m_left_padding = padding;
	update();
}

void VLabel::setMaximumWidth(int maxw)
{
	QLabel::setMaximumWidth(maxw);
}

QSize VLabel::sizeHint() const
{
	if (m_graphic)
		return m_graphic->size();
	else
		return QLabel::sizeHint();
}

// LAttribute* VLabel::text_color() const
// {
// 	return m_text_color;
// }

bool VLabel::event(QEvent *e)
{
	if (e->type() == Vortex::VStyleAppliedEvent::EventType)
	{
        update();

		if (m_graphic && m_graphic->svg_renderer()) {
            if (Layers::LStyle* labelStyle = Vortex::get_widget_lstyle(this)) {
                // Look for "Svg" child style
                if (Layers::LStyle* svg_style = labelStyle->find_item("Svg")) {
                    Vortex::apply_layers_style(m_graphic->svg_renderer(), svg_style);
					share_state_pools(this, m_graphic->svg_renderer());
                }
            }
        }

        return true;
    }
    
    return QLabel::event(e);
}

void VLabel::paintEvent(QPaintEvent *event)
{
	//paint(this);

	if (m_graphic)
	{
		QPainter painter = QPainter(this);

		QSize graphic_size = m_graphic->size();

		int x = 0;
		int y = 0;

		Qt::Alignment a = alignment();

		if (a & Qt::AlignHCenter)
			x = (width() / 2) - (graphic_size.width() / 2);
		else if (a & Qt::AlignRight)
			x = width() - graphic_size.width();

		if (a & Qt::AlignVCenter)
			y = (height() / 2) - (graphic_size.height() / 2);
		else if (a & Qt::AlignBottom)
			y = height() - graphic_size.height();

		painter.setClipRect(QRectF(QPoint(x, y), graphic_size));

		if (m_graphic->svg_renderer())
		{
			m_graphic->svg_renderer()->render(&painter,
				QRectF(QPoint(x, y), graphic_size));
		}
		else if (m_graphic->image())
		{
			painter.drawImage(x, y, *m_graphic->image());
		}
		else if (VImageSequence* imgseq = m_graphic->image_sequence())
		{
			if (QImage* next_frame = imgseq->frame(m_frame++))
				painter.drawImage(x, y, *next_frame);
				
			if (m_frame == imgseq->size())
				m_frame = 0;
		}
	}
	else
		QLabel::paintEvent(event);
}

void VLabel::update()
{
	// Set text color via palette instead of stylesheet
    if (!m_graphic) {
        if (Layers::LStyle* style = Vortex::get_widget_lstyle(this)) {
            if (auto* attr = style->find_attribute("Text Color")) {
                QString textColor = QString::fromStdString(attr->as<LString>().c_str());
                
                QPalette pal = palette();
                pal.setColor(QPalette::WindowText, QColor::fromString(textColor));
                setPalette(pal);
            }
        }
    }
    
    // Set padding via margins instead of stylesheet
    if (m_left_padding > 0) {
        setContentsMargins(m_left_padding, 0, 0, 0);
    }

	// QString style_sheet = "QLabel {";

	// style_sheet += "background: transparent;";
	// style_sheet += "padding-left: " + QString::number(m_left_padding) + ";";

	// if (!m_graphic)
	// {
	// 	if (Layers::LStyle* style = get_widget_lstyle(this))
	// 	{
	// 		if (auto colorAttr = style->find_attribute("Text Color"))
	// 		{
	// 			QString colorStr = colorAttr->as<LString>().c_str();
	// 			if (!colorStr.isEmpty())
	// 			{
	// 				style_sheet += "color: " + colorStr + ";";
	// 			}
	// 		}
	// 	}
	// }
		

	// style_sheet += "}";

	// setStyleSheet(style_sheet);

	QWidget::update();
}

void VLabel::init()
{
	//init_attributes();
	update();

	set_font_size_f(font().pointSizeF() + V_FONT_OFFSET);
}

// void VLabel::init_attributes()
// {
// 	m_fill->set_value("#00000000");
// }
