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

#ifndef VORTEX_EXPORT_H
#define VORTEX_EXPORT_H

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(VORTEX_LIB)
#  define VORTEX_EXPORT Q_DECL_EXPORT
# else
#  define VORTEX_EXPORT Q_DECL_IMPORT
# endif
#else
# define VORTEX_EXPORT
#endif

#endif // !VORTEX_EXPORT_H
