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

void ParseBuild(lua_State *l){
        // Get the global 'build' array
    lua_getglobal(l, "build");
    if (!lua_istable(l, -1)) {
        fprintf(stderr, "'build' is not a table\n");
        lua_close(l);
        exit(1);
    }

    int build_len = lua_rawlen(l, -1);
    printf("Build steps (%d):\n", build_len);

    for (int i = 1; i <= build_len; i++) {
        lua_rawgeti(l, -1, i); // Push build[i] onto the stack

        if (lua_isstring(l, -1)) {
            const char* step = lua_tostring(l, -1);
            printf("  [%d] %s\n", i, step);
            if (strncmp(step, "cd ", 3) == 0) {
                const char* path = step + 3;
                if (chdir(path) != 0) {
                    perror("chdir failed");
                }
            } else {
                int ret = system(step);
                if (ret != 0) {
                    fprintf(stderr, "Command failed: %s\n", step);
                    exit(1);
                }
                printf("Ran Step %d", i);
            }
        } else {
            printf("  [%d] <non-string item>\n", i);
        }

        lua_pop(l, 1); // Remove value, keep table on stack
    }

    // Done with the 'build' array
    lua_pop(l, 1);
}