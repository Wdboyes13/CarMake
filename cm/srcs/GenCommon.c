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

void GenCommonRules(FILE* out, CM_Build* config){
    // Common Variables
    fprintf(out, "OBJS := $(patsubst %%.c,%%.o,$(SRCS))\n");
    fprintf(out, "DESTDIR ?= %s\n\n", config->PkgInfo.installdir);

    // Linking Rule
    fprintf(out, "$(OUT): $(OBJS)\n");
    if (config->PkgInfo.type == alib) fprintf(out, "\tar rcs $@ $^\n\n");
    else fprintf(out, "\t$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)\n\n");

    // Compiling Rule
    fprintf(out, "%%.o: %%.c\n");
    fprintf(out, "\t$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)\n\n");

    // Clean Rule
    fprintf(out, "clean:\n");
    fprintf(out, "\trm -f $(OBJS) $(OUT)\n\n");

    // Install Rule
    fprintf(out, "install: $(OUT)\n");
    fprintf(out, "\tinstall -d -m 755 $(DESTDIR)\n");
    fprintf(out, "\tinstall -m 755 $(OUT) $(DESTDIR)/$(OUT)\n\n");

    // Mark install & clean as .PHONY
    fprintf(out, ".PHONY: install clean\n");
}