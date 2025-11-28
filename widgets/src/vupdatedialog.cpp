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

#include <VortexWidgets/vupdatedialog.h>

using Vortex::VButton;
using Vortex::VGraphic;
using Vortex::VLabel;
using Vortex::VUpdateDialog;
//using Vortex::VDefinable;

VUpdateDialog::VUpdateDialog(
	const QString& version, const QString& latest_version,
	QWidget* parent
) :
	m_message_label{
		new VLabel(
			"There is an update available to download. "
			"Would you like to update the software now?\n\n"
			"Current Version: " + version + "\n\n"
			"Latest Version: " + latest_version)
	},
	VDialog("Update Available", parent)
{
	setFixedSize(525, 300);
	set_icon(std::make_unique<VGraphic>(":/images/update_icon.svg"));
	setObjectName("Update Dialog");

	m_remind_me_later_button->setObjectName("Remind Me Later Button");
	m_remind_me_later_button->set_padding(8, 6, 8, 6);
	connect(m_remind_me_later_button, &VButton::clicked,
		[this] { done(QDialog::Rejected); });

	m_update_button->setObjectName("Update Button");
	m_update_button->set_padding(8, 6, 8, 6);
	connect(m_update_button, &VButton::clicked,
		[this] { done(QDialog::Accepted); });

	m_message_label->setObjectName("Message Label");
	m_message_label->set_font_size(15);
	m_message_label->setWordWrap(true);

	init_layout();
}

void VUpdateDialog::init_layout()
{
	// Buttons Layout
	QHBoxLayout* buttons_layout = new QHBoxLayout;

	buttons_layout->setContentsMargins(0, 0, 0, 0);
	buttons_layout->setSpacing(15);
	buttons_layout->addStretch();
	buttons_layout->addWidget(m_remind_me_later_button);
	buttons_layout->addWidget(m_update_button);

	// Layout
	QVBoxLayout* layout = new QVBoxLayout;

	layout->setContentsMargins(15, 22, 15, 15);
	layout->addWidget(m_message_label);
	layout->addStretch();
	layout->addLayout(buttons_layout);
	layout->setAlignment(m_message_label, Qt::AlignLeft);

	setLayout(layout);
}
