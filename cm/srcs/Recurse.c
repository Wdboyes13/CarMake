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

void RecurseGen(CM_Build* config){
    // Loop through subdirs, run CarMake in each
    for (int i = 0; i < config->RecurseInfo.subdirs->count; i++){
        if (chdir(config->RecurseInfo.subdirs->values[i]) != 0) {
            perror("Failed to enter subdir");
            continue;
        }
        pid_t pid = fork();
        if (pid == 0){
            execlp("CarMake", "CarMake", NULL);
            perror("Execlp Failed\n");
            exit(1);
        } else {
            wait(NULL);
        }
        chdir("..");
    }
}

void GetSubdirs(CM_Build* config, toml_result_t result){
    toml_datum_t subdirs = toml_seek(result.toptab, "package.subdirs");
    FillFlexArray(subdirs, RecurseInfo.subdirs);
    if (!config->RecurseInfo.subdirs) error("Expecered package.subdirs", 0);
}

void MakeRecursiveMake(FILE* out, CM_Build* config){
    // Make SUBDIRS Variable
    fprintf(out, "SUBDIRS = ");
    for (int i = 0; i < config->RecurseInfo.subdirs->count; i++){
        fprintf(out, "%s ", config->RecurseInfo.subdirs->values[i]);
    }
    
    // Build all subdirs
    fprintf(out, "\n\n");
    fprintf(out, "build:\n");
    fprintf(out, "\t@for dir in $(SUBDIRS); do \\\n");
    fprintf(out, "\t\t$(MAKE) -C $$dir || exit 1; \\\n");
    fprintf(out, "\tdone\n\n");

    // Clean all subdirs
    fprintf(out, "clean:\n");
    fprintf(out, "\t@for dir in $(SUBDIRS); do \\\n");
    fprintf(out, "\t\t$(MAKE) -C $$dir clean || exit 1; \\\n");
    fprintf(out, "\tdone\n\n");

    // Install all subdirs
    fprintf(out, "install:\n");
    fprintf(out, "\t@for dir in $(SUBDIRS); do \\\n");
    fprintf(out, "\t\t$(MAKE) -C $$dir install || exit 1; \\\n");
    fprintf(out, "\tdone\n\n");

    // Mark build & clean & install as .PHONY
    fprintf(out, ".PHONY: build clean install");
}

void GenRecurseBuild(FILE* out, toml_result_t result, CM_Build* config){
    GetSubdirs(config, result);
    RecurseGen(config);
    MakeRecursiveMake(out, config);
}