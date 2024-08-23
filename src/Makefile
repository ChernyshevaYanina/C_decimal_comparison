CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11 
VALGRIND=valgrind --leak-check=full --leak-resolution=med -s
OS:= $(shell uname -s)
LINFLAGS=-lcheck -pthread -lrt -lm -lsubunit
SRCFILE = comparison.c
OBJECTS = comparison.o

all: clean test 

decimal.a:
	$(CC) $(CFLAGS) -c $(SRCFILE)
	@ar rcs comparison.a $(OBJECTS)
	ranlib comparison.a

test: decimal.a
ifeq ($(OS), Darwin)
	gcc test.c comparison.a  -o test `pkg-config --cflags --libs check` -lcheck -lpthread 
	./test
	rm -rf *.o *.a 
else
	gcc test.c comparison.a -o test $(LINFLAGS)
	./test
	rm -rf *.o *.a 
endif

gcov_report: clean
ifeq ($(OS), Darwin)
	gcc --coverage test.c -o test $(SRCFILE) -lcheck
	./test
	gcov -f comparison.gcda
	lcov -t "test" -o test.info -c -d .   
	genhtml -o report test.info
	open ./report/index.html
else
	gcc --coverage test.c -o test $(SRCFILE) $(LINFLAGS)
	./test
	gcov -f comparison.gcda
	lcov -t "test" -o test.info -c -d .  
	genhtml -o report test.info
	xdg-open ./report/index.html
endif

check: clean cppcheck style leaks

cppcheck: test
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h


style: test
	cp ../materials/linters/.clang-format .clang-format 
	clang-format -style=google -i *.c *.h
	clang-format -style=google -n *.c *.h
	rm .clang-format 

leaks: test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./test
	rm -rf decimal.o
else
	#sudo dnf install valgrind
	#$(VALGRIND) --leak-check=full --show-leak-kinds=all ./test
	rm -rf decimal.o
endif

clean:
	-rm -rf *.o && rm -rf *.gcno && rm -rf *.exec
	-rm -rf *.a && rm -rf *.gcda
	-rm -rf *.info && rm -rf *.gcov
	-rm -rf ./gcov_report
	-rm -rf ./run_tests ./test 
	-rm -rf ./report/
	-rm -rf *.log
