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

#include <VortexWidgets/vlineeditor.h>

#include <QEvent>
#include <QGraphicsOpacityEffect>
#include <QResizeEvent>
#include <QStyle>
#include <Layers/lstring.h>
#include <Layers/lstyle.h>
#include <VortexCore/vboxstyle.h>

using Layers::LAttribute;
using Layers::LString;

using Vortex::VLineEditor;

VLineEditor::VLineEditor(QWidget* parent) : QLineEdit(parent)
{
	//init_attributes();
	//installEventFilter(this);
	//setFocusProxy(m_line_edit);

	//m_line_edit->installEventFilter(this);
	//m_line_edit->installEventFilter(this);

	QGraphicsOpacityEffect* pretext_opacity = new QGraphicsOpacityEffect;
	pretext_opacity->setOpacity(0.5);

	m_pretext_label->setAttribute(Qt::WA_TransparentForMouseEvents);
	m_pretext_label->setGraphicsEffect(pretext_opacity);
	m_pretext_label->setObjectName("Pretext Label");
	m_pretext_label->set_italic();
	m_pretext_label->move(m_left_padding->as<double>(), m_pretext_label->y());

	// Update the base position for the label
	updateBaseLabelPosition();

	// Store initial font size
	m_normalFontSize = m_pretext_label->font().pointSizeF();

	// Setup animations
	setupAnimations();

	m_left_padding->on_change([this] {
		update();
		updateBaseLabelPosition();
		m_pretext_label->move(m_baseLabelPos.toPoint());
		//m_line_edit->move(m_baseLabelPos.toPoint());
		});

	//connect(m_line_edit, &QLineEdit::textEdited, [this] {
	connect(this, &QLineEdit::textEdited, [this] {
		if (const auto& text_string = m_text->as_if<LString>())
			m_text->set_value(QLineEdit::text().toStdString().c_str());
		else if (const auto& text_double = m_text->as_if<double>())
			m_text->set_value(QLineEdit::text().toDouble());

		emit text_edited(QLineEdit::text());
		});

	connect(this, &QLineEdit::editingFinished, [this]
		{
			emit editing_finished();
		});

	m_text->on_change([this] { update(); });

	update();
}

void VLineEditor::setupAnimations()
{
	m_animationGroup = new QParallelAnimationGroup(this);

	// Position animation
	m_positionAnimation = new QPropertyAnimation(this, "labelPos");
	m_positionAnimation->setDuration(150);
	m_positionAnimation->setEasingCurve(QEasingCurve::InOutCubic);

	// Font size animation
	m_fontSizeAnimation = new QPropertyAnimation(this, "labelFontSize");
	m_fontSizeAnimation->setDuration(150);
	m_fontSizeAnimation->setEasingCurve(QEasingCurve::InOutCubic);

	m_animationGroup->addAnimation(m_positionAnimation);
	m_animationGroup->addAnimation(m_fontSizeAnimation);
}

QPointF VLineEditor::labelPos() const
{
	return m_pretext_label->pos();
}

void VLineEditor::setLabelPos(const QPointF& pos)
{
	m_pretext_label->move(pos.toPoint());
}

qreal VLineEditor::labelFontSize() const
{
	return m_pretext_label->font().pointSizeF();
}

void VLineEditor::setLabelFontSize(qreal size)
{
	QFont font = m_pretext_label->font();
	font.setPointSizeF(size);
	m_pretext_label->setFont(font);
}

void VLineEditor::updateBaseLabelPosition()
{
	double left_padding = m_left_padding->as<double>();
	m_baseLabelPos = QPointF(left_padding, m_pretext_label->y());
}

void VLineEditor::startFloatingAnimation(bool floating)
{
	if (floating == m_isFloating) {
		return;  // Already in the requested state
	}

	QPointF startPos = m_pretext_label->pos();
	QPointF endPos;

	if (floating) {
		endPos = QPointF(m_baseLabelPos.x(), m_baseLabelPos.y() + m_floatingOffset);
		m_positionAnimation->setStartValue(startPos);
		m_positionAnimation->setEndValue(endPos);
		m_fontSizeAnimation->setStartValue(m_normalFontSize);
		m_fontSizeAnimation->setEndValue(m_floatingFontSize);
	}
	else {
		endPos = m_baseLabelPos;
		m_positionAnimation->setStartValue(startPos);
		m_positionAnimation->setEndValue(endPos);
		m_fontSizeAnimation->setStartValue(m_floatingFontSize);
		m_fontSizeAnimation->setEndValue(m_normalFontSize);
	}

	m_isFloating = floating;
	m_animationGroup->start();
}

VLineEditor::~VLineEditor()
{
	if (m_default_value)
		delete m_default_value;
}

