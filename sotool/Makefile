OUT = sotool
CC ?= clang

CFLAGS += -O2

SRCS = sotool.c
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
