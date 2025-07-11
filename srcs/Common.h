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

// Common Includes
#include "../include/tomlc17.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Common Error Function
static inline void error(const char *msg, const char *msg1) {
  fprintf(stderr, "ERROR: %s%s\n", msg, msg1 ? msg1 : "");
  exit(1);
}

#define TYPE_E 0
#define TYPE_A 2

typedef struct {
    int count;
    char* values[];
} FlexArray;

typedef struct CM_Build {
    char* name;
    enum {
        exec = TYPE_E,
        alib = TYPE_A
    } type;

    char* compiler;
    char* cflags;
    FlexArray* includes;
    FlexArray* ldirs;
    FlexArray* libs;
    FlexArray* sources;
} CM_Build;

// Function Prototypes
void pkgparse(FILE* out, toml_result_t result, CM_Build* config);
void buildparse(FILE* out, toml_result_t result, CM_Build* config);
void GenCommonRules(FILE* out, CM_Build* config);