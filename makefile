output: main.o cui.o graph_io.o graph.o alg_fac_meth.o conn_alg.o
	g++ main.o cui.o graph_io.o graph.o alg_fac_meth.o conn_alg.o -o output

main.o: main.cpp
	g++ -c main.cpp

cui.o: ./ui/cui.cpp ./ui/cui.h
	g++ -c ./ui/cui.cpp

graph.o: ./data/graph.cpp ./data/graph.h
	g++ -c ./data/graph.cpp

graph_io.o: ./data/graph_io.cpp ./data/graph_io.h
	g++ -c ./data/graph_io.cpp

alg_fac_meth.o: ./algorithm/alg_fac_meth.cpp ./algorithm/alg_fac_meth.h ./algorithm/alg.h
	g++ -c ./algorithm/alg_fac_meth.cpp

conn_alg.o: ./algorithm/conn_alg.cpp ./algorithm/conn_alg.h ./algorithm/alg.h
	g++ -c ./algorithm/conn_alg.cpp

clean:
	rm *.o output

winclean:
	del *.o output.exe