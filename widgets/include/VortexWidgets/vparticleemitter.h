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

#ifndef VPARTICLIZER_H
#define VPARTICLIZER_H

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include <QTimer>
#include <QElapsedTimer>

#include "vsvgrenderer.h"

VORTEX_NAMESPACE_BEGIN

struct VParticle
{
  float x;
  float y;
  float vx;  // velocity x (pixels per second)
  float vy;  // velocity y (pixels per second)
  float w;
  float h;
  float life;
};

class VORTEX_WIDGETS_EXPORT VParticleEmitter : public QObject
{
  Q_OBJECT

signals:
  void updated();

public:
	VParticleEmitter(const QString& file_path, int count = 100);

  void paint(QPainter* painter);
  void update();

  void set_gravity(float gravity) { m_gravity = gravity; }
  float gravity() const { return m_gravity; }

  void set_drag(float drag) { m_drag = drag; }
  float drag() const { return m_drag; }

  void set_emission_region(const QRectF& region) { m_emission_region = region; }

  void set_kill_y(float y) { m_kill_y = y; }
  float kill_y() const { return m_kill_y; }

  void start_staggered_initialization(int batch_size = 3, int interval_ms = 50);

  void emit_particle();

private:
  void _emit();

  VSvgRenderer* m_renderer{ nullptr };

  int m_target_count;

  std::vector<VParticle> m_particles;

  QTimer* m_update_timer{ nullptr };
  QTimer* m_init_timer{ nullptr };
  QElapsedTimer m_elapsed_timer;
  
  float m_gravity{ 200.0f }; // pixels per second squared (approx. 9.8 m/s^2 at 100 pixels per meter)
  float m_drag{ 0.5f }; // drag coefficient (0 = no drag, higher = more drag)

  QRectF m_emission_region{ 0, 0, 100, 100 };
  float m_kill_y{ 10000.0f }; // Particles are removed when they fall below this y value

  int m_init_batch_size{ 3 }; // Number of particles to emit per initialization batch
  bool m_initializing{ false }; // Whether we're currently in staggered initialization
};
VORTEX_NAMESPACE_END

#endif // !VPARTICLIZER_H