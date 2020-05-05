#ifndef GRAPH_IO_H
#define GRAPH_IO_H
#include <bits/stdc++.h>
#include "graph.h"

//Enumerator for parallel exucution state management //  Currently deprecated 
enum State {Waiting, Reading, Keeping, Closing, Closed};

//Extension definition
const std::string FILE_EXTENSION = ".ag";

class Graph_io
{
private:
    std::string file_name; //path - WARNING it is RELATIVE!!!
    State st; //deprecated state management
    std::fstream file; //io stream
    Graph g;
    
public:
    Graph_io(std::string name);
    void SetGraph(Graph setted);
    void Open(); //Open stream
    Graph* Read();
    void Write(std::string data);
    void Close();
    void Create(); //Same as Open but creates files if needed
};

//Custom exception for Corrupted binary files
class InadequateFile: public std::exception {
    public :
        const char* what() const throw(){
            return "File does not exist or is corrupted";
        }
};

#endif