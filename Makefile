CC:=gcc
CFLAGS:=-Wall -pedantic -ansi -g -O2

EP2: EP2.o matrix.o stack.o
	$(CC) $(CFLAGS) -o $@ $^

#General formulas for making objects

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o