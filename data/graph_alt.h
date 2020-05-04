#ifndef GRAPH_A_H
#define GRAPH_A_H
#include "graph.h"

struct Edge;

class Alt_Graph {
    private:
        u_short V_num;
        std::vector<Edge> Edges;
        u_short **adj;
    public:
        GraphClassify type;
        Alt_Graph(u_short v, bool weighted=false);
        void addEdge(u_short a_in, u_short b_in, bool undir = false, u_short w =0);
        
        std::string MatrixToString();
        std::string PrintMeta();
        
        u_short getVertCount(){return V_num;}
        u_short getEdgesCount(){return Edges.size();}


};

struct Edge{
    bool directed;
    u_short vert_a;
    u_short vert_b;
    u_short weight;
};


#endif