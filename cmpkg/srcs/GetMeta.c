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