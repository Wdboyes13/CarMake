SUBDIRS = cm cmpkg sotool repotool

ifeq ($(INT),1)
build:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Internal.mk || exit 1; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean -f Internal.mk || exit 1; \
	done

install:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir install -f Internal.mk || exit 1; \
	done

.PHONY: build clean install

else

build:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir || exit 1; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean || exit 1; \
	done

install:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir install || exit 1; \
	done

.PHONY: build clean install
endif