/*
 * Copyright (C) 2025 Huntr Software LLC
 *
 * This file is part of Layers.
 *
 * Layers is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Layers is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Layers. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef VSYSTEM_H
#define VSYSTEM_H

#include <string>

#ifdef _WIN32
#include <windows.h>
#include <Lmcons.h>
#elif defined(__APPLE__)
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#endif

#include "vortex_core_global.h"
#include "vortex_core_export.h"

VORTEX_NAMESPACE_BEGIN

VORTEX_CORE_EXPORT inline std::string get_current_username()
{
#ifdef _WIN32
    WCHAR buffer[UNLEN + 1];
    DWORD buffer_len = UNLEN + 1;

    if (GetUserNameW(buffer, &buffer_len))
    {
        std::wstring wstr(buffer);
        return std::string(wstr.begin(), wstr.end());
    }
    else
    {
        return std::string("unknown");
    }

#elif defined(__APPLE__)
    // macOS and Unix-like implementation
    const char* username = getlogin(); // Try to get the username using getlogin()
    if (username)
    {
        return std::string(username);
    }
    else
    {
        // Fallback to using getpwuid() if getlogin() fails
        struct passwd* pw;
        uid_t uid = geteuid();

        if ((pw = getpwuid(uid)) != NULL)
        {
            return std::string(pw->pw_name);
        }
        else
        {
            return std::string("unknown");
        }
    }
#endif
}

VORTEX_NAMESPACE_END

#endif // !QLSYSTEM_H
