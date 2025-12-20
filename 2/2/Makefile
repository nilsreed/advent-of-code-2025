# https://cs.colby.edu/maxwell/courses/tutorials/maketutor/
# https://stackoverflow.com/questions/28559338/makefile-to-convert-all-c-to-o

CC=gcc
SRC=main.c
OBJS=$(SRC:.c=.o)
CFLAGS=
LDLIBS=-lm

ifeq ($(OS),Windows_NT)
	EXE_FILE=main.exe
	RM_COMMAND=Del
else
	UNAME := $(shell uname -s)
	ifeq ($(UNAME),Linux)
		EXE_FILE=main
		RM_COMMAND=rm
	else
		$(error Unsupported OS)
	endif
endif


all:$(EXE_FILE)

rebuild: clean all

debug: CFLAGS += -g
debug: $(EXE_FILE)

$(EXE_FILE): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS)

$(OBJS): $(SRC)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	$(RM_COMMAND) $(EXE_FILE) $(OBJS)
