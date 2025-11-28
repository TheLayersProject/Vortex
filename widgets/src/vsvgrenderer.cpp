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

#include <VortexWidgets/vsvgrenderer.h>

#include <QFile>
#include <QRegularExpression>
#include <QTextStream>
#include <Layers/lstring.h>
#include <Layers/lstyle.h>
#include <VortexCore/vboxstyle.h>

using Layers::LAttribute;
using Layers::LString;

using Vortex::VSvgRenderer;

//VSvgRenderer::VSvgRenderer(const QString& file_path, QObject* parent) :
//    QWebEngineView(qobject_cast<QWidget*>(parent))
//{
//    // Set transparent background
//    setStyleSheet("QWebEngineView { background: transparent; }");
//    page()->setBackgroundColor(Qt::transparent);
//
//    // Load SVG file
//    QFile file(file_path);
//    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        QTextStream in(&file);
//        m_svg_str = in.readAll();
//        file.close();
//    }
//
//    init_svg_elements_list();
//    parse_exclusion_comments();
//
//    // Extract default size from SVG more carefully
//    QRegularExpression widthRegex("<svg[^>]*\\s+width=\"([^\"]+)\"");
//    QRegularExpression heightRegex("<svg[^>]*\\s+height=\"([^\"]+)\"");
//
//    auto widthMatch = widthRegex.match(m_svg_str);
//    auto heightMatch = heightRegex.match(m_svg_str);
//
//    int width = 0, height = 0;
//
//    if (widthMatch.hasMatch()) {
//        QString widthStr = widthMatch.captured(1);
//        // Remove any units (px, pt, etc) and keep only numbers
//        widthStr.remove(QRegularExpression("[^0-9.]"));
//        width = widthStr.toInt();
//    }
//
//    if (heightMatch.hasMatch()) {
//        QString heightStr = heightMatch.captured(1);
//        heightStr.remove(QRegularExpression("[^0-9.]"));
//        height = heightStr.toInt();
//    }
//
//    // If we couldn't get the size from explicit attributes, try viewBox
//    if (width == 0 || height == 0) {
//        QRegularExpression viewBoxRegex("<svg[^>]*\\s+viewBox=\"([^\"]+)\"");
//        auto viewBoxMatch = viewBoxRegex.match(m_svg_str);
//        if (viewBoxMatch.hasMatch()) {
//            QString viewBox = viewBoxMatch.captured(1);
//            QStringList values = viewBox.split(" ", Qt::SkipEmptyParts);
//            if (values.size() == 4) {
//                if (width == 0) width = values[2].toInt();
//                if (height == 0) height = values[3].toInt();
//            }
//        }
//    }
//
//    // Set a minimum default size if we still couldn't get valid dimensions
//    if (width <= 0) width = 10;
//    if (height <= 0) height = 10;
//
//    m_default_size = QSize(width, height);
//    setFixedSize(m_default_size);
//
//    setContent(m_svg_str.toUtf8(), "image/svg+xml");
//}
//
//LAttribute* VSvgRenderer::color() const
//{
//    return m_color;
//}
//
//void VSvgRenderer::exclude_from_theme(const QString& path_id)
//{
//    m_excluded_paths.append(path_id);
//}
//
//void VSvgRenderer::update()
//{
//    for (int i = 0; i < m_svg_elements.size(); i++) {
//        if ((m_svg_elements[i].startsWith("<path") || m_svg_elements[i].startsWith("<circle")) &&
//            (m_svg_elements[i].contains("id=") && m_svg_elements[i].contains("fill="))) {
//
//            bool skip = false;
//            for (const QString& path_id : m_excluded_paths)
//                if (m_svg_elements[i].contains(path_id))
//                    skip = true;
//            if (skip)
//                continue;
//
//            QString color_name = QString::fromStdString(
//                m_color->as<LString>(state_combo()).c_str());
//
//            m_svg_elements[i].replace(
//                m_svg_elements[i].indexOf("fill=") + 6, 7, color_name);
//        }
//    }
//
//    rebuild_svg_content();
//
//    //updateSvgContent();
//    //emit repaintNeeded();
//}
//
//void VSvgRenderer::init_svg_elements_list()
//{
//    QString temp_svg_str = QString(m_svg_str);
//
//    while (temp_svg_str.contains("<")) {
//        int tag_open_index = temp_svg_str.indexOf("<");
//        int tag_close_index = temp_svg_str.indexOf(">");
//        int tag_size = tag_close_index - tag_open_index + 1;
//
//        m_svg_elements.append(temp_svg_str.mid(tag_open_index, tag_size));
//        temp_svg_str.remove(tag_open_index, tag_size);
//    }
//}
//
//void VSvgRenderer::parse_exclusion_comments()
//{
//    QRegularExpression exclusion_regex(
//        R"(<!--\s*exclude\s*=\s*\"([^\"]+)\"\s*-->)"
//    );
//    QRegularExpressionMatchIterator matches = exclusion_regex.globalMatch(m_svg_str);
//
//    while (matches.hasNext())
//    {
//        QRegularExpressionMatch match = matches.next();
//        QString id = match.captured(1).trimmed();
//        m_excluded_paths.append(id);
//    }
//}
//
//void VSvgRenderer::rebuild_svg_content()
//{
//    QString new_svg_str = "";
//    for (const QString& tag : m_svg_elements) {
//        new_svg_str += tag;
//    }
//    m_svg_str = new_svg_str;
//
//	setContent(m_svg_str.toUtf8(), "image/svg+xml");
//}

