/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
*
* This file is part of NEWorld.
* NEWorld is free software: you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* NEWorld is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with NEWorld.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAIN_MENU_H_
#define MAIN_MENU_H_

#include <uilib.h>

class BackGround : public UI::Controls::GLContext
{
public:
    BackGround(UI::Core::Window * win);
private:
    unsigned long long elapsed;
};

class MainMenu : public UI::Core::Grid
{
public:
    MainMenu(UI::Core::Window* win);
};

#endif
