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

std::vector<u_short> Graph::searchConnectionsOut(u_short v_num){
    vector<u_short> Out;
    for (u_short i = 1; i <= edges.size(); i++) {
        if (edges[i].first == v_num) {
            Out.push_back(i);
        }
    }
    return Out;
}

std::vector<u_short> Graph::searchConnectionsIn(u_short v_num){
    vector<u_short> In;
    for (u_short i = 1; i <= edges.size(); i++) {
        if (edges[i].second == v_num) {
            In.push_back(i);
        }
    }
    return In;
}

std::vector<u_short> Graph::searchVertexConnectionsOut(u_short v_num){
    vector<u_short> VOut;
    for (u_short i = 1; i <= edges.size(); i++) {
        if (edges[i].first == v_num) {
            VOut.push_back(edges[i].second);
        }
    }
    return VOut;
}

std::vector<u_short> Graph::searchVertexConnectionsIn(u_short v_num){
    vector<u_short> VIn;
    for (u_short i = 1; i <= edges.size(); i++) {
        if (edges[i].second == v_num) {
            VIn.push_back(edges[i].first);
        }
    }
    return VIn;
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