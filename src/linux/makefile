CFLAGS=-I../../inc -g -Wall


%.o: %.c 
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f *.a

plt_lib: plt_spi.o plt_lib.o
	$(AR) rcs libplt.a plt_spi.o plt_lib.o
	cp libplt.a ../../lib/
