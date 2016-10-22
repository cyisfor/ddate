CC = gcc -std=gnu99
CFLAGS = -g -O2 -Wall -Wextra
CPP = gcc -std=gnu99 -E
CPPFLAGS = -g

PREFIX=/usr/local

all: ddate ddate.1.gz libddate.so test_libddate

ddate: main.o ddate.o
	$(CC) $(CFLAGS) $^ -o $@

libddate.so: ddate.c
	$(CC) -shared -fpic $(CFLAGS) $^ -o $@

test_libddate: libddate.so test_libddate.c
	$(CC) $(CFLAGS) -o $@ $^

ddate.1.gz: ddate.1

%.gz: %
	gzip -c $< >> $@.temp
	mv $@.temp $@

install: all
	mkdir -p $(PREFIX)/bin/
	mkdir -p $(PREFIX)/share/man/man1/
	cp ddate $(PREFIX)/bin/
	cp ddate.1.gz $(PREFIX)/share/man/man1/

.PHONY: all clean install
clean:
	git clean -fd
