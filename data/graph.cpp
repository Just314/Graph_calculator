#include "graph.h"

using namespace std;

Graph::Graph(u_short v, bool weighted){
    verticies_num = v;
    adj = new u_short* [v]; 
    for (u_short i=0; i < v; i++)  { 
        adj[i] = new u_short[v]; 
        memset(adj[i], 0, v*sizeof(u_short)); 
    } 

    if (weighted){
        vector<u_short> PWeights (verticies_num, 0);
        vertecies_W = PWeights;
    } 
    type = Empty;
}

void Graph::addEdge(u_short first, u_short second){
    edges.push_back(pair<u_short,u_short>(first,second));
    adj[first-1][second-1]++;
}

std::vector<int> Graph::searchConnectionsOut(int v_num){
    vector<int> Out;
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].first == v_num-1) {
            Out.push_back(i);
        }
    }
    return Out;
}

std::vector<int> Graph::searchConnectionsIn(int v_num){
    vector<int> In;
    for (int i = 0; i < edges.size(); i++) {
        if (edges[i].second == v_num-1) {
            In.push_back(i);
        }
    }
    return In;
}

string Graph::MatrixToString(){
    string out;
    out += "  ";
    for ( u_short i =0;i<verticies_num; i++)
    {
        out+=char(97+i);
        out+=" ";
    }
    out+="\n";
    for(u_short i =0;i<verticies_num;i++){
        out+=char(97+i);
        out+=" ";
        for(u_short j =0; j<verticies_num;j++){
            out+=to_string(adj[i][j]);
            out+=" ";
        }
        out+="\n";
    }
    return out;
}