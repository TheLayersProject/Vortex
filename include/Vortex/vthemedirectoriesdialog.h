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

#ifndef VTHEMEDIRECTORIESDIALOG_H
#define VTHEMEDIRECTORIESDIALOG_H

#include <Vortex/vortex_global.h>

#include <QLayers/qlbutton.h>
#include <QLayers/qldialog.h>

namespace Vortex {
	class VThemeDirectoriesDialog : public QLayers::QLDialog
	{
		Q_OBJECT

	public:
		VThemeDirectoriesDialog(QWidget* parent = nullptr);

	private:
		void add_directory_label(const QString& dir);
		void init_directory_list();
		void init_layout();

		QVBoxLayout* layout_directory_labels{ new QVBoxLayout };

		QLayers::QLButton* m_new_directory_button{
			new QLayers::QLButton(
				std::make_unique<QLayers::QLGraphic>(
					":/images/new_theme_directory_icon.svg", QSize(27, 26)),
				"New Theme Directory") };
	};
}

#endif // !VTHEMEDIRECTORIESDIALOG_H
