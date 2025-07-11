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