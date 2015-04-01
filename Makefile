PREFIX 	= /usr/local
BINPATH = ${PREFIX}/bin
SRCS	= $(wildcard *.c)
BIN     = ${SRCS:.c=}

all: ${BIN}

${BIN}: ${SRCS}
	cc -g -std=c99 -pedantic -Wall -O0 -I. -I/usr/include -I/usr/local/include -Wl,-rpath=/usr/local/lib -L/usr/lib -lc -L/usr/local/lib -lrfi -o $@ $<

install: all
	@install -d ${BINPATH}
	@install -m 755 ${BIN} ${BINPATH}

uninstall:
	@rm -f ${BINPATH}/${BIN}

clean:
	@rm -f ${BIN}

.PHONY: all clean install uninstall
