# Universal Ultimative Graph Calculator (only 5 algorithms)

Calculator has its own file extension for storing graphs - .ag



## Flow chart:

main.cpp - launches default cui messages and execution loop

cui.cpp (loop) - requests a .ag file for algorithm execution, 
  launches graph_io for file processing and exceutes factory method of algorithm interface.
  
graph.cpp - stores graph's data and primitive data management methods. Model class.

graph_io.cpp - performs file processing and i/o for the system. Repo class, composed with the graph.

alg.h - contains interface definition for other algorithm classes.

alg_fac_meth.h - contains factory methods for algrithm construction on binding level.

alg_fac_meth.cpp - main logic binding algorithm, selected in the 
Perform Calc operation to the real calculations;

Alg_select.cpp - selector for algorithms on enum (WIP)

