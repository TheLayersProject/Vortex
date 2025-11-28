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

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <VortexWidgets/vdialog.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VUpdateDialog : public VDialog
{
	Q_OBJECT

public:
	VUpdateDialog(const QString& version, const QString& latest_version,
		QWidget* parent = nullptr);

private:
	void init_layout();

	VButton* m_remind_me_later_button{
		new VButton("Remind Me Later") };

	VButton* m_update_button{
		new VButton("Update") };

	VLabel* m_message_label;
};
VORTEX_NAMESPACE_END

#endif // VUPDATEDIALOG_H
