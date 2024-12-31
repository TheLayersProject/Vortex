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

#ifndef VGITHUBREPO_H
#define VGITHUBREPO_H

#include <QString>

#include "vortex_global.h"
#include "vortex_export.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_EXPORT VGitHubRepo
{
public:
	VGitHubRepo(const QString& repo_url);

	QString to_string() const;

private:
	QString m_repo_name{ "" };
	QString m_user_name{ "" };
};
VORTEX_NAMESPACE_END

#endif // !VGITHUBREPO_H
