#pragma once


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <curl/curl.h>
#include <zstd.h>

void GetMeta(lua_State* l);
void ParseBuild(lua_State *l);
void DoFullBuild(const char* argv1);
int DecompressZst(const char* in_path, const char* out_path);
void DownloadFile(const char* url, const char* out);
void LoadPackageIndex(const char* filename);