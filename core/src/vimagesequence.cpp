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

#include <VortexCore/vimagesequence.h>

#include <QImage>
#include <QPixmap>

using Vortex::VImageSequence;

VImageSequence::VImageSequence(QDir directory)
{
	QStringList image_filenames =
		directory.entryList(
			QStringList() << "*.png" << "*.PNG", QDir::Files);

	for (QString filename : image_filenames)
	{
		m_frames.append(QImage(directory.filePath(filename)));
	}
}

VImageSequence::VImageSequence(QFile file)
{
	if (file.exists())
	{
		if (!file.open(QIODevice::ReadOnly))
			qDebug() << "Could not read file '" + file.fileName() + "'";

		QDataStream in(&file);

		in >> m_frames;

		file.close();
	}
}

QImage* VImageSequence::frame(int i)
{
	if (!m_frames.isEmpty() && i < m_frames.size())
		return &m_frames[i];

	return nullptr;
}

void VImageSequence::save(QFile file)
{
	if (!file.open(QIODevice::WriteOnly))
	{
		qDebug() << "Could not create file '" + file.fileName() + "'";
		return;
	}

	QDataStream out(&file);

	out << m_frames;

	file.close();
}

qsizetype VImageSequence::size() const
{
	return m_frames.size();
}
