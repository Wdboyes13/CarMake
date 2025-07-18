CC ?= wclang
CPPFLAGS = -I./include
CFLAGS = -O2
LDFLAGS = -L./lib
LDLIBS = -ltomlc17
SRCS = srcs/BuildParse.c srcs/main.c srcs/PkgParse.c srcs/GenCommon.c srcs/Recurse.c
OUT = cm
OBJS := $(patsubst %.c,%.o,$(SRCS))
DESTDIR = /opt/will/bin
REQLIBS = lib/libtomlc17.a

all: $(REQLIBS) $(OUT)

$(OUT): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)
%.o: %.c 
	$(CC) -o $@ -c $< $(CFLAGS) $(CPPFLAGS)

$(REQLIBS):
	$(MAKE) -C libsrcs/tomlc17/src libtomlc17.a || exit 1
	cp libsrcs/tomlc17/src/libtomlc17.a ./lib/

clean:
	rm -f $(OUT) $(REQLIBS) $(OBJS)
	$(MAKE) -C libsrcs/tomlc17/src clean

install: $(OUT)
	install -d -m 755 $(DESTDIR)
	install -m 755 $(OUT) $(DESTDIR)/$(OUT)

.PHONY: all clean install