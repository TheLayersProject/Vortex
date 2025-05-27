/*
 * Copyright (C) 2025 The Layers Project
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

#include <Vortex/vapplication.h>

#include <QDirIterator>
#include <QFontDatabase>
#include <QGradientStops>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QProcess>
#include <QWidget>
#include <Layers/lalgorithms.h>
#include <Layers/lcontroller.h>
#include <Layers/lpaths.h>
#include <Layers/lstyle.h>
#include <QLayers/qllogger.h>
#include <Vortex/vdownloader.h>
#include <Vortex/vgithubrepo.h>

using Layers::LAttribute;
using Layers::LString;
using Layers::LStyle;
using Layers::LStyleList;
using Layers::LTheme;
using Layers::LDefinable;
using QLayers::QLDefinable;
using Vortex::VApplication;

LTheme* Vortex::activeTheme()
{
	if (vApp)
		return vApp->active_theme();
	else
		return nullptr;
}

VApplication::VApplication(
	int& argc, char** argv,
	const QString& name,
	const QUuid& uuid) :
	m_name{ name },
	m_uuid{ uuid },
	m_settings{ QSettings(name, name) },
	m_downloader{ new VDownloader(this) },
	QApplication(argc, argv) {}

VApplication::~VApplication()
{
	if (m_github_repo)
		delete m_github_repo;
}

QString VApplication::app_display_id() const
{
	return m_name + " (" + m_publisher + ")";
}

void VApplication::apply_theme(LTheme* theme)
{
	if (lController.set_active_theme(theme))
	{
		emit active_theme_changed();

		m_settings.setValue(
			"themes/active_theme",
			QString::fromStdString(theme->display_id().c_str()));
	}
}

bool VApplication::toggle_style(const Layers::LString& style_name)
{
	bool style_applied = lController.toggle_style(style_name);

	QStringList active_style_IDs;

	for (LStyle* style : lController.active_styles())
	{
		active_style_IDs.push_back(style->object_name().c_str());
	}

	m_settings.setValue("styles/active_styles", active_style_IDs);

	return style_applied;
}

LTheme* VApplication::active_theme()
{
	return lController.active_theme();
}

void VApplication::add_theme(std::unique_ptr<LTheme> theme)
{
	LTheme* theme_ptr = theme.get();

	lController.add_theme(std::move(theme));

	emit theme_added(theme_ptr);
}

QFile* VApplication::icon_file()
{
	return m_icon_file;
}

void VApplication::init()
{
	if (m_initialized) return;
	
	qRegisterMetaType<QGradientStops>("QGradientStops");

	Layers::set_log_function(&QLayers::QLLog_Layers);

	init_fonts();
	init_latest_version();
	setEffectEnabled(Qt::UI_AnimateCombo, false);

	QStringList name_parts = m_name.split(' ', Qt::SkipEmptyParts);
	for (int i = 0; i < name_parts.size(); i++)
		name_parts[i].replace(0, 1, name_parts[i][0].toLower());
	m_name_underscored = name_parts.join("_");

	init_themes();
	init_styles();
	init_active_theme();

	m_initialized = true;
}

QString VApplication::latest_version()
{
	return m_latest_version;
}

void VApplication::load_resource_theme(const QString& path)
{
	// Open the resource file
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		std::cerr << "Failed to open resource file: " <<
			path.toStdString() << std::endl;
	}

	// Read file contents
	QTextStream in(&file);
	QString contents = in.readAll();
	file.close();
	
	add_theme(lController.load_theme(
		Layers::remove_whitespace(contents.toStdString())));
}

void VApplication::load_themes(const QString& theme_directory)
{
	lController.load_themes(theme_directory.toStdString());

	QStringList theme_directories = m_settings.value("themes/directories").toStringList();
	theme_directories.append(theme_directory);
	m_settings.setValue("themes/directories", theme_directories);
}

bool VApplication::update_available()
{
	if (!m_latest_version.isEmpty() && !version().isEmpty())
		return m_latest_version != version();
	else
		return false;
}

QString VApplication::version()
{
	return applicationVersion();
}

void VApplication::download_and_install_update()
{
	QUrl repo_releases_json_download_url(m_github_api_repos_url_base + "/" + m_github_repo->to_string() + "/releases");

	QNetworkReply* repo_releases_json_download = m_downloader->download(repo_releases_json_download_url);

	QEventLoop loop;
	connect(repo_releases_json_download, &QNetworkReply::finished, &loop, &QEventLoop::quit);
	loop.exec();

	if (repo_releases_json_download->error() == QNetworkReply::NoError)
	{
		QJsonArray repo_releases_json_array = QJsonDocument::fromJson(repo_releases_json_download->readAll()).array();

		QJsonArray release_assets_array = repo_releases_json_array.first().toObject()["assets"].toArray();

		for (QJsonValueRef release_asset : release_assets_array)
		{
			QString release_asset_name = release_asset.toObject()["name"].toString();

			if (release_asset_name.endsWith(".exe") || release_asset_name.endsWith(".msi"))
			{
				QDir temp_dir = Layers::local_app_data_path() / "Temp\\";

				QUrl latest_version_download_url = QUrl(release_asset.toObject()["browser_download_url"].toString());

				if (!QFile::exists(latest_version_download_url.fileName()))
				{
					QNetworkReply* update_download = m_downloader->download(latest_version_download_url, temp_dir);

					QEventLoop loop;
					connect(update_download, SIGNAL(finished()), &loop, SLOT(quit()));
					loop.exec();
				}

				QStringList args = { "/SILENT" };

				QProcess update_process;
				update_process.startDetached(temp_dir.filePath(latest_version_download_url.fileName()), args);
			}
		}
	}
}

QString VApplication::name()
{
	return m_name;
}

void VApplication::reapply_theme()
{
	apply_theme(lController.active_theme());
}

void VApplication::set_github_repo(const QString& github_repo_url)
{
	if (m_github_repo)
		delete m_github_repo;

	m_github_repo = new VGitHubRepo(github_repo_url);
}

void VApplication::set_publisher(const QString& publisher)
{
	m_publisher = publisher;
}

void VApplication::set_version(const QString& version)
{
	setApplicationVersion(version);
}

QSettings& VApplication::settings()
{
	return m_settings;
}

LTheme* VApplication::theme(const QString& theme_id)
{
	return lController.theme(
		LString(theme_id.toStdString().c_str()));
}

void VApplication::init_fonts()
{
	QDirIterator fonts_iterator(
		":/fonts",
		{ "*.ttf", "*.otf" },
		QDir::Files, QDirIterator::Subdirectories);

	while (fonts_iterator.hasNext())
		QFontDatabase::addApplicationFont(fonts_iterator.next());

	QFont font("Roboto", 12, QFont::Normal);
	font.setStyleStrategy(QFont::PreferAntialias);
	setFont(font);
}

void VApplication::init_active_theme()
{
	LString active_theme_id =
		LString(m_settings.value("themes/active_theme").toString().toStdString().c_str());

	if (lController.themes().count(active_theme_id) > 0)
		apply_theme(lController.theme(active_theme_id));
	else
		apply_theme(lController.theme("Dark"));
}

void VApplication::init_themes()
{
	// Load default light and dark themes
	load_resource_theme(":/themes/dark.json");
	load_resource_theme(":/themes/light.json");

	// Load themes from user directories (if present)
	QVariant _theme_directories = m_settings.value("themes/directories");

	if (_theme_directories.isValid())
	{
		QStringList theme_directories = _theme_directories.toStringList();
		for (const QString& theme_directory : theme_directories)
		{
			// Process each theme directory
			qDebug() << "Vortex: VApplication: Loading themes from:" << theme_directory;

			lController.load_themes(theme_directory.toStdString());
		}
	}
	else
	{
		qDebug() << "Vortex: VApplication: No theme directories found.";
	}
}

void VApplication::init_styles()
{
	QVariant _active_style_IDs = m_settings.value("styles/active_styles");

	if (_active_style_IDs.isValid())
	{
		QStringList active_style_IDs = _active_style_IDs.toStringList();
		for (const QString& active_style_ID : active_style_IDs)
		{
			// Process each enabled style
			qDebug() << "Active style:" << active_style_ID;

			lController.toggle_style(active_style_ID.toStdString().c_str());
		}
	}
	else
	{
		qDebug() << "No styles enabled.";
	}
}

void VApplication::init_latest_version()
{
	if (m_github_repo)
	{
		QUrl url(m_github_api_repos_url_base + "/" + m_github_repo->to_string() + "/tags");

		QNetworkReply* download = m_downloader->download(url);

		QEventLoop loop;
		connect(download, &QNetworkReply::finished, &loop, &QEventLoop::quit);
		loop.exec();

		if (download->error() == QNetworkReply::NoError)
		{
			QJsonDocument json_doc =
				QJsonDocument::fromJson(download->readAll());

			if (!json_doc.array().isEmpty())
				m_latest_version =
				json_doc.array().first().toObject()["name"].toString();
		}
	}
}