void VLineEditor::set_default_value(const QString& default_value)
{
	if (m_default_value)
		delete m_default_value;

	m_default_value = new QString(default_value);
}

void VLineEditor::set_font_size(int size)
{
	QFont line_edit_font = font();
	line_edit_font.setPointSize(size);
	setFont(line_edit_font);

	update();
}

void VLineEditor::set_font_size_f(qreal size)
{
	QFont line_edit_font = font();
	line_edit_font.setPointSizeF(size);
	setFont(line_edit_font);

	update();
}

void VLineEditor::set_pretext(const QString &pretext)
{
	m_pretext_label->setText(pretext);
}

void VLineEditor::set_text(const QString& text)
{
	setText(text);

	m_text->set_value(text.toStdString().c_str());

	if (!text.isEmpty() && !m_isFloating)
	{
		startFloatingAnimation(true);
	}
	else if (text.isEmpty() && m_isFloating)
	{
		startFloatingAnimation(false);
	}
}

void VLineEditor::set_validator(const QValidator* validator)
{
	setValidator(validator);
}

LAttribute* VLineEditor::left_padding() const
{
	return m_left_padding;
}

LAttribute* VLineEditor::text_color() const
{
	return m_text_color;
}

LAttribute* VLineEditor::text() const
{
	return m_text;
}

// void VLineEditor::update()
// {
// 	double left_padding = m_left_padding->as<double>();
// 	double top_padding = m_pretext_label ?
// 		16.0 : 0.0;

// 	//m_line_edit->setStyleSheet(
// 	setStyleSheet(
// 		"QLineEdit {"
// 		"border: none;"
// 		"background: transparent;"
// 		"color: " + QString::fromStdString(
// 			m_text_color->as<LString>().c_str()) + ";"
// 		"padding-top: " + QString::number(top_padding) + "px;"
// 		// "padding-left: " + QString::number(
// 		// 	m_margins_left->as<double>() + left_padding) + "px;"
// 		"padding-bottom: 2px;"
// 		"}");

// 	if (m_pretext_label)
// 	{
// 		m_pretext_label->move(
// 			left_padding, m_pretext_label->y());
// 	}

// 	QString text_qstring;

// 	if (const auto& text_string = m_text->as_if<LString>())
// 		text_qstring = QString::fromStdString(text_string->c_str());
// 	else if (const auto& text_double = m_text->as_if<double>())
// 		text_qstring = QString::number(*text_double);

// 	if (QLineEdit::text() != text_qstring)
// 		setText(text_qstring);

// 	QLineEdit::update();
// }

void VLineEditor::update()
{
	if (Layers::LStyle* style = Vortex::get_widget_lstyle(this)) {
		if (auto* attr = style->find_attribute("Text Color")) {
			QString textColor = QString::fromStdString(attr->as<LString>().c_str());
			
			QPalette pal = palette();
			pal.setColor(QPalette::Text, QColor::fromString(textColor));
			setPalette(pal);
		}
	}

	// Set text padding
    double top_padding = m_pretext_label ? 16.0 : 0.0;
    double left_padding = m_left_padding->as<double>();
    
    setTextMargins(left_padding, top_padding, 0, 2);  // left, top, right, bottom
}

bool VLineEditor::event(QEvent* e)
{
	// if (object == m_line_edit)
	// {
	if (e->type() == Vortex::VStyleAppliedEvent::EventType)
	{
        update();
        return true;
    }
	else if (e->type() == QEvent::FocusOut)
	{
		if (QLineEdit::text().isEmpty())
		{
			if (m_default_value)
			{
				setText(*m_default_value);
			}
			startFloatingAnimation(false);
		}
	}
	else if (e->type() == QEvent::FocusIn)
	{
		qDebug() << "VLineEditor style:" << style()->metaObject()->className();

		startFloatingAnimation(true);
	}
	// }
	// else if (object == this)
	// {
	if (e->type() == QEvent::Resize)
	{
		QResizeEvent* resize_event = static_cast<QResizeEvent*>(e);
		//m_line_edit->setFixedSize(resize_event->size());
		setFixedSize(resize_event->size());
		//m_pretext_label->setFixedHeight(m_line_edit->height());
		m_pretext_label->setFixedHeight(height());
		updateBaseLabelPosition();
	}
	//}

	return QLineEdit::event(e);

	//return false;
}

// void VLineEditor::init_attributes()
// {
// 	m_corner_radii_top_left->set_value(5.0);
// 	m_corner_radii_top_right->set_value(5.0);
// 	m_corner_radii_bottom_left->set_value(5.0);
// 	m_corner_radii_bottom_right->set_value(5.0);
// 	m_fill->set_value("#c0c0c0");
// }
