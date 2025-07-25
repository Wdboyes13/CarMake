#include "common.h"

void DoAllTests(ProjectInfo* info){
    chdir(info->TestInfo.TestFolderPath);
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    for (int i = 0; i < info->TestInfo.TestNames->count; i++){
        pid_t pid = fork();
        if (pid < 0){
            perror("Fork Failed");
            if (info->TestInfo.TestNames) free(info->TestInfo.TestNames);
            if (info) free(info);
            chdir("..");
            _exit(1);
        }
        if (pid == 0){
            char* filename = malloc(sizeof(char) * PATH_MAX);
            sprintf(filename, "%s/%s", cwd, info->TestInfo.TestNames->values[i]);
            char *argv[] = {filename, NULL};
            execve(filename, argv, environ);
            perror("Execve Failure");
            if (info->TestInfo.TestNames) free(info->TestInfo.TestNames);
            if (info) free(info);
            free(filename);
            chdir("..");
            _exit(1);
        } else {
            int status;
            waitpid(pid, &status, 0);
            status = WEXITSTATUS(status);
            printf("%s Exited with code %d\n", info->TestInfo.TestNames->values[i], status);
        }
    }
}