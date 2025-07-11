OUT = cmpkg
CC ?= wclang

CFLAGS += 
CPPFLAGS += $(shell pkg-config --cflags lua) $(shell pkg-config --cflags libzstd) 
LDFLAGS += $(shell pkg-config --libs-only-L lua) $(shell pkg-config --libs-only-L libzstd) 
LDLIBS += $(shell pkg-config --libs-only-l lua) $(shell pkg-config --libs-only-l libzstd) 

SRCS = srcs/BuildParse.c srcs/GetMeta.c srcs/main.c srcs/DoFullBuild.c srcs/Decompressor.c 
OBJS := $(patsubst %.c,%.o,$(SRCS))
DESTDIR ?= /opt/will/bin

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
