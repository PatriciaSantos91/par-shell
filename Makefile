CC=gcc
TARGET = par-shell
CFLAGS= -c -g -ansi -Wall

SRCFILES = par-shell.c list.c commandlinereader.c
INCFILES = list.h commandlinereader.h
OBJFILES = par-shell.o list.o commandlinereader.o

default: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) -o $(TARGET) $(OBJFILES)

clean:
	rm -f $(TARGET) $(OBJFILES) core.* #*

%.o: %.c
	$(CC) -c $< -o $@