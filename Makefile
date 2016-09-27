CC:=gcc
CFLAGS:=-Wall -pedantic -ansi -O2

ep2: restaUm.o matrix.o stack.o
	$(CC) $(CFLAGS) -o $@ $^

#General formulas for making objects

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.o
	rm -rf *.aux
	rm -rf *.log
	rm -rf *.dvi
	rm -rf *.synctex.gz