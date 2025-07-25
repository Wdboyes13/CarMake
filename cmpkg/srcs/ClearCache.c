#include "Common.h"

#ifdef _WIN32 
#define RMCMD "rmdir /s /q "
#else
#define RMCMD "rm -rf "
#endif

void DelPath(const char* path){
    char cmd[1024];
    sprintf(cmd, "%s %s", RMCMD, path);
    system(cmd);
}

void ClearCache(){
    const char* home = getenv("HOME");
    char indexdir[PATH_MAX];
    sprintf(indexdir, "%s/.cmpkg/", home);
    char indexpath[PATH_MAX];
    sprintf(indexpath, "%s/.cmpkg/packages.lua", home);
    ensure_dir(indexdir);
    char cachedir[PATH_MAX];
    sprintf(cachedir, "%s/.cmpkg/cache", home);
    ensure_dir(cachedir);

    DelPath(indexpath);
    DelPath(cachedir);

    exit(0);
}