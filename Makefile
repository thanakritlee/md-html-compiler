testrunner: test/testrunner.c test/common.o \
			test/tokeniser/tokeniser-test-runner.o \
			source/tokeniser.o \
			test/tokeniser/heading.o \
			test/tokeniser/space-and-tab.o \
			test/tokeniser/newline-and-eof.o \
			test/tokeniser/string.o \
			test/tokeniser/number.o \
			test/parser/parser-test-runner.o \
			test/parser/heading.o \
			source/parser.o \
			source/buffer.o \
			test/buffer/buffer-test-runner.o \
			test/buffer/buffer.o
	gcc test/testrunner.c -o testrunner \
	source/tokeniser.o test/common.o test/tokeniser/tokeniser-test-runner.o \
	test/tokeniser/heading.o test/tokeniser/space-and-tab.o \
	test/tokeniser/newline-and-eof.o test/tokeniser/string.o \
	test/tokeniser/number.o test/parser/parser-test-runner.o \
	test/parser/heading.o source/parser.o source/buffer.o \
	test/buffer/buffer-test-runner.o test/buffer/buffer.o

test/tokeniser/tokeniser-test-runner.o: test/tokeniser/tokeniser-test-runner.c test/tokeniser/tokeniser-test-runner.h
	gcc -c test/tokeniser/tokeniser-test-runner.c -o test/tokeniser/tokeniser-test-runner.o 

test/parser/parser-test-runner.o: test/parser/parser-test-runner.c test/parser/parser-test-runner.h
	gcc -c test/parser/parser-test-runner.c -o test/parser/parser-test-runner.o

test/buffer/buffer-test-runner.o: test/buffer/buffer-test-runner.c test/buffer/buffer-test-runner.h
	gcc -c test/buffer/buffer-test-runner.c -o test/buffer/buffer-test-runner.o

test/common.o: test/common.c test/common.h
	gcc -c test/common.c -o test/common.o

test/tokeniser/heading.o: test/tokeniser/heading.c test/tokeniser/heading.h
	gcc -c test/tokeniser/heading.c -o test/tokeniser/heading.o

test/tokeniser/space-and-tab.o: test/tokeniser/space-and-tab.c test/tokeniser/space-and-tab.h
	gcc -c test/tokeniser/space-and-tab.c -o test/tokeniser/space-and-tab.o

test/tokeniser/newline-and-eof.o: test/tokeniser/newline-and-eof.c test/tokeniser/newline-and-eof.h
	gcc -c test/tokeniser/newline-and-eof.c -o test/tokeniser/newline-and-eof.o

test/tokeniser/string.o: test/tokeniser/string.c test/tokeniser/string.h
	gcc -c test/tokeniser/string.c -o test/tokeniser/string.o

test/tokeniser/number.o: test/tokeniser/number.c test/tokeniser/number.h
	gcc -c test/tokeniser/number.c -o test/tokeniser/number.o

test/parser/heading.o: test/parser/heading.c test/parser/heading.h
	gcc -c test/parser/heading.c -o test/parser/heading.o

test/buffer/buffer.o: test/buffer/buffer.c test/buffer/buffer.h
	gcc -c test/buffer/buffer.c -o test/buffer/buffer.o

source/tokeniser.o: source/tokeniser.c source/tokeniser.h
	gcc -c source/tokeniser.c -o source/tokeniser.o

source/buffer.o: source/buffer.c source/buffer.h
	gcc -c source/buffer.c -o source/buffer.o

source/parser.o: source/parser.c source/parser.h
	gcc -c source/parser.c -o source/parser.o