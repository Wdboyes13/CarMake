OUT = cmpkg
CC ?= wclang

CFLAGS += -O2
CPPFLAGS = -I/opt/will/include
LDFLAGS = -L../privlibs
LDLIBS =  -framework LDAP -lz -framework CoreFoundation -framework CoreServices \
		 -framework SystemConfiguration -lall

SRCS = srcs/BuildParse.c srcs/GetMeta.c srcs/main.c srcs/DoFullBuild.c srcs/Decompressor.c srcs/Downloader.c srcs/LoadIndex.c
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
