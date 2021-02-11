project = simpletest

objs  = $(project).o optMultiplication.o naiveMultiplication.o
files = $(project).c

CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -O3 -g2

.PHONY: all

all: $(project)

$(project): $(objs)
	$(CC) $(CFLAGS) -o $(project) $(objs)

.PHONY: clean
clean:
	rm -f $(project)
	rm -f $(objs)
