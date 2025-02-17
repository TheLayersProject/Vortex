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

#include <Vortex/vthemecomboboxitemmodel.h>

using Layers::LTheme;
using Vortex::VThemeComboBoxItemModel;

VThemeComboBoxItemModel::VThemeComboBoxItemModel(QObject* parent) :
	QAbstractListModel(parent) {}

void VThemeComboBoxItemModel::append(LTheme* theme)
{
	beginInsertRows({}, m_themes.count(), m_themes.count());
	m_themes.append(theme);
	endInsertRows();
}

void VThemeComboBoxItemModel::clear()
{
	if (!m_themes.isEmpty())
	{
		beginResetModel();
		m_themes.clear();
		endResetModel();
	}
}

QVariant VThemeComboBoxItemModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid())
		return QVariant();

	else if (role == Qt::DisplayRole)
		return QString::fromStdString(m_themes[index.row()]->object_name().c_str());

	else if (role == Qt::UserRole)
		return QVariant::fromValue(m_themes[index.row()]);
	
	return QVariant();
}

int VThemeComboBoxItemModel::rowCount(const QModelIndex& parent) const
{
	if (!parent.isValid())
		return m_themes.count();
	else
		return 0;
}
