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

#ifndef VBOXSTYLE_H
#define VBOXSTYLE_H

#include "vortex_core_global.h"
#include "vortex_core_export.h"

#include <QCommonStyle>
#include <QEvent>
#include <QPainter>
#include <QStyleOption>
#include <QPointer>

#include <Layers/lstring.h>

//#include "vcalculate.h"
//#include "vpaint.h"
#include "vstatepool.h"

namespace Layers {
    class LStyle;
}

VORTEX_NAMESPACE_BEGIN

// Structure to hold corner radii
struct VBoxCornerRadii {
    double top_left = 0.0;
    double top_right = 0.0;
    double bottom_left = 0.0;
    double bottom_right = 0.0;
    
    VBoxCornerRadii() = default;
    VBoxCornerRadii(double all) : 
        top_left(all), top_right(all), 
        bottom_left(all), bottom_right(all) {}
    VBoxCornerRadii(double tl, double tr, double bl, double br) :
        top_left(tl), top_right(tr), 
        bottom_left(bl), bottom_right(br) {}
};

// Structure to hold margins
struct VBoxMargins {
    double left = 0.0;
    double top = 0.0;
    double right = 0.0;
    double bottom = 0.0;
    
    VBoxMargins() = default;
    VBoxMargins(double all) : 
        left(all), top(all), right(all), bottom(all) {}
    VBoxMargins(double l, double t, double r, double b) :
        left(l), top(t), right(r), bottom(b) {}
};

// States helper functions
VORTEX_CORE_EXPORT void init_state_pools(QObject* obj);
VORTEX_CORE_EXPORT void add_state_pool(
    QObject* obj, VStatePool* state_pool, bool include_children = true);
VORTEX_CORE_EXPORT Layers::LStringList get_state_combo(const QObject* obj);
VORTEX_CORE_EXPORT void share_state_pools(const QObject* parent, QObject* child);

// Helper functions
VORTEX_CORE_EXPORT void debug_lstyle_structure(const Layers::LStyle* style, int indent = 0);
VORTEX_CORE_EXPORT void debug_widget_style(const QWidget* widget);
VORTEX_CORE_EXPORT void update_all_styled_widgets(QWidget* root = nullptr);
VORTEX_CORE_EXPORT QString get_widget_style_path(const QWidget* widget);
VORTEX_CORE_EXPORT Layers::LStyle* get_widget_lstyle(const QObject* obj);

// Main functions to apply Layers styles to widgets
//VORTEX_CORE_EXPORT void apply_layers_style_recursive(QWidget* root);
VORTEX_CORE_EXPORT void apply_layers_style_from_parent(QWidget* widget);
VORTEX_CORE_EXPORT void apply_layers_style(QObject* obj, Layers::LStyle* style);
VORTEX_CORE_EXPORT void apply_layers_style_by_path(QWidget* widget, const QString& style_path);
VORTEX_CORE_EXPORT void apply_layers_style_auto(QWidget* widget);
VORTEX_CORE_EXPORT void refresh_widget_style(QWidget* widget);

class VORTEX_CORE_EXPORT VStyleAppliedEvent : public QEvent
{
public:
    static const QEvent::Type EventType;
    
    VStyleAppliedEvent() : QEvent(EventType) {}
};

class VORTEX_CORE_EXPORT VBoxStyle : public QCommonStyle
{
    Q_OBJECT

public:
    VBoxStyle();
    
    void drawPrimitive(
        PrimitiveElement pe,
        const QStyleOption* opt,
        QPainter* p,
        const QWidget* w = nullptr) const override;
    
    void drawControl(
        ControlElement element,
        const QStyleOption* opt,
        QPainter* p,
        const QWidget* w = nullptr) const override;

private:
    QPainterPath create_box_path(
        const QRect& rect, const VBoxCornerRadii& radii) const;
    
    void draw_box_background(
        QPainter* p,
        const QWidget* widget,
        const QRect& rect) const;
};

VORTEX_NAMESPACE_END

// Declare metatypes for custom structs
Q_DECLARE_METATYPE(Vortex::VBoxCornerRadii)
Q_DECLARE_METATYPE(Vortex::VBoxMargins)

#endif // VBOXSTYLE_H