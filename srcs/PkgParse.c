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

#include "Common.h"

void pkgparse(FILE* out, toml_result_t result, CM_Build* config){
    // Get package metadata
    toml_datum_t pkgname = toml_seek(result.toptab, "package.name");
    toml_datum_t pkgtype = toml_seek(result.toptab, "package.type");

    // Check type
    if (pkgname.type != TOML_STRING){
        error("Missing package.name\n", 0);
    }
    if (pkgtype.type != TOML_STRING){
        error("Missing package.type\n", 0);
    }

    // Write Output Name
    if (strcmp(pkgtype.u.s, "exec") == 0) { 
        fprintf(out, "OUT = %s\n", pkgname.u.s); 
        config->name = (char*)pkgname.u.s;
        config->type = exec;
    }
    else if (strcmp(pkgtype.u.s, "alib") == 0) { 
        fprintf(out, "OUT = %s.a\n", pkgname.u.s);
        config->name = (char*)pkgname.u.s;
        config->type = alib;    
    } 
    else if (strcmp(pkgtype.u.s, "recurse") == 0){
        config->name = (char*)pkgname.u.s;
        config->type = recs;
    }
    else { fclose(out); error("Unknown Package Type\n", 0); }
}