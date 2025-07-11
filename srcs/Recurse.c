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
}

void MakeRecursiveMake(FILE* out, CM_Build* config){
    // Make SUBDIRS Variable
    fprintf(out, "SUBDIRS = ");
    for (int i = 0; i < config->RecurseInfo.subdirs->count; i++){
        fprintf(out, "%s", config->RecurseInfo.subdirs->values[i]);
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