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

void PrintVer(){
    printf("CarMake %s\n", CM_VER);
    printf("Copyright (C) 2025 Wdboyes13\n");
    printf("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>\n");
    printf("This is free software: you are free to change and redistribute it.\n");
    printf("There is NO WARRANTY, to the extent permitted by law\n");
    exit(0);
}

void Usage(){
    printf("Usage: cm [options]\n");
    printf("Options:\n");
    printf("    -f [filename]  - Set input file to [filename]\n");
    printf("    -o [filename]  - Set output file to [filename]\n");
    printf("    --run          - Immediatly Run Make After\n");
    printf("    -C [dirname]   - Run from [dirname]\n");
    printf("    -v | --version - Print version\n");
    printf("    -h | --help    - Print This\n");
    exit(0);
}

int main(int argc, char* argv[]){
    char* file = "cm.toml";
    char* ofile = "Makefile";
    bool dorun = false;
    bool didswitch = false;
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "-f") == 0) file = argv[++i];
        else if (strcmp(argv[i], "-o") == 0) ofile = argv[++i];
        else if (strcmp(argv[i], "-C") == 0) {
            chdir(argv[++i]);
            didswitch = true;
        }
        else if (strcmp(argv[i], "--run") == 0) dorun = true;
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) PrintVer();
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) Usage();
        else {
            printf("Unknown Arguement: %s\n", argv[i]);
            Usage();
        }
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

    if (dorun) {
        execlp("make", "make", NULL);
        perror("Run Make Failed\n");
    }
    if (didswitch){
        chdir("..");
    }
    return 0;
}