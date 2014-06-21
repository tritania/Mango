/*
 * Copyright 2014 <erikwilson@magnorum.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
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
#include "files.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/filesystem.hpp>

MangoCommands::MangoCommands()
{
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    std::string home(homedir);
    std::string dir = home + std::string("/.config/mango/mango.conf");
    std::string confdir = home + std::string("/.config");
    std::string conf = home + std::string("/.config/mango");

    boost::filesystem::create_directories(confdir.c_str());
    boost::filesystem::create_directories(conf.c_str());

    std::cout << "Commands are being loaded! " << dir <<std::endl;
    std::ifstream file(dir.c_str());
    if (file.is_open())
    {
        std::string str;
        bool typeCommand = false;
        std::string gesture = str;
        std::string command = str;
        while (getline(file, str))
        {
            if (!typeCommand) {
                gesture = str;
                typeCommand = true;
            } else {
                command = str;
                commands[gesture] = command;
                std::cout << gesture << " " << command << std::endl;
                typeCommand = false;
            }
        }
    }
    else
    {
        std::ofstream out(dir.c_str());
        std::cout << "Please add commands to the config file" << std::endl;
    }
}

std::string MangoCommands::getCommand(std::string gesture) {
    if (commands.find(gesture) != commands.end()) {
        return commands[gesture];
    } else {
        return "NOT_FOUND";
    }
}

void MangoCommands::reloadCommands() {

}
