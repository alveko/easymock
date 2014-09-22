EASYMOCK = ..

GCC	= gcc
CFLAGS	+= -c -Wall
CFLAGS	+= -g -DDEBUG
CFLAGS	+= -I/usr/local/include -I./include -I./mocks -I$(EASYMOCK)/src

SRC	= test.c
SRC	+= $(EASYMOCK)/src/easymock.c
SRC	+= $(wildcard mocks/*.c)

OBJ	= $(SRC:.c=.o)
EXE	= test

.PHONY: all clean
all:	$(SRC) $(EXE)

$(EXE): $(OBJ)
	$(GCC) $(OBJ) -o $@ $(LDFLAGS)

.cc.o:
	$(GCC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXE) $(OBJ)
	rm -rf mocks
