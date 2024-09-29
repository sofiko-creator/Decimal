CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
CFLAGS_GCOV = $(CFLAGS) -fprofile-arcs -ftest-coverage

LIBRARY_FILE_A = s21_decimal.a

PREF_OBJ = obj
SRC = $(wildcard *.c)
OBJ =  $(patsubst %.c, $(PREF_OBJ)/%.o, $(SRC))

PREF_SRC_TEST = tests
PREF_OBJ_TEST = tests/obj
SRC_TEST = $(wildcard $(PREF_SRC_TEST)/*.c)
OBJ_TEST = $(patsubst $(PREF_SRC_TEST)/%.c, $(PREF_OBJ_TEST)/%.o, $(SRC_TEST))

PREF_SRC_NOT_FOR_VERTER_TEST = not_for_verter_tests
PREF_OBJECT_NOT_FOR_VERTER_TEST = not_for_verter_tests/obj
SRC_TEST_NFV = $(wildcard $(PREF_SRC_NOT_FOR_VERTER_TEST)/*.c)
OBJ_TEST_NFV = $(patsubst $(PREF_SRC_NOT_FOR_VERTER_TEST)/%.c, $(PREF_OBJECT_NOT_FOR_VERTER_TEST)/%.o, $(SRC_TEST_NFV))

PREF_OBJ_TEST_GCOV = tests/gcov
OBJ_GCOV = $(patsubst %.c, $(PREF_OBJ_TEST_GCOV)/%.o, $(SRC))

LIBS_CHECK = $(shell pkg-config --cflags --libs check) #-pthread -lcheck_pic -pthread -lrt -lm -lsubunit

all: $(LIBRARY_FILE_A) test gcov_report


test: $(LIBRARY_FILE_A) $(OBJ) $(OBJ_TEST)
	$(CC) $^ -o test $(LIBS_CHECK) -L. $(LIBRARY_FILE_A)

$(PREF_OBJ_TEST)/%.o: $(PREF_SRC_TEST)/%.c
	@mkdir -p $(PREF_OBJ_TEST)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBRARY_FILE_A): $(OBJ)
	ar rcs $(LIBRARY_FILE_A) $^
	ranlib $(LIBRARY_FILE_A)
	rm -rf *.o *.gch

$(PREF_OBJ)/%.o: %.c
	@mkdir -p $(PREF_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@


gcov_report:	
	make test_gcov
	./test_gcov
	lcov --directory . --capture --output Meow.info
	genhtml Meow.info --output CatReport
	open CatReport/index.html

test_gcov: $(OBJ_GCOV) $(OBJ_TEST)
	$(CC) $^ -o test_gcov $(LIBS_CHECK) -lgcov

$(PREF_OBJ_TEST_GCOV)/%.o: %.c
	@mkdir -p $(PREF_OBJ_TEST_GCOV)
	$(CC) $(CFLAGS_GCOV) -c $< -o $@


clean:
	rm -rf $(PREF_OBJ_TEST) $(PREF_OBJ) $(PREF_OBJ_TEST_GCOV) CatReport
	rm -rf test test_gcov Meow.info $(LIBRARY_FILE_A) test_not_for_verter.bin run
	rm -fr $(PREF_OBJECT_NOT_FOR_VERTER_TEST)
	rm -fr *.bin a.out .clang-format *.check tests/*.check

clang_format:
	cp ../materials/linters/.clang-format .
	clang-format -style=Google -i *.c *.h $(PREF_SRC_TEST)/*.c $(PREF_SRC_TEST)/*.h
	rm .clang-format

run_test:  $(LIBRARY_FILE_A) $(OBJ) $(OBJ_TEST)
	$(CC) $^ -o test.bin $(LIBS_CHECK) -L. $(LIBRARY_FILE_A) && ./test.bin

$(PREF_OBJECT_NOT_FOR_VERTER_TEST)/%.o: $(PREF_SRC_NOT_FOR_VERTER_TEST)/%.c
	@mkdir -p $(PREF_OBJECT_NOT_FOR_VERTER_TEST)
	$(CC) $(CFLAGS) -c $< -o $@
