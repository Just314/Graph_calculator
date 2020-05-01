# Universal Ultimative Graph Calculator (only 5 algorithms)

Calculator has its own file extension for storing graphs - .ag



## Usage in details


### Read function

- Entering ***read*** to the console will launch read for the file name

- Typed name goes to the Graph_io constructor, where:


  1) The name is checked for extension existence - if there is no .ag at the end, it would be added
  2) If folder is not defined (e.g. typed just ***test .ag*** and not ***myfolder/test .ag***) default folder ***examples/*** would be picked and added to the name -> ***examples/test .ag***
  3) I/O class state is set to <u>*Waiting*</u>, namely, defining that it is ready for performing operations 

- ***Graph_io::Read()*** call to read the data from the file

- Displays Number of vertex and edges with corresponding functions in **Graph** class

- Displays Adjacency matrix using ***Graph::MatrixToString()***

- Returns to the execution of the *loop()*


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


