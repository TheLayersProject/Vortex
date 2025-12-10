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

#include <VortexCore/vboxstyle.h>

#include <QApplication>
#include <QWidget>
#include <QColor>
#include <QLinearGradient>
#include <QPainterPath>
#include <QDebug>

#include <Layers/lattribute.h>
#include <Layers/lcontroller.h>
#include <Layers/lstyle.h>

#include <VortexCore/vconvert.h>

using namespace Vortex;

using Layers::LString;
using Layers::LStringList;
using Layers::LStyle;
using Layers::LAttribute;

const QEvent::Type VStyleAppliedEvent::EventType = 
    static_cast<QEvent::Type>(QEvent::registerEventType());

void Vortex::init_state_pools(QObject* obj)
{
    if (!obj) return;
    
    auto state_pools = new QList<VStatePool*>();
    obj->setProperty("layers_State_Pools",
        QVariant::fromValue(static_cast<void*>(state_pools))); 
}

void Vortex::add_state_pool(
    QObject* obj,
    VStatePool* state_pool,
    bool include_children)
{
    if (!obj || !state_pool) return;

    QVariant pools_var = obj->property("layers_State_Pools");
    if (!pools_var.isValid())
    {
        Vortex::init_state_pools(obj);
        pools_var = obj->property("layers_State_Pools");
    }   

    auto state_pools = static_cast<QList<VStatePool*>*>(
        pools_var.value<void*>());

    state_pools->append(state_pool);

    state_pool->connect(state_pool, &VStatePool::changed,
        [obj] {
            QCoreApplication::postEvent(obj, new VStyleAppliedEvent());
        });

    if (include_children)
        for (QObject* child : obj->findChildren<QObject*>())
            Vortex::add_state_pool(child, state_pool, false);
}

LStringList Vortex::get_state_combo(const QObject* obj)
{
    Layers::LStringList state_combo;

    if (!obj) return state_combo;

    QVariant pools_var = obj->property("layers_State_Pools");
    if (pools_var.isValid())
    {
        auto state_pools = static_cast<QList<VStatePool*>*>(
            pools_var.value<void*>());

        for (VStatePool* state_pool : *state_pools)
            state_combo.push_back(
                Layers::LString(state_pool->state().toStdString().c_str()));
    }

    return state_combo;
}

void Vortex::share_state_pools(const QObject* parent, QObject* child)
{
    if (!child || !parent) return;
    
    QVariant poolsVar = parent->property("layers_State_Pools");
    if (poolsVar.isValid())
        child->setProperty("layers_State_Pools", poolsVar);
}

// ============================================================================
// Helper Functions
// ============================================================================

void Vortex::debug_lstyle_structure(const LStyle* style, int indent)
{
    if (!style) {
        qDebug() << "DEBUG: style is nullptr";
        return;
    }
    
    QString indentStr(indent * 2, ' ');
    
    qDebug().noquote() << indentStr << "Style:" << style->object_name().c_str() 
                       << "Path:" << style->path().c_str();
    
    // Show attributes
    const auto& attributes = style->attributes();
    if (!attributes.empty()) {
        qDebug().noquote() << indentStr << "  Attributes:" << attributes.size();
        for (const auto& [name, attr] : attributes) {
            qDebug().noquote() << indentStr << "    -" << name.c_str();
        }
    }
    
    // Show children
    const auto& children = style->children();
    if (!children.empty()) {
        qDebug().noquote() << indentStr << "  Children:" << children.size();
        for (const auto& [name, child] : children) {
            qDebug().noquote() << indentStr << "    -" << name.c_str();
            // Recursively show child structure
            debug_lstyle_structure(child, indent + 2);
        }
    }
    else {
        qDebug().noquote() << indentStr << "  (no children)";
    }
}

