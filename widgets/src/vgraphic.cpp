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

#include <VortexWidgets/vgraphic.h>

using Vortex::VGraphic;
using Vortex::VImageSequence;
using Vortex::VSvgRenderer;

//VGraphic::VGraphic(const QString& file_path, QSize size)
//{
//	if (file_path.endsWith(".png") || file_path.endsWith(".jpg") ||
//		file_path.endsWith(".jpeg") || file_path.endsWith(".bmp") ||
//		file_path.endsWith(".gif"))
//	{
//		m_image = new QImage(file_path);
//	}
//	else if (file_path.endsWith(".svg"))
//	{
//		m_svg_renderer = new VSvgRenderer(file_path);
//		m_svg_renderer->setObjectName("Svg");
//		// Since QWebEngineView is a widget, it needs a parent
//		// We'll set it to nullptr initially and let VLabel handle parenting
//		//m_svg_renderer->hide(); // Hide until properly parented
//	}
//	else if (file_path.endsWith(".imgseq"))
//	{
//		m_image_sequence = new VImageSequence(QFile(file_path));
//	}
//
//	if (size.isValid())
//	{
//		m_size = size;
//
//		if (m_svg_renderer)
//		{
//			m_svg_renderer->setFixedSize(size);
//		}
//	}
//	else if (m_svg_renderer)
//		m_size = m_svg_renderer->defaultSize();
//	else if (m_image)
//		m_size = m_image->size();
//	else if (m_image_sequence)
//		if (QImage* first_frame = m_image_sequence->frame(0))
//			m_size = first_frame->size();
//}

VGraphic::VGraphic(const QString& file_path, QSize size)
{
	if (file_path.endsWith(".png") || file_path.endsWith(".jpg") ||
		file_path.endsWith(".jpeg") || file_path.endsWith(".bmp") ||
		file_path.endsWith(".gif"))
	{
		m_image = new QImage(file_path);
	}
	else if (file_path.endsWith(".svg"))
	{
		m_svg_renderer = new VSvgRenderer(file_path);
		m_svg_renderer->setObjectName("Svg");
	}
	else if (file_path.endsWith(".imgseq"))
	{
		m_image_sequence = new VImageSequence(QFile(file_path));
	}

	if (size.isValid())
		m_size = size;
	else if (m_svg_renderer)
		m_size = m_svg_renderer->defaultSize();
	else if (m_image)
		m_size = m_image->size();
	else if (m_image_sequence)
		if (QImage* first_frame = m_image_sequence->frame(0))
			m_size = first_frame->size();
}

VGraphic::VGraphic(const QImage& image) :
	m_image{ new QImage(image) }
{
	m_size = m_image->size();
}

VGraphic::~VGraphic()
{
	//if (m_svg_renderer)
	//	delete m_svg_renderer;
	if (m_image)
		delete m_image;
	else if (m_image_sequence)
		delete m_image_sequence;
}

QImage* VGraphic::image() const
{
	return m_image;
}

VImageSequence* VGraphic::image_sequence() const
{
	return m_image_sequence;
}

void VGraphic::set_width(int desired_width)
{
	QSize original_size;
	if (m_svg_renderer)
		original_size = m_svg_renderer->defaultSize();
	else if (m_image)
		original_size = m_image->size();
	else if (m_image_sequence)
		if (QImage* first_frame = m_image_sequence->frame(0))
			original_size = first_frame->size();
		else
			return;

	double aspect_ratio = (double)original_size.height() / original_size.width();
	m_size = QSize(desired_width, qRound(desired_width * aspect_ratio));

	//if (m_image)
	//{
	//	m_size.setWidth(desired_width);
	//	m_image->scaled(m_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	//}
	//else if (m_svg_renderer)
	//{
	//	m_svg_renderer->set_view_box(QRectF(0, 0, desired_width, m_size.height()));
	//}
	//else if (m_image_sequence)
	//{
	//	m_size.setWidth(desired_width);
	//	for (int i = 0; i < m_image_sequence->size(); i++)
	//		m_image_sequence->frame(i)->scaled(m_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	//}
}

QSize VGraphic::size() const
{
	return m_size;
}

VSvgRenderer* VGraphic::svg_renderer() const
{
	return m_svg_renderer;
}
