all: numgen fork thread

CC = gcc
FLAG = -pthread

numgen: numgen.c
	$(CC) -o $@ $<

fork: fork.c
	$(CC) -o $@ $<

thread: thread.c
	$(CC) -o $@ $< $(FLAG)

