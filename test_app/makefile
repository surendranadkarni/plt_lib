
CFLAGS=-I./../inc/ -I../cfg/ -Wall


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

test: test_spi.o 
	mkdir -p ../lib
	cp test_spi.o ../lib/

clean:
	rm -f  *.o
