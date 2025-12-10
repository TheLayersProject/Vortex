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

#ifndef VPARTICLEOVERLAY_H
#define VPARTICLEOVERLAY_H

#include <QWidget>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include "vparticleemitter.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VParticleOverlay : public QWidget
{
    Q_OBJECT

public:
    explicit VParticleOverlay(QWidget* parent);
    
    VParticleEmitter* add_emitter(const QString& image_path);
    void remove_emitter(VParticleEmitter* emitter);
    void clear_emitters();
    
    const std::vector<std::unique_ptr<VParticleEmitter>>& emitters() const;

protected:
    void paintEvent(QPaintEvent* e) override;
    bool eventFilter(QObject* watched, QEvent* event) override;

private:
    std::vector<std::unique_ptr<VParticleEmitter>> m_emitters;
};
VORTEX_NAMESPACE_END

#endif // VPARTICLEOVERLAY_H