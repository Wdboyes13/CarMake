CC ?= clang
CPPFLAGS = -I./include
CFLAGS += -O2
LDFLAGS = -L./lib
LDLIBS = -ltomlc17
SRCS = srcs/BuildParse.c srcs/main.c srcs/PkgParse.c srcs/GenCommon.c srcs/Recurse.c
OUT = cm
OBJS := $(patsubst %.c,%.o,$(SRCS))
DESTDIR = /usr/local/bin/
REQLIBS = lib/libtomlc17.a

all: $(REQLIBS) $(OUT)

$(OUT): $(OBJS)
	@echo "[LD] $@"
	@$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
%.o: %.c 
	@echo "[CC] $<"
	@$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)

$(REQLIBS):
	@$(MAKE) -C libsrcs/tomlc17/src libtomlc17.a > /dev/null 2>&1 || exit 1
	cp libsrcs/tomlc17/src/libtomlc17.a ./lib/

clean:
	@echo "[RM] $(OUT) $(REQLIBS) $(OBJS)"
	@rm -f $(OUT) $(REQLIBS) $(OBJS)
	@$(MAKE) -C libsrcs/tomlc17/ clean > /dev/null 2>&1 || exit 1

install: $(OUT)
	@install -d -m 755 $(DESTDIR)
	@echo "[INSTALL] $(OUT)"
	@install -m 755 $(OUT) $(DESTDIR)/$(OUT)

.PHONY: all clean install