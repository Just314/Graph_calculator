#include "conn_alg.h"
using namespace std; 


void Connectedness_check::Depth_Fist_SearchOut(u_short s) {
    if (visitedOut[s]) return;
    counterOut++;
    vector <u_short> neighborsout = g->searchVertexConnectionsOut(s);
    visitedOut[s] = true;
    for (auto u: neighborsout) {
    	Depth_Fist_SearchOut(u);
    }
}

void Connectedness_check::Depth_Fist_SearchIn(u_short s) {
    if (visitedIn[s]) return;
    counterIn++;
    vector <u_short> neighborsin = g->searchVertexConnectionsIn(s);
    visitedIn[s] = true;
    for (auto u: neighborsin) {
    	Depth_Fist_SearchIn(u);
    }
}

void Connectedness_check::Initialize(Graph* g_in){
    this->g = g_in;
    cardinal =  g->getVertCount();
    counterOut = 0;
    counterIn = 0;
}

string Connectedness_check::Calculate() {
    string Is_Connected;
    visitedOut.assign(cardinal+1, false);
    visitedIn.assign(cardinal+1, false);
    Depth_Fist_SearchOut(1);
    Depth_Fist_SearchIn(1);
    if (counterOut == cardinal || counterIn == cardinal) {
        weakly_connected = true;        
        Is_Connected = "Graph is weakly connected.\n";
        if (counterIn == counterOut) {
            strongly_connected = true;
            Is_Connected = "Graph is connected.\n";
        }
    }
    else {
        Is_Connected = "Graph is not connected.\n";
    }
    return Is_Connected;
}