#include "Common.h"
#include "Index.h"

void PrintInfo(const char* argv1){
    printf("Installed %s to /opt/carmake\n", argv1);
    printf("You may need to add /opt/carmake/lib/pkgconfig to PKG_CONFIG_PATH\n");
    printf("Do this with 'export PKG_CONFIG_PATH=\"/opt/carmake/lib/pkgconfig:$PKG_CONFIG_PATH\"'\n");
    printf("It is recommended to run the following as well\n");
    printf("'export CPPFLAGS=\"-I/opt/carmake/include $CPPFLAGS\"'\n");
    printf("'export LDFLAGS=\"-L/opt/carmake/lib $LDFLAGS\"'\n");
}

void ensure_dir(const char* path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
            printf("Directory '%s' exists.\n", path);
        } else {
            printf("'%s' exists but is not a directory!\n", path);
        }
    } else {
        // Directory doesn't exist, create it
        if (mkdir(path, 0755) == 0) {
            printf("Created directory '%s'\n", path);
        } else {
            perror("mkdir failed");
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Need pkg name\n");
        return 1;
    }
    const char* home = getenv("HOME");
    char indexdir[PATH_MAX];
    sprintf(indexdir, "%s/.cmpkg/", home);
    char indexpath[PATH_MAX];
    sprintf(indexpath, "%s/.cmpkg/packages.lua", home);
    ensure_dir(indexdir);
    DownloadFile("https://raw.githubusercontent.com/Wdboyes13/CarMake/master/cmpkg/srcs/Index.lua", indexpath);
    LoadPackageIndex(indexpath);

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
    
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    char cachedir[PATH_MAX];
    sprintf(cachedir, "%s/.cmpkg/cache", home);
    ensure_dir(cachedir);
    chdir(cachedir);

    if (access(pkgs[pkgindex].oname, F_OK)){
        printf("This packge was already installed\n");
        PrintInfo(argv[1]);
        chdir(cwd);
        return 0;
    }
    DownloadFile(pkgs[pkgindex].url, pkgs[pkgindex].urlbase);
    DecompressZst(pkgs[pkgindex].urlbase, pkgs[pkgindex].oname);
    DoFullBuild(pkgs[pkgindex].oname);

    chdir(cwd);
    PrintInfo(argv[1]);
    return 0;
}