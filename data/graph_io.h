#ifndef GRAPH_IO_H
#define GRAPH_IO_H
#include <bits/stdc++.h>
#include "graph.h"

enum State {Waiting, Reading, Keeping, Closing, Closed};

const std::string FILE_EXTENSION = ".ag";

class Graph_io
{
private:
    std::string file_name;
    State st;
    std::fstream file;
    Graph g;
    
public:
    Graph_io(std::string name);
    void SetGraph(Graph setted);
    void Open();
    Graph* Read();
    void Write(std::string data);
    void Close();
    void Create();
};


#endif