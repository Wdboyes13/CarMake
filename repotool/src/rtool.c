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

int main(int argc, char* argv[]){
    bool dogit = true;
    bool dotsts = true;
    for (int i = 0; i < argc; i++){
        if (strcmp("-ng", argv[i]) == 0) dogit = false;
        if (strcmp("-nt", argv[i]) == 0) dotsts = false;
    }
    if (access(".git", F_OK) != -1) {
        dogit = true;
    } else {
        dogit = false;
    }
    ProjectInfo* info = malloc(sizeof(ProjectInfo));
    Parse(info);
    if (dotsts) DoAllTests(info);
    if (dogit) DoAllGit(info);
    if (info) free(info);
    return 0;
}