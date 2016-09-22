CC:=gcc
CFLAGS:=-Wall -pedantic -O2 -ansi

EP2: EP2.o matrix.o stack.o
	$(CC) $(CFLAGS) -o $@ $^

#General formulas for making objects

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o