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

#include <VortexWidgets/vplaintexteditor.h>

#include <Layers/lattribute.h>
#include <Layers/lstyle.h>
#include <VortexCore/vboxstyle.h>

using Layers::LString;
using Vortex::VPlainTextEditor;

VPlainTextEditor::VPlainTextEditor(QWidget* parent) :
	QPlainTextEdit(parent)
{
	document()->setDocumentMargin(10);

	viewport()->setAutoFillBackground(false);

	setFrameStyle(QFrame::NoFrame);

	//update();
}

void VPlainTextEditor::update()
{
	if (Layers::LStyle* style = Vortex::get_widget_lstyle(this)) {
		if (auto* attr = style->find_attribute("Text Color")) {
			QString textColor = QString::fromStdString(attr->as<LString>().c_str());
			
			QPalette pal = palette();
			pal.setColor(QPalette::Text, QColor::fromString(textColor));
			setPalette(pal);
		}
	}

	// Call the base class update method
	QPlainTextEdit::update();
}

bool VPlainTextEditor::event(QEvent* e)
{
	if (e->type() == Vortex::VStyleAppliedEvent::EventType)
	{
        update();

        return true;
    }
    
    return QPlainTextEdit::event(e);
}
