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

#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include <vector>

#include "world.h"
#include "pluginmanager.h"
#include "blockmanager.h"

// Multi-world
class WorldManager
{
public:
    WorldManager(PluginManager& plugins, BlockManager& blocks) : m_plugins(plugins), m_blocks(blocks)
    {
    }

    ~WorldManager()
    {
        m_worlds.clear();
    }

    World* addWorld(const std::string& name)
    {
        m_worlds.emplace_back(new World(name, m_plugins, m_blocks));
        return m_worlds[m_worlds.size() - 1];
    }

    std::vector<World*>::iterator begin() { return m_worlds.begin(); }
    std::vector<World*>::iterator end() { return m_worlds.end(); }

private:
    std::vector<World*> m_worlds;
    PluginManager& m_plugins;
    BlockManager& m_blocks;
};

#endif
