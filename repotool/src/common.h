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

#pragma once

#include <limits.h>
#include <stdio.h>
#include "../../cm/include/tomlc17.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "gitwrap.h"
#include <time.h>

static inline void error(const char *msg, const char *msg1) {
  fprintf(stderr, "ERROR: %s%s\n", msg, msg1 ? msg1 : "");
  exit(1);
}

typedef struct {
    int count;
    char* values[];
} FlexArray;

typedef struct ProjectInfo {
    struct GitInfo {
        char* AuthName;
        char* AuthMail;
        char* RemName;
        char* LocName;
    } GitInfo;
    struct TestInfo {
        char* TestFolderPath;
        FlexArray* TestNames;
    } TestInfo;
} ProjectInfo;

#define FillFlexArray(datumt, field)                                       \
    if (check_toml_string_array(datumt)) {                                 \
        info->field = malloc(sizeof(FlexArray) +                         \
                              sizeof(char*) * datumt.u.arr.size);          \
        if (!info->field) error("Failed to allocate " #field "\n", 0);   \
        info->field->count = datumt.u.arr.size;                          \
        for (int i = 0; i < datumt.u.arr.size; i++) {                      \
            const char* toml_str = datumt.u.arr.elem[i].u.s;               \
            info->field->values[i] = strdup(toml_str);                   \
            if (!info->field->values[i])                                 \
                error("strdup failed for " #field "[%d]\n", 0);            \
        }                                                                  \
    }

static inline bool check_toml_string_array(toml_datum_t array){
    if (array.type != TOML_ARRAY){
        return false;
    }
    for (int i = 0; i < array.u.arr.size; i++){
        toml_datum_t elem = array.u.arr.elem[i];
        if (elem.type != TOML_STRING){
            return false;
        }
    }
    return true;
}

void Parse(ProjectInfo* info);
void DoAllTests(ProjectInfo* info);
void DoAllGit(ProjectInfo* info);
extern char **environ;