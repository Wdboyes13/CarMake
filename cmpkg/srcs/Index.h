#pragma once


typedef struct Package {
    const char* url;
    const char* name;
    const char* oname;
    const char* urlbase;
} Package;

extern Package* pkgs;
extern int pkgsnum;