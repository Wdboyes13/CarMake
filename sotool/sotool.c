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