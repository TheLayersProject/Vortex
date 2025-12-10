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

#ifndef VPARTICLES_H
#define VPARTICLES_H

#include <QObject>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include "vparticleoverlay.h"

VORTEX_NAMESPACE_BEGIN

struct VParticleDefinition
{
    QString name;
    QString image;
    int count = 50;
    float gravity = 40.0f;
    float drag = 0.1f;
    QString region = "top";
};

VORTEX_WIDGETS_EXPORT void sync_particle_effects(QWidget* widget);
VORTEX_WIDGETS_EXPORT void apply_particle_effects(
    QWidget* widget, Layers::LStyle* style);
VORTEX_WIDGETS_EXPORT void remove_particle_effects(QWidget* widget);
VORTEX_WIDGETS_EXPORT std::vector<VParticleDefinition> get_particle_definitions(Layers::LStyle* style);

class VORTEX_WIDGETS_EXPORT VParticleEventFilter : public QObject
{
    Q_OBJECT
public:
    static VParticleEventFilter& instance();
    
    void install();  // Call once at app startup
    
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
    
private:
    VParticleEventFilter() = default;
};

VORTEX_NAMESPACE_END

#endif // VPARTICLES_H