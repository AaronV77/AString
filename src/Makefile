
all:
	gcc -c astring.c 
	gcc astring_tester.c astring.o

debug:
	gcc -c astring.c -g
	gcc astring_tester.c astring.o

archive:
	gcc -c astring.c
	ar rcs astring.o 

archive_debug:
	gcc -c astring.c -gcc
	ar rcs astring.o
	
clean:
	rm *.o *.a
