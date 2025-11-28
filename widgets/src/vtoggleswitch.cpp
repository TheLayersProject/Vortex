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

#include <VortexWidgets/vtoggleswitch.h>

#include <QHBoxLayout>
#include <QMouseEvent>
#include <VortexCore/vboxstyle.h>

using Layers::LAttribute;
using Vortex::VToggleSwitch;

VToggleSwitch::VToggleSwitch(bool vertical, QWidget* parent) :
	m_vertical{ vertical }, QWidget(parent)
{
	//init_attributes();
	init_layout();
	Vortex::add_state_pool(this, m_toggle_states);

	installEventFilter(this);
	setFixedSize(40, 40);
	setObjectName("Toggle Switch");

	m_square->setObjectName("Square");
	m_square->setFixedSize(10, 10);

	update_spacer_size();
	m_spacer->hide();

	m_toggle_states->set_state("Untoggled");
}

void VToggleSwitch::set_toggled(bool toggled)
{
	if ((toggled && m_toggle_states->state() != "Toggled") ||
		(!toggled && m_toggle_states->state() == "Toggled"))
	{
		toggle();
	}
}

void VToggleSwitch::setFixedHeight(int h)
{
	QWidget::setFixedHeight(h);

	update_spacer_size();
}

void VToggleSwitch::toggle(bool emit_toggled_event)
{
	if (m_toggle_states->state() == "Untoggled")
	{
		m_toggle_states->set_state("Toggled");
		m_spacer->show();

		if (emit_toggled_event)
			emit toggled_event(true);
	}
	else
	{
		m_toggle_states->set_state("Untoggled");
		m_spacer->hide();

		if (emit_toggled_event)
			emit toggled_event(false);
	}

	QWidget::update();
}

bool VToggleSwitch::toggled() const
{
	return (m_toggle_states->state() == "Toggled");
}

bool VToggleSwitch::eventFilter(QObject* object, QEvent* event)
{
	// TODO: See if you want to call super's eventFilter()
	if ((event->type() == QEvent::MouseButtonPress ||
		event->type() == QEvent::MouseButtonDblClick) &&
		object == this)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			toggle();
		}
	}

	return false;
}

// void VToggleSwitch::init_attributes()
// {
// 	m_border_fill->set_value("#1e2023");
// 	//border_fill()->create_state("Toggled", "#6fc65b");
// 	//Layers::lMake<LAttribute>(m_border_fill, "Toggled", "#6fc65b");
// 	m_border_thickness->set_value(3.0);
// 	m_corner_radii_top_left->set_value(4.0);
// 	m_corner_radii_top_right->set_value(4.0);
// 	m_corner_radii_bottom_left->set_value(4.0);
// 	m_corner_radii_bottom_right->set_value(4.0);
// 	m_fill->set_value("#00000000");
// 	//m_fill->create_state("Toggled", "#6fc65b");
// 	//Layers::lMake<LAttribute>(m_fill, "Toggled", "#6fc65b");
// 	if (m_vertical)
// 		set_margin(10.0);
// 	else
// 	{
// 		m_margins_top->set_value(10.0);
// 		m_margins_bottom->set_value(10.0);
// 	}

// 	m_square->corner_radii_top_left()->set_value(2.0);
// 	m_square->corner_radii_top_right()->set_value(2.0);
// 	m_square->corner_radii_bottom_left()->set_value(2.0);
// 	m_square->corner_radii_bottom_right()->set_value(2.0);
// 	m_square->fill()->set_value("#1e2023");
// 	//m_square->fill()->create_state("Toggled", "#ffffff");
// 	//Layers::lMake<LAttribute>(m_square->fill(), "Toggled", "#ffffff");

// 	//m_spacer->fill()->set_disabled();
// 	m_spacer->fill()->set_value("#0000ff");
// }

void VToggleSwitch::init_layout()
{
	if (m_vertical)
	{
		m_layout_v = new QVBoxLayout;

		update_layout_margins();

		m_layout_v->setSpacing(0);
		m_layout_v->addWidget(m_spacer);
		m_layout_v->addWidget(m_square);
		m_layout_v->addStretch();
		m_layout_v->setAlignment(m_spacer, Qt::AlignHCenter);
		m_layout_v->setAlignment(m_square, Qt::AlignHCenter);

		setLayout(m_layout_v);
	}
	else
	{
		m_layout_h = new QHBoxLayout;

		update_layout_margins();

		m_layout_h->setSpacing(0);
		m_layout_h->addWidget(m_spacer);
		m_layout_h->addWidget(m_square);
		m_layout_h->addStretch();
		m_layout_h->setAlignment(m_spacer, Qt::AlignVCenter);
		m_layout_h->setAlignment(m_square, Qt::AlignVCenter);

		setLayout(m_layout_h);
	}
}

void VToggleSwitch::update_layout_margins()
{
	// int b_thickness = border_thickness()->as<double>();

	// if (m_layout_v)
	// 	m_layout_v->setContentsMargins(
	// 		0, m_margins_top->as<double>() + b_thickness + a_padding_top.as<double>(),
	// 		0, a_padding_bottom.as<double>() + b_thickness + m_margins_bottom->as<double>());
	// else if (m_layout_h)
	// 	m_layout_h->setContentsMargins(
	// 		m_margins_left->as<double>() + b_thickness + a_padding_left.as<double>(), 0,
	// 		a_padding_right.as<double>() + b_thickness + m_margins_right->as<double>(), 0);
}

void VToggleSwitch::update_spacer_size()
{
	// int b_thickness = border_thickness()->as<double>();

	// if (m_vertical)
	// {
	// 	m_spacer->setFixedSize(
	// 		0, height() - m_margins_top->as<double>() - b_thickness - a_padding_top.as<double>() - m_square->height() - a_padding_bottom.as<double>() - b_thickness - m_margins_bottom->as<double>()
	// 	);
	// }
	// else
	// {
	// 	m_spacer->setFixedSize(
	// 		width() - m_margins_left->as<double>() - b_thickness - a_padding_left.as<double>() - m_square->width() - a_padding_right.as<double>() - b_thickness - m_margins_right->as<double>(), 0
	// 	);
	// }
}
