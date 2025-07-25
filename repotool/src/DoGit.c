#include "common.h"

void DoAllGit(ProjectInfo* info){
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    char buf[128];
    strftime(buf, sizeof(buf), "%a %d %b %Y %T %Z", local);

    gitinit();
    stageall();

    char* msg = malloc(sizeof(char) * 512);
    sprintf(msg, "Updated at: %s", buf);

    commit(info->GitInfo.AuthMail, info->GitInfo.AuthName, msg);
    pushmain(info->GitInfo.RemName, info->GitInfo.LocName);
}