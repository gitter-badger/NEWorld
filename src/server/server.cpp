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

#include "server.h"

using namespace boost::asio;
using namespace boost::system;

unsigned short globalPort;

void errorHandle(const tcp::socket& m_socket, error_code ec)
{
    infostream << m_socket.remote_endpoint().address().to_string() << " disconnected, code: " << ec.value();
}

void Session::doUpdate()
{
    return;
    auto self(shared_from_this());
    deadline_timer(m_socket.get_io_service(), boost::posix_time::microseconds(updateInterval)).async_wait(
        [this, self](error_code)
    {
        // TODO: Process client actions here
        doWrite();
    });
}

//void Server::sendToAllSessions(Packet packet)
//{
//TODO: fix it
//for (auto iter = m_sessions.begin(); iter != m_sessions.end();)
//{
//    auto session = iter->lock();
//    if (session)
//    {
//        session->addRequest(packet);
//        ++iter;
//    }
//    else
//    {
//        iter = m_sessions.erase(iter);
//    }
//}
//}

void Server::doAccept()
{
    m_acceptor.async_accept(m_socket, [this](boost::system::error_code ec)
    {
        if (!ec)
        {
            infostream << m_socket.remote_endpoint().address().to_string() << " connected to the server";
            auto session = std::make_shared<Session>(std::move(m_socket));
            session->start();
            m_sessions.push_back(session);
        }
        doAccept();
    });
}

void Server::doGlobalUpdate()
{
    return;
    boost::asio::deadline_timer(m_socket.get_io_service(), boost::posix_time::microseconds(globalUpdateInterval)).async_wait(
        [this](boost::system::error_code)
    {
        // Update worlds
        for (auto world : m_worlds) world->update();
        doGlobalUpdate();
    });
}
