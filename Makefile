testrunner: test/testrunner.c source/tokeniser.o
	gcc test/testrunner.c -o testrunner source/tokeniser.o

source/tokeniser.o: source/tokeniser.h source/tokeniser.c
	gcc -c source/tokeniser.c -o source/tokeniser.o