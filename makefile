
LDFLAGS= -L./src/linux -lplt

test:
	$(MAKE) -C test_app test

plt_lib:
	$(MAKE) -C src/linux plt_lib

clean:
	$(MAKE) -C test_app clean
	$(MAKE) -C src/linux clean
	rm lib/*


spi_test: test plt_lib
	$(CC) -o test_spi lib/test_spi.o $(LDFLAGS)
	mv test_spi ./lib/
i2c_test: test plt_lib
	$(CC) -o test_i2c lib/test_i2c.o $(LDFLAGS)
	mv test_i2c ./lib/
