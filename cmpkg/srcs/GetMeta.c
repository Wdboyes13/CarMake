/*
CarMake - A simple build system using TOML
Copyright (C) 2025  Wdboyes13

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "Common.h"

void GetMeta(lua_State* l){
    // Get the 'package' table
    lua_getglobal(l, "package");
    if (!lua_istable(l, -1)) {
        fprintf(stderr, "'package' is not a table\n");
        exit(1);
    }

    // Read fields
    lua_getfield(l, -1, "name");
    const char* name = lua_tostring(l, -1);
    lua_pop(l, 1);

    lua_getfield(l, -1, "license");
    const char* license = lua_tostring(l, -1);
    lua_pop(l, 1);

    lua_getfield(l, -1, "version");
    const char* version = lua_tostring(l, -1);
    lua_pop(l, 1);

    lua_getfield(l, -1, "author");
    const char* author = lua_tostring(l, -1);
    lua_pop(l, 1);

    // Done with the package table
    lua_pop(l, 1);

    printf("Name: %s\nLicense: %s\nVersion: %s\nAuthor: %s\n", name, license, version, author);
}