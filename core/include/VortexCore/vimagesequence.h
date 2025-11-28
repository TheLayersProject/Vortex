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

#ifndef VIMAGESEQUENCE_H
#define VIMAGESEQUENCE_H

#include <QDir>

#include "vortex_core_global.h"
#include "vortex_core_export.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_CORE_EXPORT VImageSequence
{
public:
	VImageSequence(QDir directory);

	VImageSequence(QFile file);

	QImage* frame(int i);

	void save(QFile file);

	qsizetype size() const;

private:
	QList<QImage> m_frames;
};
VORTEX_NAMESPACE_END

#endif // VIMAGESEQUENCE_H
