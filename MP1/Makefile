CC=gcc
CFLAGS=-W -Wall -ansi -pedantic
LDFLAGS=
EXEC=mishell
MAIN=main

all: $(EXEC)

$(EXEC): $(MAIN).o shell.o print.o command.o separators.o pipe_command.o
	$(CC) -o $(@) $(MAIN).o shell.o print.o command.o separators.o pipe_command.o $(LDFLAGS)

$(MAIN).o: $(MAIN).c header.h
	$(CC) -o $(@) -c $(MAIN).c $(CFLAGS)

shell.o: shell.c
	$(CC) -o $(@) -c shell.c $(CFLAGS)

print.o: print.c
	$(CC) -o $(@) -c print.c $(CFLAGS)

command.o: command.c
	$(CC) -o $(@) -c command.c $(CFLAGS)

separators.o: separators.c
	$(CC) -o $(@) -c separators.c $(CFLAGS)

pipe_command.o: pipe_command.c
	$(CC) -o $(@) -c pipe_command.c $(CFLAGS)

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)
