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

void DoFullBuild(const char* Filename){
    lua_State *l = luaL_newstate();
    luaL_openlibs(l);
    if (luaL_dofile(l, Filename) != LUA_OK) {
        fprintf(stderr, "Failed to load %s: %s\n", Filename, lua_tostring(l, -1));
        exit(1);
    }
    GetMeta(l);
    ParseBuild(l);
    lua_close(l);
}