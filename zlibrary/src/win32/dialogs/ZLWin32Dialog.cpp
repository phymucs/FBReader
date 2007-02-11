/*
 * Copyright (C) 2007 Nikolay Pultsin <geometer@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "ZLWin32Dialog.h"
#include "ZLWin32DialogContent.h"
#include "../application/ZLWin32ApplicationWindow.h"

ZLWin32Dialog::ZLWin32Dialog(ZLWin32ApplicationWindow &window, const std::string &name) : myWindow(window), myTitle(name), myPanel(myWindow.mainWindow(), myTitle) {
	const short charHeight = myPanel.charDimension().Height;

	W32VBox *panelBox = new W32VBox();
	myPanel.setElement(panelBox);

	ZLWin32DialogContent *contentTab = new ZLWin32DialogContent();
	myTab = contentTab;
	panelBox->addElement(contentTab->contentPtr());
	W32Table &table = contentTab->contentTable();
	table.setSpacings(charHeight / 2, charHeight);
	table.setMargins(charHeight / 2, charHeight / 2, charHeight / 2, charHeight / 2);

	myButtonBox = new W32HBox();
	panelBox->addElement(myButtonBox);
	myButtonBox->setHomogeneous(true);
	myButtonBox->setSpacing(charHeight / 2);
	myButtonBox->setMargins(charHeight / 2, charHeight / 2, charHeight / 2, charHeight / 2);
}

void ZLWin32Dialog::addButton(const std::string &text, bool accept) {
	W32WidgetPtr button = new W32PushButton(text, accept ? W32PushButton::OK_BUTTON : W32PushButton::CANCEL_BUTTON);
	button->setVisible(true);
	myButtonBox->addElement(button);
}

bool ZLWin32Dialog::run() {
	myWindow.blockMouseEvents(true);
	bool result = myPanel.runDialog();
	myWindow.blockMouseEvents(false);
	return result;
}
