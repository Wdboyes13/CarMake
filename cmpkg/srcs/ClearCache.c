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

#ifdef _WIN32 
#define RMCMD "rmdir /s /q "
#else
#define RMCMD "rm -rf "
#endif

void DelPath(const char* path){
    char cmd[1024];
    sprintf(cmd, "%s %s", RMCMD, path);
    system(cmd);
}

void ClearCache(){
    const char* home = getenv("HOME");
    char indexdir[PATH_MAX];
    sprintf(indexdir, "%s/.cmpkg/", home);
    char indexpath[PATH_MAX];
    sprintf(indexpath, "%s/.cmpkg/packages.lua", home);
    ensure_dir(indexdir);
    char cachedir[PATH_MAX];
    sprintf(cachedir, "%s/.cmpkg/cache", home);
    ensure_dir(cachedir);

    DelPath(indexpath);
    DelPath(cachedir);

    exit(0);
}