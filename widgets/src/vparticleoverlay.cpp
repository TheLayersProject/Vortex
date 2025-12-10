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

 #include <VortexWidgets/vparticleoverlay.h>

 #include <QEvent>
 #include <QPainter>

 using namespace Vortex;

VParticleOverlay::VParticleOverlay(QWidget* parent) : QWidget(parent)
{
    // Transparent, non-interactive overlay
    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    
    // Match parent size and keep below other widgets
    if (parent)
    {
        parent->installEventFilter(this);
        setGeometry(parent->rect());
        lower(); 
    }
}

VParticleEmitter* VParticleOverlay::add_emitter(const QString& image_path)
{
    auto emitter = std::make_unique<VParticleEmitter>(image_path);
    VParticleEmitter* ptr = emitter.get();
    
    // Configure emission region based on parent
    if (parentWidget())
    {
        emitter->set_emission_region(
            QRectF(0, -100, parentWidget()->width(), 100));
        emitter->set_kill_y(parentWidget()->height() + 50);
    }
    
    connect(ptr, &VParticleEmitter::updated, this, 
        QOverload<>::of(&QWidget::update));
    
    m_emitters.push_back(std::move(emitter));
    
    // Start staggered emission
    ptr->start_staggered_initialization(1, 120);
    
    return ptr;
}

void VParticleOverlay::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    for (auto& emitter : m_emitters)
        emitter->paint(&painter);
}

bool VParticleOverlay::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == parentWidget() && event->type() == QEvent::Resize)
    {
        setGeometry(parentWidget()->rect());
        
        // Update all emitter regions
        for (auto& emitter : m_emitters)
        {
            emitter->set_emission_region(
                QRectF(0, -100, width(), 100));
            emitter->set_kill_y(height() + 50);
        }
    }
    return QWidget::eventFilter(watched, event);
}
