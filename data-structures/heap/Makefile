COMPILE_OBJECT_FLAGS=-Wall -Wconversion -c

output: main.o heap.o
	g++ main.o heap.o -o output

main.o: src/main.cpp
	g++ $(COMPILE_OBJECT_FLAGS) src/main.cpp

heap.o: src/heap.cpp src/heap.h
	g++ $(COMPILE_OBJECT_FLAGS) src/heap.cpp

clean:
	rm *.o output
