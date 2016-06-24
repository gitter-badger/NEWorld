/*
* NEWorld: A free game with similar rules to Minecraft.
* Copyright (C) 2016 NEWorld Team
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SETTINGSMANAGER_H__
#define SETTINGSMANAGER_H__
#include <map>
#include <string>
#include <fstream>
#include <boost/spirit/home/support/detail/hold_any.hpp>

class Settings
{
public:
    //ʹ���ļ�����ʼ��Settings���Զ��Ӹ��ļ���ȡ����
    Settings(std::string filename) :m_settings(readFromFile(std::ifstream(filename))), m_filename(filename) {}

    //�������ļ����浽��ȡ���ļ�
    void save()
    {
        writeToFile(std::ofstream(m_filename), m_settings);
    }

    //�������ļ��л�ȡ����
    template<class T>
    T get(std::string key, T defaultValue)
    {
        auto result = m_settings.find(key);
        if (result != m_settings.end())
            return result->second.cast<T>();
        else
        {
            m_settings[key] = defaultValue;
            return defaultValue;
        }
    }

    //����ĳһ������
    template<class T>
    void set(std::string key, const T& value)
    {
        m_settings[key] = value;
    }

    bool have(std::string key)
    {
        return m_settings.find(key) != m_settings.end();
    }

private:
    using SettingsMap = std::map<std::string, boost::spirit::hold_any>;
    SettingsMap m_settings;
    std::string m_filename;

    //���ļ���ȡ����
    static SettingsMap readFromFile(std::ifstream& file);

    //������д�뵽�ļ�
    static void writeToFile(std::ofstream& file, const SettingsMap& settings);
};


#endif // SETTINGSMANAGER_H__