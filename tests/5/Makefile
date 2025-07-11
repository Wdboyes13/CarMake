OUT = test.a
CC ?= clang

CFLAGS += 
CPPFLAGS += 
LDFLAGS += 
LDLIBS += 

SRCS = main.c 
OBJS := $(patsubst %.c,%.o,$(SRCS))
DESTDIR ?= /opt/will/lib/

$(OUT): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(CPPFLAGS)

clean:
	rm -f $(OBJS) $(OUT)

install: $(OUT)
	install -d -m 755 $(DESTDIR)
	install -m 755 $(OUT) $(DESTDIR)/$(OUT)

.PHONY: install clean
