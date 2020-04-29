#include "graph.h"

using namespace std;

Graph::Graph(u_short v){
    verticies_num = v;
}

void Graph::addEdge(u_short first, u_short second){
    edges.push_back(pair<u_short,u_short>(first,second));
}
/*vector<pair<int,int>> Graph::searchConnections(int v_num){
    // TODO
    /*realize search of out/in degs
    
}*/