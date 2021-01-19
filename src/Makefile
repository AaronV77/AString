all:
	gcc -std=c99 -c astring.c 

debug:
	gcc -std=c99 -c astring.c -g

archive: all
	ar rcs astring.a astring.o

archive_debug: debug
	ar rcs astring.a astring.o

tester: all
	gcc -std=c99 -c astring.c
	gcc astring_tester.c astring.o -o tester

clean:
	rm -f *.o *.a *.out tester
