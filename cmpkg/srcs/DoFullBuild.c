#include "Common.h"

void DoFullBuild(const char* argv1){
    char *ext = strstr(argv1, ".zst");
    if (ext && strcmp(ext, ".zst") == 0) {
        *ext = '\0';  // Truncate string at start of ".zst"
    }
    const char* Filename = argv1;
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