void Vortex::debug_widget_style(const QWidget* widget)
{
    if (!widget) {
        qDebug() << "DEBUG: widget is nullptr";
        return;
    }
    
    qDebug() << "=== Style Debug for:" << widget->objectName() << "===";
    qDebug() << "  Widget type:" << widget->metaObject()->className();
    qDebug() << "  Widget path:" << get_widget_style_path(widget);
    
    // Check if LStyle was found
    LStyle* style = get_widget_lstyle(widget);
    qDebug() << "  LStyle found:" << (style ? "YES" : "NO");
    if (style) {
        qDebug() << "    Style name:" << style->object_name().c_str();
        qDebug() << "    Style path:" << style->path().c_str();
    }
    
    // Check stored path
    QVariant pathVar = widget->property("layers_Style_Path");
    qDebug() << "  Stored path:" << pathVar.toString();
    
    // Check if WA_StyledBackground is set
    qDebug() << "  WA_StyledBackground:" << widget->testAttribute(Qt::WA_StyledBackground);
    
    // Check properties
    qDebug() << "  Fill:" << style->find_attribute("Fill")->as<LString>().c_str();
    qDebug() << "  Border fill:" << style->find_attribute("Border.Fill")->as<LString>().c_str();
    
    // QVariant radii = widget->property("layers_Corner_Radii"););
    // qDebug() << "  Corner radii valid:" << radii.isValid();
    // if (radii.isValid()) {
    //     BoxCornerRadii r = radii.value<BoxCornerRadii>();
    //     qDebug() << "    TL:" << r.top_left << "TR:" << r.top_right 
    //              << "BL:" << r.bottom_left << "BR:" << r.bottom_right;
    // }
    
    qDebug() << "==================";
}

void Vortex::update_all_styled_widgets(QWidget* root)
{
    // If no root specified, update all top-level windows
    if (!root)
    {
        for (QWidget* window : QApplication::topLevelWidgets())
            update_all_styled_widgets(window);

        return;
    }
    
    // Update the root if it has a style
    if (get_widget_lstyle(root))
    {
        root->update();
        QCoreApplication::postEvent(root, new VStyleAppliedEvent());
    }
    
    // Recursively update all children
    for (QWidget* child : root->findChildren<QWidget*>())
        if (get_widget_lstyle(child))
        {
            child->update();
            QCoreApplication::postEvent(child, new VStyleAppliedEvent());
        }
    
    // // Also trigger updates for non-widget children (QLSvgRenderer, etc)
    // for (QObject* obj : root->findChildren<QObject*>()) {
    //     if (qobject_cast<QWidget*>(obj)) continue; // Skip widgets
        
    //     // Post StyleAppliedEvent to trigger their updates
    //     if (get_widget_lstyle_from_qobject(obj)) {
    //         QCoreApplication::postEvent(obj, new StyleAppliedEvent());
    //     }
    // }
}

QString Vortex::get_widget_style_path(const QWidget* widget)
{
    if (!widget) return QString();

    QStringList parts;
    
    // Build path from widget up to top-level parent
    for (const QWidget* current = widget; current; current = qobject_cast<const QWidget*>(current->parent()))
    {
        QString name = current->objectName();
        if (!name.isEmpty()) {
            parts.prepend(name);  // Prepend to build parent/child/widget order
        }
    }

    return parts.join('/');
}

Layers::LStyle* Vortex::get_widget_lstyle(const QObject* obj)
{
    if (!obj) return nullptr;
    
    QVariant styleVar = obj->property("layers_Style");
    if (!styleVar.isValid()) return nullptr;
    
    return static_cast<Layers::LStyle*>(styleVar.value<void*>());
}

// ============================================================================
// Style Application Functions
// ============================================================================

// void Vortex::apply_layers_style_recursive(QWidget* root)
// {
//     if (!root) return;
    
//     // Apply to root first
//     apply_layers_style_auto(root);
    
//     // Then recursively apply to all children
//     for (QWidget* child : root->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly))
//     {
//         apply_layers_style_recursive(child);
//     }
// }

void Vortex::apply_layers_style_from_parent(QWidget* widget)
{
    if (!widget) return;
    
    // Get parent widget
    QWidget* parent = qobject_cast<QWidget*>(widget->parent());
    if (!parent) {
        // No parent, try auto-detection
        apply_layers_style_auto(widget);
        return;
    }
    
    // Get parent's LStyle
    LStyle* parentStyle = get_widget_lstyle(parent);
    if (!parentStyle) {
        // Parent has no style, try auto-detection
        apply_layers_style_auto(widget);
        return;
    }
    
    // Look up child style
    QString childName = widget->objectName();
    if (childName.isEmpty()) {
        qWarning() << "Cannot apply style from parent: widget has no object name";
        return;
    }
    
    LStyle* childStyle = parentStyle->find_item(childName.toStdString().c_str());
    apply_layers_style(widget, childStyle);
}

