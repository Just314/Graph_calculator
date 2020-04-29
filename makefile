output: main.o cui.o graph_io.o graph.o
	g++ main.o cui.o graph_io.o graph.o -o output
	rm *.o

main.o: main.cpp
	g++ -c main.cpp

cui.o: ./ui/cui.cpp ./ui/cui.h
	g++ -c ./ui/cui.cpp

graph.o: ./data/graph.cpp ./data/graph.h
	g++ -c ./data/graph.cpp

graph_io.o: ./data/graph_io.cpp ./data/graph_io.h
	g++ -c ./data/graph_io.cpp
clean:
	rm *.o output