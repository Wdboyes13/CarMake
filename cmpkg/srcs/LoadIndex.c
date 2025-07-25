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
#include "Index.h"

Package* pkgs = NULL;
int pkgsnum = 0;

void LoadPackageIndex(const char* filename) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_dofile(L, filename) != LUA_OK) {
        fprintf(stderr, "Failed to load package index: %s\n", lua_tostring(L, -1));
        return;
    }

    lua_getglobal(L, "pkgs");
    if (!lua_istable(L, -1)) {
        fprintf(stderr, "'pkgs' is not a table\n");
        return;
    }

    int count = lua_rawlen(L, -1);
    pkgs = malloc(sizeof(Package) * count);
    pkgsnum = count;

    for (int i = 0; i < count; i++) {
        lua_rawgeti(L, -1, i + 1); // pkgs[i+1]

        lua_getfield(L, -1, "url");
        lua_getfield(L, -2, "name");
        lua_getfield(L, -3, "oname");
        lua_getfield(L, -4, "urlbase");

        pkgs[i].url = strdup(lua_tostring(L, -4));
        pkgs[i].name = strdup(lua_tostring(L, -3));
        pkgs[i].oname = strdup(lua_tostring(L, -2));
        pkgs[i].urlbase = strdup(lua_tostring(L, -1));

        lua_pop(L, 5); // remove table and 4 fields
    }

    lua_close(L);
}