CC=gcc

LDFLAGS= -L./src/linux -lplt

test:
	$(MAKE) -C test_app test

plt_lib:
	$(MAKE) -C src/linux plt_lib

clean:
	$(MAKE) -C test_app clean
	$(MAKE) -C src/linux clean
	rm lib/*


all: test plt_lib
	gcc -o test_plt lib/test.o $(LDFLAGS)
	mv test_plt ./lib/