#include "Common.h"
#include "Index.h"

int main(int argc, char* argv[]){
    if (argc < 2){
        fprintf(stderr, "Need pkg name\n");
        return 1;
    }
    int pkgindex = -1;
    for (int i = 0; i < pkgsnum; i++){
        if (strcmp(pkgs[i].name, argv[1]) == 0){
            pkgindex = i;
        }
    }

    DownloadFile(pkgs[pkgindex].url, pkgs[pkgindex].urlbase);
    DecompressZst(pkgs[pkgindex].urlbase, pkgs[pkgindex].oname);
    DoFullBuild(pkgs[pkgindex].oname);
    return 0;
}