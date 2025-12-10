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

#include <VortexWidgets/vstyledirectoriesdialog.h>

#include <QFileDialog>
#include <Layers/lstyle.h>
#include <Layers/ltheme.h>
#include <VortexCore/vapplication.h>
#include <VortexCore/vboxstyle.h>
#include <VortexWidgets/vlabel.h>

using Layers::LString;
using Layers::LStyle;
using Layers::LTheme;
using Vortex::VButton;
using Vortex::VGraphic;
using Vortex::VLabel;
using Vortex::VStyleDirectoriesDialog;

VStyleDirectoriesDialog::VStyleDirectoriesDialog(QWidget* parent) : VDialog("Style Directories")
{
	init_layout();
	init_directory_list();
	set_icon(std::make_unique<VGraphic>(":/images/theme_directories_icon.svg", QSize(25, 22)));
	setObjectName("Style Directories Dialog");
	setFixedSize(620, 370);

	m_new_directory_button->setObjectName("New Directory Button");
	m_new_directory_button->setFixedHeight(50);
	m_new_directory_button->set_pointing_hand_cursor();
	m_new_directory_button->layout()->insertStretch(0);
	m_new_directory_button->layout()->addStretch();
	m_new_directory_button->text_label()->set_bold();

	connect(m_new_directory_button, &VButton::clicked,
		[this] {
			QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath(),
				QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

			if (!dir.isEmpty())
			{
				qDebug() << QString("New Style Directory: " + dir);

				vApp->load_user_styles(dir);

				add_directory_label(dir);

				//return done(QDialog::Accepted);
			}

			//return done(QDialog::Rejected);
		});

	Vortex::apply_layers_style_auto(this);
}

void Vortex::VStyleDirectoriesDialog::add_directory_label(const QString& dir)
{
	VLabel* directory_label = new VLabel(dir);
	directory_label->setObjectName("Directory Label");
	directory_label->setFixedHeight(30);
	directory_label->set_left_padding(3.0);

	// if (LStyle* s = LStylable::style())
	// {
	// 	directory_label->apply_style(
	// 		s->find_item(directory_label->name()));
	// }

	layout_directory_labels->addWidget(directory_label);
}

void Vortex::VStyleDirectoriesDialog::init_directory_list()
{
	QVariant _style_directories = vApp->settings().value("styles/directories");

	if (_style_directories.isValid())
	{
		QStringList style_directories = _style_directories.toStringList();
		for (const QString& style_directory : style_directories)
		{
			add_directory_label(style_directory);
		}
	}
}

void VStyleDirectoriesDialog::init_layout()
{
	layout_directory_labels->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout* main_layout = new QVBoxLayout;
	main_layout->setContentsMargins(15, 15, 15, 15);
	main_layout->setSpacing(25);
	main_layout->addLayout(layout_directory_labels);
	main_layout->addStretch();
	main_layout->addWidget(m_new_directory_button);
	setLayout(main_layout);
}
