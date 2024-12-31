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

#ifndef VTHEMESWIDGET_H
#define VTHEMESWIDGET_H

#include <QLayers/qlbutton.h>
#include <Vortex/vthemecombobox.h>

#include <Vortex/vortex_global.h>

namespace Vortex{

	class VThemesWidget : public QLayers::QLWidget
	{
		Q_OBJECT

	public:
		VThemesWidget(QWidget* parent = nullptr);
		~VThemesWidget();

		void handle_theme_buttons_visibility();

		QLayers::QLButton* customize_theme_button() const;

		QLayers::QLButton* new_theme_button() const;

		VThemeComboBox* theme_combobox() const;

		void show_custom_theme_buttons(bool cond = true);

	private:
		void init_layout();

		QLayers::QLLabel* m_theme_label{ new QLayers::QLLabel("Theme") };

		VThemeComboBox* m_theme_combobox{ new VThemeComboBox };

		QLayers::QLButton* m_new_theme_button{
			new QLayers::QLButton(
				QLayers::QLGraphic(":/images/new_theme.svg", QSize(20, 20))) };
			
		QLayers::QLButton* m_customize_theme_button{
			new QLayers::QLButton(
				QLayers::QLGraphic(":/images/customize_theme.svg", QSize(20, 20))) };
			
		QLayers::QLButton* m_delete_theme_button{
			new QLayers::QLButton(
				QLayers::QLGraphic(":/images/delete_theme.svg", QSize(17, 20))) };
			
		QLayers::QLButton* m_theme_info_button{
			new QLayers::QLButton(
				QLayers::QLGraphic(":/images/info_theme.svg", QSize(20, 20))) };

		QLWidget* m_separator_1{ new QLWidget };
		QLWidget* m_separator_2{ new QLWidget };
		QLWidget* m_spacer_1{ new QLWidget };
		QLWidget* m_spacer_2{ new QLWidget };

		QMetaObject::Connection m_theme_buttons_handler_connection;

		//QLThemeEditorDialog* m_theme_editor_dialog{ nullptr };
	};
}

#endif // !VTHEMESWIDGET_H
