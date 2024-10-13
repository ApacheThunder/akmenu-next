/*
    startmenu.h
    Copyright (C) 2007 Acekard, www.acekard.com
    Copyright (C) 2007-2009 somebody
    Copyright (C) 2009 yellow wood goblin

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "popmenu.h"

#define START_MENU_ITEM_SETTING 0
#define START_MENU_ITEM_INFO 1
#define START_MENU_ITEM_HELP 2
#define START_MENU_ITEM_TOOLS 3

class cStartMenu : public akui::cPopMenu {
  public:
    cStartMenu(s32 x, s32 y, u32 w, u32 h, cWindow* parent, const std::string& text)
        : cPopMenu(x, y, w, h, parent, text) {}

    ~cStartMenu() {}

    void init();

    bool process(const akui::cMessage& msg);

    cWindow& loadAppearance(const std::string& aFileName);
};
