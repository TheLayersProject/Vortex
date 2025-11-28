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

#ifndef VSVGRENDERER_H
#define VSVGRENDERER_H

//#include <QColor>
#include <QSvgRenderer>
//#include <QWebEngineView>
#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VSvgRenderer : public QSvgRenderer
{
	Q_OBJECT

public:
	VSvgRenderer(const QString& file_path, QObject* parent = nullptr);

	//Layers::LAttribute* color() const;

	void exclude_from_theme(const QString& path_id);

protected:
	bool event(QEvent* e) override;

private:
	void init_svg_elements_list();

	void parse_exclusion_comments();

	void rebuild_svg_str();

	void update();

	// Layers::LAttribute* m_color{
	// 	lMakeDefinableAttribute(this, "Color", "#000000") };

	QStringList m_svg_elements;

	QStringList m_excluded_paths;

	QString m_svg_str;
};

//class VORTEX_WIDGETS_EXPORT VSvgRenderer : public QWebEngineView, public QLDefinable
//{
//    Q_OBJECT
//
//public:
//    VSvgRenderer(const QString& file_path, QObject* parent = nullptr);
//    ~VSvgRenderer() = default;
//
//    Layers::LAttribute* color() const;
//    void exclude_from_theme(const QString& path_id);
//    QSize defaultSize() const { return m_default_size; }
//
//signals:
//    void repaintNeeded();
//
//private:
//    void update();
//    void init_svg_elements_list();
//    void parse_exclusion_comments();
//    void rebuild_svg_content();
//    //void updateSvgContent();
//
//    QString m_svg_str;
//    QStringList m_excluded_paths;
//    QStringList m_svg_elements;
//    QSize m_default_size;
//    //Layers::LAttribute* m_color;
//
//    Layers::LAttribute* m_color{
//        lMakeDefinableAttribute(this, "Color", "#000000") };
//};

VORTEX_NAMESPACE_END

#endif // VSVGRENDERER_H
