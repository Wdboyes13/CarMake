#include "Common.h"

int main(int argc, char* argv[]){
    if (argc < 2){
        fprintf(stderr, "Need filename\n");
        return 1;
    }
    char* argv1 = strdup(argv[1]);
    char *ext = strstr(argv1, ".zst");
    if (ext && strcmp(ext, ".zst") == 0) {
        *ext = '\0';  // Truncate string at start of ".zst"
    }
    DecompressZst(argv[1], argv1);
    DoFullBuild(argv[1]);
    return 0;
}