void Vortex::apply_layers_style(QObject* obj, LStyle* style)
{
    if (!obj || !style) return;
    
    // Store pointer to the LStyle for future reference
    obj->setProperty("layers_Style", 
                       QVariant::fromValue(static_cast<void*>(style)));

    //share_state_pools(obj->parent(), obj);

    // Enable styled background so QStyle gets called
    if (QWidget* widget = qobject_cast<QWidget*>(obj))
    {
        widget->setAttribute(Qt::WA_StyledBackground, true);
    }

    QCoreApplication::postEvent(obj, new VStyleAppliedEvent());

    /* Post event when user-style is applied to style */
    style->on_style_applied([obj]() {
        QCoreApplication::postEvent(obj, new VStyleAppliedEvent()); } );

    // RECURSIVE PART: Apply child styles to child widgets
    const auto& children_map = style->children();
    if (!children_map.empty()) {
        for (QObject* child : obj->findChildren<QWidget*>(QString(), Qt::FindDirectChildrenOnly))
        {
            QString childName = child->objectName();
            if (!childName.isEmpty()) {
                auto it = children_map.find(childName.toStdString().c_str());
                if (it != children_map.end())
                {
                    apply_layers_style(child, it->second);  // Recursive call
                }
            }
        }
    }
}

void Vortex::apply_layers_style_by_path(QWidget* widget, const QString& style_path)
{
    if (!widget) return;
    
    // Store the style path for future lookups
    widget->setProperty("layers_Style_Path", style_path);
    
    // Look up the style in the Layers controller
    LStyle* style = lController.find_style(style_path.toStdString().c_str());
    
    apply_layers_style(widget, style);
}

void Vortex::apply_layers_style_auto(QWidget* widget)
{
    if (!widget) return;
    
    // Automatically determine the style path from widget hierarchy
    QString path = get_widget_style_path(widget);
    
    if (path.isEmpty()) {
        qWarning() << "Cannot auto-apply style: widget has no object name";
        return;
    }
    
    apply_layers_style_by_path(widget, path);
}

void Vortex::refresh_widget_style(QWidget* widget)
{
    if (!widget) return;
    
    // Check if widget has a stored style path
    QVariant pathVar = widget->property("layers_Style_Path");
    if (pathVar.isValid() && !pathVar.toString().isEmpty()) {
        apply_layers_style_by_path(widget, pathVar.toString());
    } else {
        // Try auto-detection
        apply_layers_style_auto(widget);
    }
}

// ============================================================================
// VBoxStyle Implementation
// ============================================================================

VBoxStyle::VBoxStyle() : QCommonStyle()
{
}

QPainterPath VBoxStyle::create_box_path(
    const QRect& box_rect, const VBoxCornerRadii& radii) const
{
    QPainterPath path;

    int corner_diameter_tl = radii.top_left * 2;
    int corner_diameter_tr = radii.top_right * 2;
    int corner_diameter_bl = radii.bottom_left * 2;
    int corner_diameter_br = radii.bottom_right * 2;

    // Move to starting point (left side, after top-left corner)
    path.moveTo(box_rect.left(), box_rect.top() + radii.top_left);

    // Top-left arc
    if (radii.top_left > 0) {
        path.arcTo(QRect(box_rect.left(), box_rect.top(),
                        corner_diameter_tl, corner_diameter_tl),
                  180, -90);
    }

    // Top line
    path.lineTo(box_rect.right() - radii.top_right, box_rect.top());

    // Top-right arc
    if (radii.top_right > 0) {
        path.arcTo(QRect(box_rect.right() - corner_diameter_tr, box_rect.top(),
                        corner_diameter_tr, corner_diameter_tr),
                  90, -90);
    }

    // Right line
    path.lineTo(box_rect.right(), box_rect.bottom() - radii.bottom_right);

    // Bottom-right arc
    if (radii.bottom_right > 0) {
        path.arcTo(QRect(box_rect.right() - corner_diameter_br,
                        box_rect.bottom() - corner_diameter_br,
                        corner_diameter_br, corner_diameter_br),
                  0, -90);
    }

    // Bottom line
    path.lineTo(box_rect.left() + radii.bottom_left, box_rect.bottom());

    // Bottom-left arc
    if (radii.bottom_left > 0) {
        path.arcTo(QRect(box_rect.left(),
                        box_rect.bottom() - corner_diameter_bl,
                        corner_diameter_bl, corner_diameter_bl),
                  -90, -90);
    }

    // Close path back to start
    path.closeSubpath();

    return path;
}

