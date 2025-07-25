OUT = cmpkg
CC ?= clang

CFLAGS += -O2
CPPFLAGS += $(shell pkg-config --cflags lua) $(shell pkg-config --cflags libzstd) $(shell pkg-config --cflags libcurl)
LDFLAGS += $(shell pkg-config --libs-only-L lua) $(shell pkg-config --libs-only-L libzstd) $(shell pkg-config --libs-only-L libcurl)
LDLIBS += $(shell pkg-config --libs-only-l lua) $(shell pkg-config --libs-only-l libzstd) $(shell pkg-config --libs-only-l libcurl)

SRCS = srcs/BuildParse.c srcs/GetMeta.c srcs/main.c srcs/DoFullBuild.c srcs/Decompressor.c srcs/Downloader.c srcs/LoadIndex.c srcs/ClearCache.c
OBJS := $(patsubst %.c,%.o,$(SRCS))
DESTDIR ?= /usr/local/bin

$(OUT): $(OBJS)
	@echo "[LD] $@"
	@$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

clean:
	@echo "[RM] $(OBJS) $(OUT)"
	@rm -f $(OBJS) $(OUT)

install: $(OUT)
	@install -d -m 755 $(DESTDIR)
	@echo "[INSTALL] $(OUT)"
	@install -m 755 $(OUT) $(DESTDIR)/$(OUT)

.PHONY: install clean
