COMPILE_OBJECT_FLAGS=-Wall -Wconversion -c

output: main.o bst.o
	g++ main.o bst.o -o output.out

main.o: src/main.cpp
	g++ $(COMPILE_OBJECT_FLAGS) src/main.cpp

bst.o: src/bst.cpp src/bst.hpp
	g++ $(COMPILE_OBJECT_FLAGS) src/bst.cpp

clean:
	rm *.o *.out
