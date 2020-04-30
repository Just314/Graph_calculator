#include "graph.h"

using namespace std;

Graph::Graph(u_short v){
    verticies_num = v;
    adj = new u_short* [v]; 
    for (u_short i=0; i < v; i++)  { 
        adj[i] = new u_short[v]; 
        memset(adj[i], 0, v*sizeof(u_short)); 
    } 
}

void Graph::addEdge(u_short first, u_short second){
    edges.push_back(pair<u_short,u_short>(first,second));
    adj[first-1][second-1]++;
}

/*vector<pair<int,int>> Graph::searchConnections(int v_num){
    // TODO
/*realize search of out/in degs
    
}*/

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