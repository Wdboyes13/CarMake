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

int main(int argc, char* argv[]){
    char* file = "cm.toml";
    char* ofile = "Makefile";
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-f") == 0) file = argv[++i];
        if (strcmp(argv[i], "-o") == 0) ofile = argv[++i];
        else printf("Unknown Arguement: %s\n", argv[i]);
    }

    toml_result_t result = toml_parse_file_ex(file);
    if (!result.ok){
        error(result.errmsg, 0);
    }
    
    FILE* out = fopen(ofile, "w");
    if (!out) { error("Failed to create Makefile\n", 0); return 1; }

    CM_Build* config = malloc(sizeof(CM_Build));

    pkgparse(out, result, config);
    if (config->PkgInfo.type != recs){
        buildparse(out, result, config);
        GenCommonRules(out, config);
        if (config->BuildInfo.includes) free(config->BuildInfo.includes);
        if (config->BuildInfo.ldirs) free(config->BuildInfo.ldirs);
        if (config->BuildInfo.libs) free(config->BuildInfo.libs);
        if (config->BuildInfo.sources) free(config->BuildInfo.sources);
    } else {
        GenRecurseBuild(out, result, config);
        if (config->RecurseInfo.subdirs) free (config->RecurseInfo.subdirs);
    }
    if (config) free(config);

    return 0;
}