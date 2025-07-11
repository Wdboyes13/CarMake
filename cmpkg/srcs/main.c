#include "Common.h"
#include "Index.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Need pkg name\n");
        return 1;
    }
    DownloadFile("https://raw.githubusercontent.com/Wdboyes13/CarMake/master/cmpkg/srcs/Index.lua", "packages.lua");
    LoadPackageIndex("packages.lua");

    int pkgindex = -1;
    for (int i = 0; i < pkgsnum; i++) {
        if (strcmp(pkgs[i].name, argv[1]) == 0) {
            pkgindex = i;
            break;
        }
    }

    if (pkgindex == -1) {
        fprintf(stderr, "Package '%s' not found\n", argv[1]);
        return 1;
    }

    DownloadFile(pkgs[pkgindex].url, pkgs[pkgindex].urlbase);
    DecompressZst(pkgs[pkgindex].urlbase, pkgs[pkgindex].oname);
    DoFullBuild(pkgs[pkgindex].oname);
    return 0;
}