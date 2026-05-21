OBJS = source/tokeniser.o source/parser.o source/buffer.o source/fileio.o
HEADS = source/tokeniser.h source/buffer.h source/parser.h source/fileio.h

TEST_OBJS = test/common.o test/tokeniser/tokeniser-test-runner.o test/tokeniser/heading.o test/tokeniser/space-and-tab.o \
			test/tokeniser/newline-and-eof.o test/tokeniser/string.o test/tokeniser/number.o test/tokeniser/special-character.o \
			test/parser/parser-test-runner.o test/parser/heading.o test/parser/paragraph.o test/parser/combination.o \
			test/parser/image.o test/parser/code.o test/parser/list.o test/buffer/buffer-test-runner.o test/buffer/buffer.o
TEST_HEADS = test/tokeniser/tokeniser-test-runner.h test/parser/parser-test-runner.h test/buffer/buffer-test-runner.h \
			 test/common.h test/tokeniser/heading.h test/tokeniser/space-and-tab.h test/tokeniser/newline-and-eof.h \
			 test/tokeniser/string.h test/tokeniser/number.h test/tokeniser/special-character.h test/parser/heading.h \
			 test/parser/paragraph.h test/parser/combination.h test/parser/image.h test/parser/code.h test/parser/list.h \
			 test/buffer/buffer.h

testrunner: test/testrunner.c $(OBJS) $(TEST_OBJS) $(TEST_HEADS)
	gcc test/testrunner.c -o testrunner $(OBJS) $(TEST_OBJS)

compiler: source/main.c $(OBJS) $(HEADS)
	gcc source/main.c -o compiler $(OBJS)

clean:
	rm -f compiler testrunner
