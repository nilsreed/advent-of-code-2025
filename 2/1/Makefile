# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://stackoverflow.com/questions/28559338/makefile-to-convert-all-c-to-o

CC=gcc
EXE_FILE=main.exe
SRC=main.c
OBJS=$(SRC:.c=.o)
CFLAGS=

all:$(EXE_FILE)

rebuild: clean all

debug: CFLAGS += -g
debug: $(EXE_FILE)

$(EXE_FILE): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJS): $(SRC)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	Del $(EXE_FILE) $(OBJS)