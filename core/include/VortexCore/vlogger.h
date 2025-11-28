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

#ifndef VLOGGER_H
#define VLOGGER_H

#include "vortex_core_global.h"
#include "vortex_core_export.h"

#include <QDebug>
#include <Layers/llogger.h>

VORTEX_NAMESPACE_BEGIN
VORTEX_CORE_EXPORT void VLog_Layers(const Layers::LString& msg);
VORTEX_NAMESPACE_END

#endif // VLOGGER_H