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

#define FillFlexArray(datumt, field)                                       \
    if (check_toml_string_array(datumt)) {                                 \
        config->field = malloc(sizeof(FlexArray) +                          \
                              sizeof(char*) * datumt.u.arr.size);         \
        if (!config->field) error("Failed to allocate " #field "\n", 0);   \
        config->field->count = datumt.u.arr.size;                           \
        for (int i = 0; i < datumt.u.arr.size; i++) {                      \
            const char* toml_str = datumt.u.arr.elem[i].u.s;              \
            config->field->values[i] = strdup(toml_str);                    \
            if (!config->field->values[i])                                  \
                error("strdup failed for " #field "[%d]\n", 0);           \
        }                                                                  \
    }


bool check_toml_string_array(toml_datum_t array){
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

void buildvarparse(toml_result_t result, CM_Build* config){
    toml_datum_t compiler = toml_seek(result.toptab, "build.compiler");
    toml_datum_t cflags   = toml_seek(result.toptab, "build.cflags");
    toml_datum_t includes = toml_seek(result.toptab, "build.includes");
    toml_datum_t libdirs = toml_seek(result.toptab, "build.libdirs");
    toml_datum_t libs = toml_seek(result.toptab, "build.libs");
    toml_datum_t srcs = toml_seek(result.toptab, "build.sources");

    if (compiler.type != TOML_STRING){
        error("Build Compiler not a String\n", 0);
    } else {
        config->compiler = (char*)compiler.u.s;
    }

    if (cflags.type != TOML_STRING){
        error("CFlags not a String\n", 0);
    } else {
        config->cflags = (char*)cflags.u.s;
    }

    FillFlexArray(includes, includes);
    FillFlexArray(libdirs, ldirs);
    FillFlexArray(libs, libs);
    FillFlexArray(srcs, sources);
}

void buildwritefile(FILE* out, CM_Build* config){
    fprintf(out, "CC ?= %s\n\n", config->compiler);
    fprintf(out, "CFLAGS += %s\n", config->cflags);
    fprintf(out, "CPPFLAGS += ");
    for (int i = 0; i < config->includes->count; i++){
        fprintf(out, "-I%s ", config->includes->values[i]);
    }
    fprintf(out, "\n");

    fprintf(out, "LDFLAGS += ");
    for (int i = 0; i < config->ldirs->count; i++){
        fprintf(out, "-L%s ", config->ldirs->values[i]);
    }
    fprintf(out, "\n");

    fprintf(out, "LDLIBS += ");
    for (int i = 0; i < config->libs->count; i++){
        fprintf(out, "-l%s ", config->libs->values[i]);
    }
    fprintf(out, "\n\n");

    fprintf(out, "SRCS = ");
    for (int i = 0; i < config->sources->count; i++){
        fprintf(out, "%s ", config->sources->values[i]);
    }
    fprintf(out, "\n");
}

void buildparse(FILE* out, toml_result_t result, CM_Build* config){
    buildvarparse(result, config);
    buildwritefile(out, config);
}