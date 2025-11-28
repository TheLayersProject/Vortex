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

#include <VortexCore/vortex_core_init.h>
#include <VortexCore/vortex_core_global.h>

#include <QDebug>

#include <Layers/lstring.h>
#include <Layers/lcontroller.h>

VORTEX_NAMESPACE_BEGIN

Initializer_CORE::Initializer_CORE()
{
    // Initialize Qt resources
    Q_INIT_RESOURCE(roboto_font);
    Q_INIT_RESOURCE(themes);
    Q_INIT_RESOURCE(images);
}

static Initializer_CORE vortex_core_initializer;

VORTEX_NAMESPACE_END
