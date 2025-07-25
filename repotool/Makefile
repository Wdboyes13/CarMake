OUT = repotool
CC ?= clang

CFLAGS += -O2 -Wno-deprecated-declarations
CPPFLAGS += $(shell pkg-config -cflags libgit2)
LDFLAGS += $(shell pkg-config --libs-only-L libgit2)  -L../cm/lib
LDLIBS += $(shell pkg-config --libs-only-l libgit2) -ltomlc17

SRCS = src/DoGit.c src/DoTests.c src/gitwrap.c src/Parser.c src/rtool.c
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
