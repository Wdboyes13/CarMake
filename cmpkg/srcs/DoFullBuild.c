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