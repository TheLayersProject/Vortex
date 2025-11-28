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

#ifndef VAPPLICATION_H
#define VAPPLICATION_H

#include <vector>

#include <QApplication>
#include <QDir>
#include <QGradientStops>
#include <QSettings>
#include <QUuid>

#include <Layers/lattribute.h>
#include <Layers/ltheme.h>

#include "vortex_core_global.h"
#include "vortex_core_export.h"

VORTEX_NAMESPACE_BEGIN

VORTEX_CORE_EXPORT Layers::LTheme* activeTheme();

class VDownloader;
class VGitHubRepo;
class VMainWindow;

class VORTEX_CORE_EXPORT VApplication : public QApplication
{
	Q_OBJECT

signals:
	void active_theme_changed();

	void theme_added(Layers::LTheme* theme);

public:
	VApplication(int& argc, char** argv,
		const QString& name,
		const QUuid& uuid);

	~VApplication();

	Layers::LTheme* active_theme();

	void add_theme(std::unique_ptr<Layers::LTheme> theme);

	QString app_display_id() const;

	void apply_theme(Layers::LTheme* theme);

	bool toggle_style(const Layers::LString& style);

	void download_and_install_update();

	QFile* icon_file();

	void init();

	QString latest_version();

	void load_resource_theme(const QString& path);

	void load_themes(const QString& theme_directory);

	QString name();

	void reapply_theme();

	void set_github_repo(const QString& github_repo_url);

	void set_publisher(const QString& publisher);

	static void set_version(const QString& version);

	QSettings& settings();

	Layers::LTheme* theme(const QString& theme_id);

	bool update_available();

	static QString version();

private:
	void init_fonts();
	void init_active_theme();
	void init_themes();
	void init_styles();
	void init_latest_version();

	bool m_initialized{ false };

	VDownloader* m_downloader{ nullptr };

	QString m_github_api_repos_url_base{ "https://api.github.com/repos" };

	VGitHubRepo* m_github_repo{ nullptr };

	QFile* m_icon_file{ nullptr };

	QString m_latest_version;

	QString m_name;

	QString m_name_underscored;

	QString m_publisher;

	QSettings m_settings;

	QUuid m_uuid;
};
VORTEX_NAMESPACE_END

#define vApp (static_cast<Vortex::VApplication*>(qApp))

#endif // !VAPPLICATION_H
