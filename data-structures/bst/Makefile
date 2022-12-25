COMPILE_OBJECT_FLAGS=-Wall -Wconversion -c

output: main.o bst.o iterator.o node.o
	g++ main.o bst.o iterator.o node.o -o output.out

main.o: src/main.cpp
	g++ $(COMPILE_OBJECT_FLAGS) src/main.cpp

bst.o: src/bst.cpp src/bst.hpp
	g++ $(COMPILE_OBJECT_FLAGS) src/bst.cpp

iterator.o: src/iterator.cpp src/iterator.hpp
	g++ $(COMPILE_OBJECT_FLAGS) src/iterator.cpp

node.o: src/node.cpp src/node.hpp
	g++ $(COMPILE_OBJECT_FLAGS) src/node.cpp

clean:
	rm *.o *.out
