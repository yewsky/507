all: libmd5_a

libmd5_a : md5.c md5-private.c
	gcc -c md5.c -o md5.o
	gcc -c md5-private.c -o md5-private.o
	ar r libmd5.a md5.o md5-private.o

install: libmd5_a
	cp libmd5.a ../lib/

