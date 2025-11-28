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

#ifndef VLINEEDITOR_H
#define VLINEEDITOR_H

#include <QLineEdit>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include <Layers/lattribute.h>

#include <VortexWidgets/vortex_widgets_global.h>
#include <VortexWidgets/vortex_widgets_export.h>

#include "vlabel.h"

VORTEX_NAMESPACE_BEGIN
class VORTEX_WIDGETS_EXPORT VLineEditor : public QLineEdit
{
    Q_OBJECT
        Q_PROPERTY(QPointF labelPos READ labelPos WRITE setLabelPos)
        Q_PROPERTY(qreal labelFontSize READ labelFontSize WRITE setLabelFontSize)

signals:
    void editing_finished();
    void text_edited(const QString& text);

public:
    VLineEditor(QWidget* parent = nullptr);
    ~VLineEditor();

    // Getters and setters for animation properties
    QPointF labelPos() const;
    void setLabelPos(const QPointF& pos);
    qreal labelFontSize() const;
    void setLabelFontSize(qreal size);

    // Existing public methods...
    Layers::LAttribute* left_padding() const;
    void set_default_value(const QString& default_value);
    void set_font_size(int size);
    void set_font_size_f(qreal size);
    void set_pretext(const QString& pretext);
    void set_text(const QString& text);
    void set_validator(const QValidator* validator);
    Layers::LAttribute* text() const;
    Layers::LAttribute* text_color() const;
    void update();

protected:
    bool event(QEvent* e) override;

private:
    //void init_attributes();
    void setupAnimations();
    void startFloatingAnimation(bool floating);
    void updateBaseLabelPosition();

    Layers::LAttribute* m_left_padding{
        new Layers::LAttribute("left_padding", 3.0) };
    Layers::LAttribute* m_text_color{
        new Layers::LAttribute("Text Color", "#000000") };
    Layers::LAttribute* m_text{
        new Layers::LAttribute("text", "") };

    QString* m_default_value{ nullptr };
    //QLineEdit* m_line_edit{ new QLineEdit(this) };
    VLabel* m_pretext_label{ new VLabel(this) };

    // Animation related members
    QParallelAnimationGroup* m_animationGroup{ nullptr };
    QPropertyAnimation* m_positionAnimation{ nullptr };
    QPropertyAnimation* m_fontSizeAnimation{ nullptr };
    qreal m_normalFontSize{ 12.0 };
    qreal m_floatingFontSize{ 9.0 };
    int m_floatingOffset{ -12 };

    // New members for tracking state
    QPointF m_baseLabelPos;
    bool m_isFloating{ false };
};
VORTEX_NAMESPACE_END

#endif // VLINEEDITOR_H
