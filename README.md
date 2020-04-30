# Universal Ultimative Graph Calculator (only 5 algorithms)

Calculator has its own file extension for storing graphs - .ag



## Flow chart:

main.cpp - launches default cui messages and execution loop

cui.cpp (loop) - requests a .ag file for algorithm execution, 
  launches graph_io for file processing and exceutes factory method of algorithm interface.
  
graph.cpp - stores graph's data and primitive data management methods. Model class.

graph_io.cpp - performs file processing and i/o for the system. Repo class, composed with the graph.

alg.cpp (other one, not yet implemented) - contains interface definition for other algorithm classes.

alg_fac.cpp (nyi - not yet implemented) - contains factory method for algrithm construction on binding level.

