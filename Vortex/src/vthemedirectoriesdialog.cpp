/*
 * Copyright (C) 2025 The Layers Project
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

#include <Vortex/vthemedirectoriesdialog.h>

#include <QFileDialog>
#include <Layers/ltheme.h>
#include <QLayers/qllabel.h>
#include <Vortex/vapplication.h>

using Layers::LString;
using Layers::LTheme;
using QLayers::QLButton;
using QLayers::QLGraphic;
using QLayers::QLLabel;
using Vortex::VThemeDirectoriesDialog;

VThemeDirectoriesDialog::VThemeDirectoriesDialog(QWidget* parent) : QLDialog("Theme Directories")
{
	init_layout();
	init_directory_list();
	set_icon(QLGraphic(":/images/theme_directories_icon.svg", QSize(25, 22)));
	set_object_name("Theme Directories Dialog");
	setFixedSize(620, 370);

	m_new_directory_button->set_object_name("New Directory Button");
	m_new_directory_button->setFixedHeight(50);
	m_new_directory_button->set_pointing_hand_cursor();
	m_new_directory_button->layout()->insertStretch(0);
	m_new_directory_button->layout()->addStretch();
	m_new_directory_button->text_label()->set_bold();

	connect(m_new_directory_button, &QLButton::clicked,
		[this] {
			QString dir = QFileDialog::getExistingDirectory(this, "Select Directory", QDir::homePath(),
				QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

			if (!dir.isEmpty())
			{
				qDebug() << QString("New Theme Directory: " + dir);

				vApp->load_themes(dir);

				add_directory_label(dir);

				//return done(QDialog::Accepted);
			}

			//return done(QDialog::Rejected);
		});

	apply_definition(lController.find_definition(path()));
}

void Vortex::VThemeDirectoriesDialog::add_directory_label(const QString& dir)
{
	QLLabel* directory_label = new QLLabel(dir);
	directory_label->set_object_name("Directory Label");
	directory_label->setFixedHeight(30);
	directory_label->set_left_padding(3.0);

	if (definition())
	{
		directory_label->apply_definition(
			definition()->find_item(directory_label->object_name()));
	}

	layout_directory_labels->addWidget(directory_label);
}

void Vortex::VThemeDirectoriesDialog::init_directory_list()
{
	QVariant _theme_directories = vApp->settings().value("themes/directories");

	if (_theme_directories.isValid())
	{
		QStringList theme_directories = _theme_directories.toStringList();
		for (const QString& theme_directory : theme_directories)
		{
			add_directory_label(theme_directory);
		}
	}
}

void VThemeDirectoriesDialog::init_layout()
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
