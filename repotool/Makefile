OUT = repotool
CC ?= clang

CFLAGS += -O2 -Wno-deprecated-declarations
CPPFLAGS += $(shell pkg-config -cflags libgit2)
LDFLAGS += $(shell pkg-config --libs-only-L libgit2)  -L../cm/lib
LDLIBS += $(shell pkg-config --libs-only-l libgit2) -ltomlc17

SRCS =  src/DoTests.c src/Parser.c src/rtool.c

GSRCS = src/DoGit.c src/gitwrap.c

OBJS := $(patsubst %.c,%.o,$(SRCS))
GOBJS := $(patsubst %.c,%.o,$(GSRCS))
DESTDIR ?= /usr/local/bin

$(OUT): librepotool.a librtgit.a
	@echo "[LD] $@"
	@$(CC) -o $@ $(LDFLAGS) -L. -lrepotool -lrtgit $(LDLIBS)

librepotool.a: $(OBJS)
	@echo "[AR] $@"
	@ar rcs $@ $^

librtgit.a: $(GOBJS)
	@echo "[AR] $@"
	@ar rcs $@ $^

%.o: %.c
	@echo "[CC] $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

clean:
	@echo "[RM] $(OBJS) $(OUT)"
	@rm -f $(OBJS) $(OUT) $(GOBJS) librepotool.a librtgit.a

install: $(OUT)
	@install -d -m 755 $(DESTDIR)
	@echo "[INSTALL] $(OUT)"
	@install -m 755 $(OUT) $(DESTDIR)/$(OUT)

.PHONY: install clean
