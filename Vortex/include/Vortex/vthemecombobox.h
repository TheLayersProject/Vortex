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

#ifndef VTHEMECOMBOBOX_H
#define VTHEMECOMBOBOX_H

#include <Layers/ltheme.h>

#include "vortex_global.h"
#include "vortex_export.h"

#include <QLayers/qlcombobox.h>

VORTEX_NAMESPACE_BEGIN
class VThemeComboBoxItemModel;

class VORTEX_EXPORT VThemeComboBox : public QLayers::QLComboBox
{
	Q_OBJECT

public:
	VThemeComboBox(QWidget* parent = nullptr);

	void add_theme(Layers::LTheme* theme, bool set_as_current_index = false);

	void clear();

protected:
	//virtual bool eventFilter(QObject* object, QEvent* event) override;

	virtual void paintEvent(QPaintEvent* event) override;

private:
	void init_item_delegate();

	VThemeComboBoxItemModel* m_model;

	int m_highlighted_index = -1;
};
VORTEX_NAMESPACE_END

#endif // VTHEMECOMBOBOX_H
