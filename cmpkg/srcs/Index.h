#pragma once


typedef struct Package {
    const char* url;
    const char* name;
    const char* oname;
    const char* urlbase;
} Package;

static Package pkgs[] = {
    { 
            .url = "https://raw.githubusercontent.com/Wdboyes13/CarMake/master/cmpkgroot/comp/libmicrohttpd.lua.zst", 
            .name = "libmicrohttpd",
            .oname = "libmicrohttpd.lua",
            .urlbase = "libmicrohttpd.lua.zst"
        }
};

static int pkgsnum = 1;