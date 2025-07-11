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
#include <unistd.h>

// Common Error Function
static inline void error(const char *msg, const char *msg1) {
  fprintf(stderr, "ERROR: %s%s\n", msg, msg1 ? msg1 : "");
  exit(1);
}

// Build Type Macros
#define TYPE_E 0
#define TYPE_A 2
#define TYPE_R 1

// Array to hold TOML array
typedef struct {
    int count;
    char* values[];
} FlexArray;

// Master config struct
typedef struct CM_Build {
    struct { // Package Info
        char* name; // Package Name
        char* installdir; // Package Install Directory
        enum {
            exec = TYPE_E,
            recs = TYPE_R,
            alib = TYPE_A
        } type; // Build Type
    } PkgInfo;

    struct {
        char* compiler; // Compiler to use
        char* cflags; // C Flags
        FlexArray* includes; // Include Directories
        FlexArray* ldirs; // Library Directories
        FlexArray* libs; // Libraries to link
        FlexArray* sources; // Sources
    } BuildInfo; // Compiler/Linker Info

    struct { // Recursive build info
        FlexArray* subdirs; // Subdirecoties
    } RecurseInfo;
} CM_Build;

// Function Prototypes
void pkgparse(FILE* out, toml_result_t result, CM_Build* config);
void buildparse(FILE* out, toml_result_t result, CM_Build* config);
void GenRecurseBuild(FILE* out, toml_result_t result, CM_Build* config);
void GenCommonRules(FILE* out, CM_Build* config);

// Function to check if TOML object is an array of strings
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

// Fill a flex array
#define FillFlexArray(datumt, field)                                       \
    if (check_toml_string_array(datumt)) {                                 \
        config->field = malloc(sizeof(FlexArray) +                         \
                              sizeof(char*) * datumt.u.arr.size);          \
        if (!config->field) error("Failed to allocate " #field "\n", 0);   \
        config->field->count = datumt.u.arr.size;                          \
        for (int i = 0; i < datumt.u.arr.size; i++) {                      \
            const char* toml_str = datumt.u.arr.elem[i].u.s;               \
            config->field->values[i] = strdup(toml_str);                   \
            if (!config->field->values[i])                                 \
                error("strdup failed for " #field "[%d]\n", 0);            \
        }                                                                  \
    }