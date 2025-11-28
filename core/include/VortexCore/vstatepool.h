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

#ifndef VSTATEPOOL_H
#define VSTATEPOOL_H

#include <QObject>

#include "vortex_core_global.h"
#include "vortex_core_export.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_CORE_EXPORT VStatePool : public QObject
{
	Q_OBJECT

signals:
	void changed();

public:
	VStatePool(const QString& name, QObject* parent = nullptr);

	VStatePool(const QString& name, QStringList states,
		QObject* parent = nullptr);

	void add_state(const QString& state);

	void set_state(const QString& state);

	QString state() const;

private:
	QString m_name;

	QString m_state;

	QStringList m_states;
};
VORTEX_NAMESPACE_END

#endif // !QLSTATEPOOL_H
