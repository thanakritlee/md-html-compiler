testrunner: test/testrunner.c test/common.o \
			test/tokeniser/tokeniser-test-runner.o \
			source/tokeniser.o \
			test/tokeniser/heading.o \
			test/tokeniser/space-and-tab.o \
			test/tokeniser/newline-and-eof.o \
			test/tokeniser/string.o \
			test/tokeniser/number.o
	gcc test/testrunner.c -o testrunner \
	source/tokeniser.o test/common.o test/tokeniser/tokeniser-test-runner.o \
	test/tokeniser/heading.o test/tokeniser/space-and-tab.o \
	test/tokeniser/newline-and-eof.o test/tokeniser/string.o \
	test/tokeniser/number.o

test/tokeniser/tokeniser-test-runner.o: test/tokeniser/tokeniser-test-runner.c
	gcc -c test/tokeniser/tokeniser-test-runner.c -o test/tokeniser/tokeniser-test-runner.o 

test/common.o: test/common.c
	gcc -c test/common.c -o test/common.o

test/tokeniser/heading.o: test/tokeniser/heading.c
	gcc -c test/tokeniser/heading.c -o test/tokeniser/heading.o

test/tokeniser/space-and-tab.o: test/tokeniser/space-and-tab.c
	gcc -c test/tokeniser/space-and-tab.c -o test/tokeniser/space-and-tab.o

test/tokeniser/newline-and-eof.o: test/tokeniser/newline-and-eof.c
	gcc -c test/tokeniser/newline-and-eof.c -o test/tokeniser/newline-and-eof.o

test/tokeniser/string.o : test/tokeniser/string.c
	gcc -c test/tokeniser/string.c -o test/tokeniser/string.o

test/tokeniser/number.o : test/tokeniser/number.c
	gcc -c test/tokeniser/number.c -o test/tokeniser/number.o

source/tokeniser.o: source/tokeniser.c
	gcc -c source/tokeniser.c -o source/tokeniser.o