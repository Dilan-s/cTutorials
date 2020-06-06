CC = gcc
CFLAGS = -Wall -g -pg
BUILD = command

all: $(BUILD)

clean :
	/bin/rm -f $(BUILD) *.o core *~

profile: ./command
	./command 3 60
	gprof command gmon.out > profile.orig

command: command.o
