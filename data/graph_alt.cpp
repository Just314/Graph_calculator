#include "graph_alt.h"

using namespace std;

Alt_Graph::Alt_Graph(u_short v, bool weighted){
    V_num = v; //set number of verticies

    //Create  Adjecency matrix
    adj = new u_short* [v];

    for (u_short i=0; i < v; i++)  { 
        adj[i] = new u_short[v]; 
        memset(adj[i], 0, v*sizeof(u_short)); 
    } 

    type = Empty;
    if(weighted){
        type |= Weighted; //set flag for weighted graph
    }
}

void Alt_Graph::addEdge(u_short a_in,u_short b_in, bool undir, u_short w){
    Edge e; e.directed = !undir; e.vert_a = a_in; e.vert_b = b_in; e.weight = w; // create new Edge and set it params
    adj[a_in-1][b_in-1]++; //increment matrix at i,j (-1 because matrix is 0-indexed)
    if (a_in == b_in){
        adj[a_in-1][b_in-1]++; //loops give +2 to matrix
    }
    Edges.push_back(e); //add edge to edges list
}

string Alt_Graph::MatrixToString(){
    string out;
    out += "  ";
    for ( u_short i =0;i<V_num; i++) // Print upper letters
    {
        out+=char(97+i);
        out+=" ";
    }
    out+="\n";
    for(u_short i =0;i<V_num;i++){
        out+=char(97+i); //Print side letters
        out+=" ";
        for(u_short j =0; j<V_num;j++){
            out+=to_string(adj[i][j]);
            out+=" ";
        }
        out+="\n";
    }
    return out;
}

std::map<GraphClassify,std::string> metaPrinter = {
    {MultiGraph, "Multigraph"},
    {HasLoops, "Has Loops"},
    {StronglyConnected, "Strongly connected"},
    {WeaklyConnected, "Weakly connected"},
    {HasCircuit, "Has Circuit"},
    {Weighted, "Weighted"},
    {Bipartite, "Bipartite"},
    {Complete, "Complete"},
    {nGraph,"N-Graph"},
    {Undirected, "Undirected"},
    {Mixed,"Mixed"}
};

string Alt_Graph::PrintMeta(){
    string out = "Flags: ";
    for (u_short i = 0; i <= 10; i++)
    {
       GraphClassify flag = static_cast<GraphClassify>(pow(2,i));
       if (type == flag){
           out += metaPrinter[flag];
           out += " ";
       }
    }
    out += "\n";
    return out;
}

/*
bool Alt_Graph::checkFlag(GraphClassify flag){
    u_short flag_val = log2(static_cast<int>(flag)); 
    u_short type_shifted = static_cast<int>(type) >> flag_val;
    if (type_shifted%2 == 1){
        return true;
    }
    return false;
}
*/