#include "common.h"

int main(int argc, char* argv[]){
    bool dogit = true;
    bool dotsts = true;
    for (int i = 0; i < argc; i++){
        if (strcmp("-ng", argv[i]) == 0) dogit = false;
        if (strcmp("-nt", argv[i]) == 0) dotsts = false;
    }
    if (access(".git", F_OK) != -1) {
        dogit = true;
    } else {
        dogit = false;
    }
    ProjectInfo* info = malloc(sizeof(ProjectInfo));
    Parse(info);
    if (dotsts) DoAllTests(info);
    if (dogit) DoAllGit(info);
    if (info) free(info);
    return 0;
}