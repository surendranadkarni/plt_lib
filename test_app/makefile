
CFLAGS=-I./../inc/ -I../cfg/ -Wall


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

test: test_spi.o test_i2c.o 
	mkdir -p ../lib
	cp test_spi.o test_i2c.o ../lib/

clean:
	rm -f  *.o
