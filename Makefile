####################################################
#
#  ISA 563, Spring 2010
#  Copyleft by Muhammad Abdulla
#
####################################################

# macros

CC=gcc
CFLAGS=-g -Wall

EXECUTABLES=myspeller

# targets
all: $(EXECUTABLES)

myspeller: MySpeller.c
	$(CC) $(CFLAGS) -o myspeller MySpeller.c

clean:
	rm -rf $(EXECUTABLES) *.o
