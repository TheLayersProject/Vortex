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

#include <VortexWidgets/vparticleemitter.h>

#include <algorithm>
#include <QPainter>
#include <QRandomGenerator>

using namespace Vortex;

VParticleEmitter::VParticleEmitter(const QString& file_path, int count) :
  m_renderer{ new VSvgRenderer(file_path) },
  m_target_count{ count }
{
  // Set up particle update timer (60 FPS = ~16ms)
	m_update_timer = new QTimer(this);
	connect(m_update_timer, &QTimer::timeout, [this] { update(); });
	m_update_timer->start(16); // ~60 FPS

  // Set up staggered initialization timer
  m_init_timer = new QTimer(this);
  connect(m_init_timer, &QTimer::timeout, [this]() {
    // Emit a batch of particles
    for (int i = 0; i < m_init_batch_size && m_particles.size() < static_cast<size_t>(m_target_count); ++i)
    {
      _emit();
    }

    // Stop initialization when we reach target count
    if (m_particles.size() >= static_cast<size_t>(m_target_count))
    {
      m_init_timer->stop();
      m_initializing = false;
    }
  });

  m_elapsed_timer.start();
}

void VParticleEmitter::update()
{
  // Calculate delta time in seconds
  qint64 elapsed_ms = m_elapsed_timer.restart();
  float delta_time = elapsed_ms / 1000.0f;

  // Update particles with time-based physics
  for (auto& particle : m_particles)
  {
    // Apply gravity (acceleration)
    particle.vy += m_gravity * delta_time;

    // Apply drag (air resistance)
    float drag_factor = 1.0f - (m_drag * delta_time);
    particle.vx *= drag_factor;
    particle.vy *= drag_factor;

    // Update position based on velocity
    particle.x += particle.vx * delta_time;
    particle.y += particle.vy * delta_time;
  }

  // Remove particles that have fallen below the kill-line
  m_particles.erase(
    std::remove_if(m_particles.begin(), m_particles.end(),
      [this](const VParticle& particle) {
        return particle.y > m_kill_y;
      }),
    m_particles.end());

  // Maintain target particle count by emitting new particles
  // (but only after initial staggered emission is complete)
  if (!m_initializing)
  {
    while (m_particles.size() < static_cast<size_t>(m_target_count))
    {
      _emit();
    }
  }

  emit updated();
}

void VParticleEmitter::emit_particle()
{
  _emit();
}

void VParticleEmitter::start_staggered_initialization(int batch_size, int interval_ms)
{
  m_init_batch_size = batch_size;
  m_initializing = true;
  m_init_timer->start(interval_ms);
}

void VParticleEmitter::paint(QPainter* painter)
{
  if (painter)
  {
    for (auto& particle : m_particles)
    {
      painter->save();
      m_renderer->render(painter, QRectF(
          particle.x, particle.y, particle.w, particle.h));
      painter->restore();
    }
  }
}

void VParticleEmitter::_emit()
{
  VParticle particle;

  particle.x = m_emission_region.x() +
    QRandomGenerator::global()->bounded(m_emission_region.width());
  particle.y = m_emission_region.y() +
    QRandomGenerator::global()->bounded(m_emission_region.height());

  particle.vx = 0.0f;
  particle.vy = 0.0f;

  float particle_size =
    5.0f + QRandomGenerator::global()->bounded(15.0f);

  particle.w = particle_size;
  particle.h = particle_size;

  particle.life = 0.0f; // TODO: Set initial life

  m_particles.push_back(particle);
}