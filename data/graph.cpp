#include "graph.h"

using namespace std;

Graph::Graph(u_short v, bool weighted){
    verticies_num = v;
    adj = new u_short* [v]; 
    for (u_short i=0; i < v; i++)  { 
        adj[i] = new u_short[v]; 
        memset(adj[i], 0, v*sizeof(u_short)); 
    } 
    adj_weighted = new u_short* [v]; 
    for (u_short i=0; i < v; i++)  { 
        adj_weighted[i] = new u_short[v]; 
        memset(adj_weighted[i], 0, v*sizeof(u_short)); 
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
    if (first == second) {
        adj[first-1][second-1]++;;
    }
}

void Graph::addWeight(u_short a, u_short b, u_short w) {
    if (adj_weighted[a-1][b-1] == 0 && a!= b) {
        adj_weighted[a-1][b-1] = w;
        adj_weighted[b-1][a-1] = w;
    }
    else if (w < adj_weighted[a-1][b-1] && a != b) {
        adj_weighted[a-1][b-1] = w;
        adj_weighted[b-1][a-1] = w;
    }
}

std::vector<u_short> Graph::searchConnectionsOut(u_short v_num){
    vector<u_short> Out;
    for (u_short i = 0; i <= edges.size(); i++) {
        if (edges[i].first == v_num) {
            Out.push_back(i);
        }
    }
    return Out;
}

std::vector<u_short> Graph::searchConnectionsIn(u_short v_num){
    vector<u_short> In;
    for (u_short i = 0; i <= edges.size(); i++) {
        if (edges[i].second == v_num) {
            In.push_back(i);
        }
    }
    return In;
}

std::vector<u_short> Graph::searchVertexConnectionsOut(u_short v_num){
    vector<u_short> VOut;
    for (u_short i = 0; i <= edges.size(); i++) {
        if (edges[i].first == v_num) {
            VOut.push_back(edges[i].second);
        }
    }
    return VOut;
}

std::vector<u_short> Graph::searchVertexConnectionsIn(u_short v_num){
    vector<u_short> VIn;
    for (u_short i = 0; i <= edges.size(); i++) {
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