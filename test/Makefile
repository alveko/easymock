EASYMOCK = ..

GCC	= gcc
CFLAGS	+= -c -Wall
CFLAGS	+= -g -DDEBUG
CFLAGS	+= -I/usr/local/include -I./include -I./mocks -I$(EASYMOCK)/src

LDFLAGS	+= -Wl,--wrap=fopen
LDFLAGS	+= -Wl,--wrap=fclose
LDFLAGS	+= -Wl,--wrap=open
LDFLAGS	+= -Wl,--wrap=close

SRC	= test.c
SRC	+= $(EASYMOCK)/src/easymock.c
SRC	+= $(wildcard mocks/*.c)

OBJ	= $(SRC:.c=.o)
BIN	= test

.PHONY: all clean
all:	$(BIN)

$(BIN): $(OBJ)
	$(GCC) $(LDFLAGS) $(OBJ) -o $@

clean:
	rm -f $(BIN) $(OBJ)
	rm -rf mocks
