#pragma once

#include <lua.h>
#include <lauxlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <lualib.h>
#include <unistd.h>
#include <string.h>

void GetMeta(lua_State* l);
void ParseBuild(lua_State *l);
void DoFullBuild(const char* argv1);
int DecompressZst(const char* in_path, const char* out_path);