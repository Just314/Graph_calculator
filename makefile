
output: main.o cui.o graph_io.o graph.o alg_fac_meth.o conn_alg.o euler.o dijkstra.o hamilton.o
	g++ main.o cui.o graph_io.o graph.o alg_fac_meth.o conn_alg.o euler.o dijkstra.o hamilton.o -o output

main.o: main.cpp
	g++ -c -g main.cpp

cui.o: ./ui/cui.cpp ./ui/cui.h
	g++ -c -g ./ui/cui.cpp

graph.o: ./data/graph.cpp ./data/graph.h
	g++ -c -g ./data/graph.cpp

graph_io.o: ./data/graph_io.cpp ./data/graph_io.h
	g++ -c -g ./data/graph_io.cpp

alg_fac_meth.o: ./algorithm/alg_fac_meth.cpp ./algorithm/alg_fac_meth.h ./algorithm/alg.h
	g++ -c -g ./algorithm/alg_fac_meth.cpp

conn_alg.o: ./algorithm/conn_alg.cpp ./algorithm/conn_alg.h ./algorithm/alg.h
	g++ -c -g ./algorithm/conn_alg.cpp

euler.o: ./algorithm/euler.cpp ./algorithm/euler.h ./algorithm/alg.h
	g++ -c -g ./algorithm/euler.cpp

dijkstra.o: ./algorithm/dijkstra.cpp ./algorithm/dijkstra.h ./algorithm/alg.h
	g++ -c -g ./algorithm/dijkstra.cpp

hamilton.o: ./algorithm/hamilton.cpp ./algorithm/hamilton.h ./algorithm/alg.h
	g++ -c -g ./algorithm/hamilton.cpp
clean:
	rm *.o output

winclean:
	del *.o output.exe