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

MangoCommands::MangoCommands()
{
    std::cout << "Commands are being loaded!" << std::endl;
        std::ifstream file("~/.Mango/config");
    if (file.is_open())
    {
        std::string str;
        while (getline(file, str))
        {

        }
    }
    else
    {
        file.open("~/.Mango/config",std::fstream::out);
        std::cout << "Please add commands to the config file" << std::endl;
    }
}

void MangoCommands::reloadCommands() {

}
