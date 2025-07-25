#include <stdio.h>
#include <string.h>
#include <stdbool.h>
int main(int argc, char* argv[]){
    bool cflags = false;
    bool ldflags = false;
    if (argc < 2){
        fprintf(stderr, "Please pass either -cflags or -ldflags\n");
        return 1;
    }
    for (int i = 0; i < argc; i++){
        if (strcmp("-cflags", argv[i]) == 0){
            cflags = true;
        }
        if (strcmp("-ldflags", argv[i]) == 0){
            ldflags = true;
        }
        if (strcmp("--help", argv[i]) == 0 || strcmp("-h", argv[i]) == 0){
            printf("For CFLAGS - -cflags\n");
            printf("For LDFLAGS - -ldflags And in your makefile, without following space, the libname\n");
            printf("For help - --help or -h\n");
            printf("Makefile example\n");
            printf("CFLAGS := $(shell sotool -cflags)\nLDFLAGS := $(shell sotool -ldflags)test.dylib\n");
            return 0;
        }
    }
    if (!ldflags && !cflags){
        fprintf(stderr, "Please pass either -cflags or -ldflags\n");
        return 1;
    }
#    ifdef __APPLE__
         if (cflags){
            printf("-fPIC\n");
         }
         if (ldflags){
            printf("-dynamiclib -install_name @rpath/\n");
         }
#    elif defined(__linux__)
         if (cflags){
            printf("-fPIC\n");
         }
         if (ldflags){
            printf("-shared -Wl,-soname,\n");
         }
#    elif defined(_WIN32)
         printf("Windows is currently unsupported\n");
#    endif

}