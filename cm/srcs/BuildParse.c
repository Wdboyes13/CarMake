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

void buildvarparse(toml_result_t result, CM_Build* config){
    toml_datum_t compiler = toml_seek(result.toptab, "build.compiler");
    toml_datum_t cflags   = toml_seek(result.toptab, "build.cflags");
    toml_datum_t includes = toml_seek(result.toptab, "build.includes");
    toml_datum_t libdirs = toml_seek(result.toptab, "build.libdirs");
    toml_datum_t libs = toml_seek(result.toptab, "build.libs");
    toml_datum_t srcs = toml_seek(result.toptab, "build.sources");
    toml_datum_t ldflags = toml_seek(result.toptab, "build.ldflags");

    if (compiler.type != TOML_STRING){
        error("Build Compiler not found\n", 0);
    } else {
        config->BuildInfo.compiler = (char*)compiler.u.s;
    }

    if (cflags.type == TOML_STRING) {config->BuildInfo.cflags = (char*)cflags.u.s;} 
    else {config->BuildInfo.cflags = ""; };

    if (includes.type == TOML_ARRAY) FillFlexArray(includes, BuildInfo.includes);
    if (libdirs.type == TOML_ARRAY)  FillFlexArray(libdirs, BuildInfo.ldirs);
    if (libs.type == TOML_ARRAY)     FillFlexArray(libs, BuildInfo.libs);

    if (srcs.type == TOML_ARRAY) {FillFlexArray(srcs, BuildInfo.sources);}
    else error("Could not find sources\n", 0);

    if (ldflags.type == TOML_ARRAY) FillFlexArray(ldflags, BuildInfo.ldflags);
}

void buildwritefile(FILE* out, CM_Build* config){
    fprintf(out, "CC ?= %s\n\n", config->BuildInfo.compiler);
    if (config->BuildInfo.cflags) fprintf(out, "CFLAGS += %s\n", config->BuildInfo.cflags);
    fprintf(out, "CPPFLAGS += ");
    if (config->BuildInfo.includes) for (int i = 0; i < config->BuildInfo.includes->count; i++){
        fprintf(out, "$(shell pkg-config --cflags %s) ", config->BuildInfo.includes->values[i]);
    }
    fprintf(out, "\n");

    fprintf(out, "LDFLAGS += ");
    if (config->BuildInfo.ldirs) for (int i = 0; i < config->BuildInfo.ldirs->count; i++){
        fprintf(out, "$(shell pkg-config --libs-only-L %s) ", config->BuildInfo.ldirs->values[i]);
    }
    if (config->BuildInfo.ldflags) for (int i = 0; i < config->BuildInfo.ldflags->count; i++){
        fprintf(out, "-Wl,%s ", config->BuildInfo.ldflags->values[i]);
    }
    fprintf(out, "\n");

    fprintf(out, "LDLIBS += ");
    if (config->BuildInfo.libs) for (int i = 0; i < config->BuildInfo.libs->count; i++){
        fprintf(out, "$(shell pkg-config --libs-only-l %s) ", config->BuildInfo.libs->values[i]);
    }
    fprintf(out, "\n\n");

    fprintf(out, "SRCS = ");
    for (int i = 0; i < config->BuildInfo.sources->count; i++){
        fprintf(out, "%s ", config->BuildInfo.sources->values[i]);
    }
    fprintf(out, "\n");
}

void buildparse(FILE* out, toml_result_t result, CM_Build* config){
    buildvarparse(result, config);
    buildwritefile(out, config);
}