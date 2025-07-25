OUT = repotool
CC ?= clang

CFLAGS += -O2 -fsanitize=address
CPPFLAGS += $(shell pkg-config -cflags libgit2)
LDFLAGS += $(shell pkg-config --libs-only-L libgit2)  -L../cm/lib -fsanitize=address
LDLIBS += $(shell pkg-config --libs-only-l libgit2) -ltomlc17

SRCS = src/DoGit.c src/DoTests.c src/gitwrap.c src/Parser.c src/rtool.c
OBJS := $(patsubst %.c,%.o,$(SRCS))
DESTDIR ?= /usr/local/bin

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

install: $(OUT)
	install -d -m 755 $(DESTDIR)
	install -m 755 $(OUT) $(DESTDIR)/$(OUT)

.PHONY: install clean
