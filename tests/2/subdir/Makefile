OUT = test2sub
CC ?= clang

CFLAGS += -O2 -Wall
CPPFLAGS += $(shell pkg-config --cflags gmp) 
LDFLAGS += $(shell pkg-config --libs-only-L gmp) 
LDLIBS += $(shell pkg-config --libs-only-l gmp) 

SRCS = main.c file2.c 
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
