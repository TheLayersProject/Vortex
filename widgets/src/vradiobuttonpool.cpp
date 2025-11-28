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

#include <VortexWidgets/vradiobuttonpool.h>

#include <VortexWidgets/vradiobutton.h>

using Vortex::VRadioButtonPool;

VRadioButtonPool::VRadioButtonPool(QList<VRadioButton*> radio_buttons) :
	m_radio_buttons{ radio_buttons }
{
	set_active(m_radio_buttons.first());

	for (VRadioButton* radio_button : m_radio_buttons)
		connect(radio_button, &VRadioButton::clicked, [this, radio_button]
			{ set_active(radio_button); });
}

void VRadioButtonPool::set_active(VRadioButton* button)
{
	if (m_radio_buttons.contains(button) && m_active_button != button)
	{
		if (m_active_button)
			m_active_button->status_states()->set_state("Inactive");

		m_active_button = button;
		m_active_button->status_states()->set_state("Active");
	}
}
