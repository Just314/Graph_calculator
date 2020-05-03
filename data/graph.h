#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
typedef unsigned short int u_short;

enum GraphClassify{
    Empty = 0,
    MultiGraph = (1u << 0),
    HasLoops = (1u << 1),
    StronglyConnected = (1u << 2),
    WeaklyConnected = (1u << 3),
    HasCircuit = (1u << 4),
    Weighted = (1u << 5),
    Bipartite = (1u << 6),
    Complete = (1u << 7),
    nGraph = (1u << 8)
};

class Graph
{
private:
    
    u_short verticies_num;
    std::vector<std::pair<int,int>> Points_coord;
    std::vector<u_short> vertecies_W;
    std::vector<std::pair<u_short,u_short>> edges;
    std::vector<u_short> edges_W;
    u_short **adj;
    u_short **adj_underlying;
public:
    Graph(u_short v, bool weighted=false);
    Graph(){};
    GraphClassify type;
    void addEdge(u_short first, u_short second);
    u_short getVertexWeight(u_short index){return vertecies_W[index];}
    u_short getEdgesCount(){return edges.size();}
    u_short getVertCount(){return verticies_num;}
    bool hasVW(){return vertecies_W.size()>0;}
    bool hasEW(){return edges_W.size()>0;}
    u_short **Matrix() {return adj_underlying;}
    std::string MatrixToString(); 
    
    u_short getVWeigth(u_short index){return vertecies_W[index];}
    u_short getEWeight(u_short index){return edges_W[index];}

    void addVWeight(u_short w){vertecies_W.push_back(w);}
    void addEWeight(u_short w){edges_W.push_back(w);}

    void setVWeight(u_short w, u_short index){vertecies_W[index-1]=w;}
    void addUndirectedEdge(u_short a, u_short b){addEdge(a,b);addEdge(b,a);}

    std::vector<std::pair<u_short,u_short>> getAllEdges(){return edges;}
    std::pair<u_short,u_short> getEdge(u_short index){return edges[index];}
    
    std::vector<u_short> searchConnectionsOut(u_short v_num); //Search for all edges out of vertex[v_num];
    std::vector<u_short> searchConnectionsIn(u_short v_num);  //Search for all edges into vertex[v_num];

    std::vector<u_short> searchVertexConnectionsOut(u_short v_num); //Search for all vertices to which there is an edge out of vertex[v_num];
    std::vector<u_short> searchVertexConnectionsIn(u_short v_num);  //Search for all vertices from which there is an edge into vertex[v_num];
};



inline GraphClassify operator | (GraphClassify left, GraphClassify right)
{
    using T = std::underlying_type_t<GraphClassify>;
    return static_cast<GraphClassify>(static_cast<T>(left)|static_cast<T>(right));
}

inline GraphClassify& operator |= (GraphClassify& left, GraphClassify right)
{
    left = left | right;
    return left;
}


#endif