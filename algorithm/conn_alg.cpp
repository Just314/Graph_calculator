#include "conn_alg.h"
using namespace std; 
u_short counter = 0;

void Connectedness_check::Depth_Fist_Search(u_short s) {
    if (visited[s]) return;
    counter++;;
    vector <u_short> neighbors = g->searchVertexConnectionsOut(s);
    visited[s] = true;
    for (auto u: neighbors) {
    	Depth_Fist_Search(u);
    }
}

void Connectedness_check::Initialize(Graph* g_in){
    this->g = g_in;
    cardinal =  g->getVertCount();
}

string Connectedness_check::Calculate() {
    string Is_Connected;
    visited.assign(cardinal+1, false);
    Depth_Fist_Search(1);
    if (counter == cardinal) {
        Is_Connected = "Graph is connected.\n";
    }
    else {
        Is_Connected = "Graph is not connected.\n";
    }
    return Is_Connected;
}