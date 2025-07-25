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

#include "common.h"

void DoAllGit(ProjectInfo* info){
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    char buf[128];
    strftime(buf, sizeof(buf), "%a %d %b %Y %T %Z", local);

    gitinit();
    stageall();

    char* msg = malloc(sizeof(char) * 512);
    sprintf(msg, "Updated at: %s", buf);

    commit(info->GitInfo.AuthMail, info->GitInfo.AuthName, msg);
    pushmain(info->GitInfo.RemName, info->GitInfo.LocName);
}