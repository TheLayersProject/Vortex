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

#include <VortexWidgets/vparticles.h>

#include <QApplication>

#include <Layers/lstyle.h>
#include <VortexCore/vapplication.h>
#include <VortexCore/vboxstyle.h>
#include <VortexCore/vfeature.h>

using namespace Vortex;
using Layers::LStyle;

namespace {
    class ParticleFeature : public VFeature
    {
    public:
        void initialize() override {
            VParticleEventFilter::instance().install();
        }
        const char* name() const override { return "Particles"; }
    };
    
    // Static instance - created before main()
    ParticleFeature g_particle_feature;
    
    // Registrar triggers during static initialization
    struct ParticleRegistrar {
        ParticleRegistrar() {
            VApplication::register_feature(&g_particle_feature);
        }
    } g_registrar;
}

 void Vortex::sync_particle_effects(QWidget* widget)
{
    LStyle* style = get_widget_lstyle(widget);
    if (!style)
        return;
    
    // Check the style AND any applied style definition for particles
    auto check_and_apply = [widget](LStyle* s) -> bool {
        if (s && s->has_extension("_particles"))
        {
            apply_particle_effects(widget, s);
            return true;
        }
        return false;
    };
    
    // First check if there's an applied style definition with particles
    // (This would be from a custom style)
    if (LStyle* style_def = style->style())
    {
        if (check_and_apply(style_def))
            return;
    }
    
    // Otherwise check the base style itself
    if (check_and_apply(style))
        check_and_apply(style);

    // No particles found in style - remove existing effects
    remove_particle_effects(widget);
}

void Vortex::apply_particle_effects(QWidget* widget, LStyle* style)
{
    // Look for particle definitions in the style
    // Using a dedicated "_particles" section for clarity
    
    // First, clean up any existing overlay
    if (auto* existing = widget->findChild<VParticleOverlay*>(
            QString(), Qt::FindDirectChildrenOnly))
    {
        existing->deleteLater();
    }
    
    // Check if this style defines particles
    // (You'd parse this from the JSON - see below for format)
    auto particle_defs = get_particle_definitions(style);
    
    if (particle_defs.empty())
        return;
    
    // Create overlay and add emitters
    auto* overlay = new VParticleOverlay(widget);
    overlay->setObjectName("_particle_overlay");
    
    for (const auto& def : particle_defs)
    {
        VParticleEmitter* emitter = overlay->add_emitter(def.image);
        //emitter->set_target_count(def.count);
        emitter->set_gravity(def.gravity);
        emitter->set_drag(def.drag);
    }
    
    overlay->show();
}

void Vortex::remove_particle_effects(QWidget* widget)
{
    if (auto* existing = widget->findChild<VParticleOverlay*>(
            QString(), Qt::FindDirectChildrenOnly))
    {
        existing->deleteLater();
    }
}

std::vector<VParticleDefinition> Vortex::get_particle_definitions(LStyle* style)
{
    std::vector<VParticleDefinition> defs;
    
    if (!style || !style->has_extension("_particles"))
        return defs;
    
    json particles = style->extension("_particles");
    
    // Handle array format: "_particles": [{ ... }, { ... }]
    if (particles.is_array())
    {
        for (const auto& p : particles)
        {
            VParticleDefinition def;
            
            if (p.contains("name"))
                def.name = QString::fromStdString(p["name"].get<std::string>());
            if (p.contains("image"))
                def.image = QString::fromStdString(p["image"].get<std::string>());
            if (p.contains("count"))
                def.count = p["count"].get<int>();
            if (p.contains("gravity"))
                def.gravity = p["gravity"].get<float>();
            if (p.contains("drag"))
                def.drag = p["drag"].get<float>();
            if (p.contains("region"))
                def.region = QString::fromStdString(p["region"].get<std::string>());
            
            defs.push_back(def);
        }
    }
    // Handle simple format: "_particles": { "Snow": "/images/snow.svg" }
    else if (particles.is_object())
    {
        for (const auto& [name, val] : particles.items())
        {
            VParticleDefinition def;
            def.name = QString::fromStdString(name);
            
            if (val.is_string())
                def.image = QString::fromStdString(val.get<std::string>());
            else if (val.is_object())
            {
                if (val.contains("image"))
                    def.image = QString::fromStdString(val["image"].get<std::string>());
                if (val.contains("count"))
                    def.count = val["count"].get<int>();
                if (val.contains("gravity"))
                    def.gravity = val["gravity"].get<float>();
                if (val.contains("drag"))
                    def.drag = val["drag"].get<float>();
                if (val.contains("region"))
                    def.region = QString::fromStdString(val["region"].get<std::string>());
            }
            
            defs.push_back(def);
        }
    }
    
    return defs;
}

VParticleEventFilter& VParticleEventFilter::instance()
{
    static VParticleEventFilter instance;
    return instance;
}

void VParticleEventFilter::install()
{
    qApp->installEventFilter(this);
}

bool VParticleEventFilter::eventFilter(QObject* watched, QEvent* event)
{
    if (event->type() == VStyleAppliedEvent::EventType)
    {
        if (QWidget* widget = qobject_cast<QWidget*>(watched))
        {
            Vortex::sync_particle_effects(widget);
        }
    }
    return QObject::eventFilter(watched, event);
}
