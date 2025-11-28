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

#ifndef VGRAPHIC_H
#define VGRAPHIC_H

#include <QImage>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <VortexCore/vimagesequence.h>
#include "vsvgrenderer.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VGraphic
{
public:
	VGraphic(const QString& file_path, QSize size = QSize());

	VGraphic(const QImage& image);

	~VGraphic();

	QImage* image() const;

	VImageSequence* image_sequence() const;

	void set_width(int desired_width);

	QSize size() const;

	VSvgRenderer* svg_renderer() const;

private:
	QSize m_size;

	VImageSequence* m_image_sequence{ nullptr };

	QImage* m_image{ nullptr };

	VSvgRenderer* m_svg_renderer{ nullptr };
};
VORTEX_NAMESPACE_END

#endif // VGRAPHIC_H
