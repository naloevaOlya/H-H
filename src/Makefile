CC=g++ -std=c++17 -g
BD=./
CFLAGS=-c

all: clean main

/$(BD)%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

run:
	./main	

cpplint:
	cp ../materials/linters/CPPLINT.cfg . && python3 ../materials/linters/cpplint.py --extensions=cpp *.hpp *.cpp

clean:
	rm -rf *.o *.a *.out *.dSYM *_exe  main *.cfg
	rm -rf *.gcno *.gcda *.info report/