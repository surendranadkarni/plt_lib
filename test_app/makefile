
CFLAGS=-I./../inc/


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

test: test.o 
	cp test.o ../lib/

clean:
	rm -f  *.o
