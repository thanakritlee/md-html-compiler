testrunner: test/testrunner.c test/tokeniser/tokeniser-test-runner.o
	gcc test/testrunner.c -o testrunner test/tokeniser/tokeniser-test-runner.o source/tokeniser.o

test/tokeniser/tokeniser-test-runner.o: test/tokeniser/tokeniser-test-runner.c source/tokeniser.o
	gcc -c test/tokeniser/tokeniser-test-runner.c -o test/tokeniser/tokeniser-test-runner.o 

source/tokeniser.o: source/tokeniser.c
	gcc -c source/tokeniser.c -o source/tokeniser.o