//void VSvgRenderer::updateSvgContent()
//{
//    QString html = QString("<html><body style='background-color: transparent; margin: 0;'>"
//        "<div style='background-color: transparent;'>%1</div>"
//        "</body></html>").arg(m_svg_str);
//    setHtml(html);
//}

VSvgRenderer::VSvgRenderer(const QString& file_path, QObject* parent) :
	QSvgRenderer(parent)
{
	QFile file(file_path);

	if (file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&file);
		m_svg_str = in.readAll();
		file.close();
	}

	init_svg_elements_list();
	parse_exclusion_comments();

	load(m_svg_str.toUtf8());
}

// LAttribute* VSvgRenderer::color() const
// {
// 	return m_color;
// }

void VSvgRenderer::exclude_from_theme(const QString& path_id)
{
	m_excluded_paths.append(path_id);
}

void VSvgRenderer::rebuild_svg_str()
{
	QString new_svg_str = "";

	for (const QString& tag : m_svg_elements)
	{
		new_svg_str += tag;
	}

	m_svg_str = new_svg_str;
}

void VSvgRenderer::update()
{
	if (Layers::LStyle* style = Vortex::get_widget_lstyle(this))
	{
		Layers::LStringList states = Vortex::get_state_combo(this);

		QString color_name = QString::fromStdString(
			style->find_attribute("Color")->as<LString>(
				states).c_str());

		for (int i = 0; i < m_svg_elements.size(); i++)
		{
			/*
				TODO: Handle all valid element types that can have an 'id' and a 'fill'
			*/
			if ((m_svg_elements[i].startsWith("<path") ||
				m_svg_elements[i].startsWith("<circle") ||
				m_svg_elements[i].startsWith("<rect")) &&
				(m_svg_elements[i].contains("id=") && m_svg_elements[i].contains("fill=")))
			{
				bool skip = false;
				for (const QString& path_id : m_excluded_paths)
					if (m_svg_elements[i].contains(path_id))
						skip = true;
				if (skip)
					continue;

				// QString color_name =
				// 	QString::fromStdString(
				// 		m_color->as<LString>(state_combo()).c_str());

				m_svg_elements[i].replace(
					m_svg_elements[i].indexOf("fill=") + 6, 7, color_name);
			}
		}
	}

	rebuild_svg_str();

	load(m_svg_str.toUtf8());
}

bool VSvgRenderer::event(QEvent *e)
{
	if (e->type() == Vortex::VStyleAppliedEvent::EventType)
	{
        update();

        return true;
    }
    
    return QSvgRenderer::event(e);
}

void VSvgRenderer::init_svg_elements_list()
{
	QString temp_svg_str = QString(m_svg_str);

	while (temp_svg_str.contains("<"))
	{
		int tag_open_index = temp_svg_str.indexOf("<");
		int tag_close_index = temp_svg_str.indexOf(">");
		int tag_size = tag_close_index - tag_open_index + 1;

		m_svg_elements.append(temp_svg_str.mid(tag_open_index, tag_size));

		temp_svg_str.remove(tag_open_index, tag_size);
	}
}

void VSvgRenderer::parse_exclusion_comments()
{
	// Look for comments in the format: <!-- exclude="element_id" -->
	QRegularExpression exclusion_regex(
		R"(<!--\s*exclude\s*=\s*\"([^\"]+)\"\s*-->)"
	);
	QRegularExpressionMatchIterator matches = exclusion_regex.globalMatch(m_svg_str);

	while (matches.hasNext())
	{
		QRegularExpressionMatch match = matches.next();
		QString id = match.captured(1).trimmed();
		m_excluded_paths.append(id);
	}
}
