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

#ifndef VDOWNLOADER_H
#define VDOWNLOADER_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "vortex_global.h"
#include "vortex_export.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_EXPORT VDownloader : public QObject
{
	Q_OBJECT

public:
	VDownloader(QObject* parent = nullptr);

	QNetworkReply* download(const QUrl& file_url);

	QNetworkReply* download(const QUrl& file_url, const QDir& directory);

private:
	QNetworkAccessManager m_network_manager;
};
VORTEX_NAMESPACE_END

#endif // !VDOWNLOADER_H
