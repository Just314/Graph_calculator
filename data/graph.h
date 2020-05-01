#ifndef GRAPH_H
#define GRAPH_H
#include <bits/stdc++.h>
typedef unsigned short int u_short;

class Graph
{
private:
    u_short verticies_num;
    std::vector<std::pair<int,int>> Points_coord;
    std::vector<u_short> vertecies_W;
    std::vector<std::pair<u_short,u_short>> edges;
    std::vector<u_short> edges_W;
    u_short **adj;
public:
    Graph(u_short v, bool weighted=false);
    Graph(){};

    void addEdge(u_short first, u_short second);
    u_short getVertexWeight(u_short index){return vertecies_W[index];}
    u_short getEdgesCount(){return edges.size();}
    u_short getVertCount(){return verticies_num;}
    bool hasVW(){return vertecies_W.size()>0;}
    bool hasEW(){return edges_W.size()>0;}
    std::string MatrixToString(); 
    
    u_short getVWeigth(u_short index){return vertecies_W[index];}
    u_short getEWeight(u_short index){return edges_W[index];}

    void addVWeight(u_short w){vertecies_W.push_back(w);}
    void addEWeight(u_short w){edges_W.push_back(w);}

    void setVWeight(u_short w, u_short index){vertecies_W[index-1]=w;}

    std::vector<std::pair<u_short,u_short>> getAllEdges(){return edges;}
    std::pair<int,int> getEdge(int index){return edges[index];}
    
    std::vector<int> searchConnectionsOut(int v_num); //Search for all edges out of vertex[v_num];
    std::vector<int> searchConnectionsIn(int v_num);  //Search for all edges into vertex[v_num];
};

#endif