SUBDIRS = cm cmpkg sotool repotool


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