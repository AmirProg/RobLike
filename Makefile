#### Makefile Projet C++ - ROBLIKE
#### CHALI Amir
#### BARBAROUX Leo-Paul


all:
	+$(MAKE) -C src -j4

clean:
	+$(MAKE) -C src clean

vclean: clean
	rm -f roblike
