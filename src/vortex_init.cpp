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

#include <Vortex/vortex_init.h>
#include <Vortex/vortex_global.h>

#include <QDebug>

#include <Layers/lstring.h>
#include <Layers/lcontroller.h>

namespace Layers {
    namespace Resources {
        extern void initResources_styles();
    }
}

void initialize_resources()
{
	// Initialize Qt resources
    Q_INIT_RESOURCE(roboto_font);
    Q_INIT_RESOURCE(themes);
    Q_INIT_RESOURCE(images);

    // Initialize Layers resources
    Layers::Resources::initResources_styles();
}

VORTEX_NAMESPACE_BEGIN

Initializer::Initializer()
{
    initialize_resources();

    lController.include_internal("/styles/vortex");
    qDebug() << "Vortex: Loaded Styles";
}

static Initializer vortex_initializer;

VORTEX_NAMESPACE_END
