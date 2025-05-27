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

#ifndef VUPDATEDIALOG_H
#define VUPDATEDIALOG_H

#include "vortex_global.h"
#include "vortex_export.h"

#include <QLayers/qldialog.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_EXPORT VUpdateDialog : public QLayers::QLDialog
{
	Q_OBJECT

public:
	VUpdateDialog(const QString& version, const QString& latest_version,
		QWidget* parent = nullptr);

private:
	void init_layout();

	QLayers::QLButton* m_remind_me_later_button{
		new QLayers::QLButton("Remind Me Later") };

	QLayers::QLButton* m_update_button{
		new QLayers::QLButton("Update") };

	QLayers::QLLabel* m_message_label;
};
VORTEX_NAMESPACE_END

#endif // VUPDATEDIALOG_H