void VBoxStyle::draw_box_background(
    QPainter* p,
    const QWidget* widget,
    const QRect& rect) const
{
    if (!widget) return;

    p->setRenderHint(QPainter::Antialiasing);

    // Initialize attributes
    Layers::LAttribute* border_fill = nullptr;
    double border_thickness = 0.0;
    VBoxCornerRadii corner_radii;
    Layers::LAttribute* fill = nullptr;
    VBoxMargins margins;

    LStringList states = Vortex::get_state_combo(widget);

    if (LStyle* style = get_widget_lstyle(widget))
    {
        border_fill = style->find_attribute("Border.Fill");

        if (auto* attr = style->find_attribute("Border.Thickness"))
            border_thickness = attr->as<double>(states);

        if (auto* attr = style->find_attribute("Corner Radii.Top Left"))
            corner_radii.top_left = attr->as<double>(states);
        if (auto* attr = style->find_attribute("Corner Radii.Top Right"))
            corner_radii.top_right = attr->as<double>(states);
        if (auto* attr = style->find_attribute("Corner Radii.Bottom Left"))
            corner_radii.bottom_left = attr->as<double>(states);
        if (auto* attr = style->find_attribute("Corner Radii.Bottom Right"))
            corner_radii.bottom_right = attr->as<double>(states);

        fill = style->find_attribute("Fill");

        if (auto* attr = style->find_attribute("Margins.Left"))
            margins.left = attr->as<double>(states);
        if (auto* attr = style->find_attribute("Margins.Top"))
            margins.top = attr->as<double>(states);
        if (auto* attr = style->find_attribute("Margins.Right"))
            margins.right = attr->as<double>(states);
        if (auto* attr = style->find_attribute("Margins.Bottom"))
            margins.bottom = attr->as<double>(states);
    }

    // Handle maximized windows - no border/corners
    if (widget->isMaximized() || widget->isFullScreen()) {
        border_thickness = 0;
        corner_radii = VBoxCornerRadii(0);
    }

    // Calculate drawing rectangles
    QRect draw_rect = rect.adjusted(margins.left, margins.top, 
                                    -margins.right + 1, -margins.bottom + 1);
    
    QRect border_rect = draw_rect;
    QRect fill_rect = draw_rect.adjusted(border_thickness, border_thickness,
                                        -border_thickness, -border_thickness);

    // Calculate inner corner radii for fill
    VBoxCornerRadii fill_radii;
    if (border_thickness > 0) {
        fill_radii.top_left = std::max(0.0, corner_radii.top_left - border_thickness);
        fill_radii.top_right = std::max(0.0, corner_radii.top_right - border_thickness);
        fill_radii.bottom_left = std::max(0.0, corner_radii.bottom_left - border_thickness);
        fill_radii.bottom_right = std::max(0.0, corner_radii.bottom_right - border_thickness);
    } else {
        fill_radii = corner_radii;
    }

    // Create paths
    QPainterPath fill_path = create_box_path(fill_rect, fill_radii);
    QPainterPath border_path = create_box_path(border_rect, corner_radii) - fill_path;

    // Draw border
    if (border_thickness && border_fill)
    {
        if (auto stops = border_fill->as_if<std::vector<LString>>(states))
		{
			QLinearGradient border_fill_grad;

			border_fill_grad.setStart(border_rect.left(), 0);
			border_fill_grad.setFinalStop(border_rect.right() + 1, 0);
			border_fill_grad.setStops(to_QGradientStops(*stops));

			p->fillPath(border_path, border_fill_grad);
		}
		else
			p->fillPath(border_path,
				QColor(QString::fromStdString(
					border_fill->as<LString>(states).c_str())));
    }

    // Draw fill
    if (fill)
    {
        if (auto stops = fill->as_if<std::vector<LString>>(states))
        {
            QLinearGradient fill_grad;

            fill_grad.setStart(fill_rect.left(), 0);
            fill_grad.setFinalStop(fill_rect.right() + 1, 0);
            fill_grad.setStops(to_QGradientStops(*stops));

            p->fillPath(fill_path, fill_grad);
        }
        else
            p->fillPath(fill_path,
                QColor(QString::fromStdString(fill->as<LString>(states).c_str())));
    }
}

void VBoxStyle::drawPrimitive(
    PrimitiveElement pe,
    const QStyleOption* opt,
    QPainter* p,
    const QWidget* w) const
{
    if (w && w->testAttribute(Qt::WA_StyledBackground))
    {
        if (pe == PE_Widget ||
            pe == PE_PanelLineEdit)
        {
            p->save();
            draw_box_background(p, w, opt->rect);
            p->restore();
            return;
        }
    }

    // Delegate to base class for other primitives
    QCommonStyle::drawPrimitive(pe, opt, p, w);
}

void VBoxStyle::drawControl(
    ControlElement element,
    const QStyleOption* opt,
    QPainter* p,
    const QWidget* w) const
{
    // You can override specific control elements here if needed
    // For now, just delegate to base class
    QCommonStyle::drawControl(element, opt, p, w);
}