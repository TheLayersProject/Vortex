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

#include <VortexWidgets/vcheckbox.h>

#include <QMouseEvent>
#include <QVBoxLayout>

#include <VortexCore/vboxstyle.h>

using Vortex::VCheckBox;

VCheckBox::VCheckBox(QWidget* parent) : QWidget(parent)
{
	installEventFilter(this);
	init_layout();
	setFixedSize(40, 40);
	setObjectName("Check Box");
	Vortex::add_state_pool(this, m_check_states);

	m_check_states->set_state("Unchecked");

	m_check_label->setObjectName("Check Label");
	m_check_label->setFixedSize(size());
	m_check_label->hide();
}

bool VCheckBox::is_checked() const
{
	return m_check_states->state() == "Checked";
}

void VCheckBox::set_state(const QString& state)
{
	m_check_states->set_state(state);

	if (m_check_states->state() == "Unchecked")
	{
		m_check_label->hide();
	}
	else
	{
		m_check_label->show();
	}
}

bool VCheckBox::eventFilter(QObject* object, QEvent* event)
{
	if (event->type() == QEvent::Enter)
	{
		setCursor(Qt::PointingHandCursor);
	}
	else if (event->type() == QEvent::Leave)
	{
		unsetCursor();
	}
	else if (
		event->type() == QEvent::MouseButtonPress || 
		event->type() == QEvent::MouseButtonDblClick)
	{
		QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

		if (mouse_event->button() & Qt::LeftButton)
		{
			if (m_check_states->state() == "Unchecked")
			{
				set_state("Checked");
			}
			else
			{
				set_state("Unchecked");
			}

			emit clicked();
		}
	}

	return false;
}

void VCheckBox::init_layout()
{
	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(0, 0, 0, 0);
	main_layout->addWidget(m_check_label);
	m_check_label->setAlignment(Qt::AlignCenter);
	setLayout(main_layout);
}
