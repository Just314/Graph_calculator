#include "conn_alg.h"
using namespace std; 


void Connectedness_check::Depth_Fist_SearchUnderlying(u_short s) {
    if (visitedOut[s]) return;
    counterUnd++;
    visitedOut[s] = true;
    visitedIn[s] = true;
    for (u_short u = 0; u < cardinal; u++) {
        if (adjacency[s][u] > 0) {
    	Depth_Fist_SearchUnderlying(u);
        }
    }
    for (u_short u = 0; u < cardinal; u++) {
        if (adjacency[u][s] > 0) {
    	    Depth_Fist_SearchUnderlying(u);
        }
    }
}

void Connectedness_check::Depth_Fist_SearchOut(u_short s) {
    if (visitedOut[s]) return;
    counterOut++;
    visitedOut[s] = true;
    for (u_short u = 0; u < cardinal; u++) {
        if (adjacency[s][u] > 0) {
    	    Depth_Fist_SearchOut(u);
        }
    }
}

void Connectedness_check::Depth_Fist_SearchIn(u_short s) {
    if (visitedIn[s]) return;
    counterIn++;
    visitedIn[s] = true;
    for (u_short u = 0; u < cardinal; u++) {
        if (adjacency[u][s] > 0) {
    	    Depth_Fist_SearchIn(u);
        }
    }
}

void Connectedness_check::Initialize(Graph* g_in){
    this->g = g_in;
    cardinal =  g->getVertCount();
    counterOut = 0;
    counterIn = 0;
    counterUnd = 0;
    adjacency = g->Matrix();   
    visitedOut.assign(cardinal, false);
    visitedIn.assign(cardinal, false);
}

string Connectedness_check::Calculate() {
    string Is_Connected;
    Depth_Fist_SearchUnderlying(0);
    visitedIn.assign(cardinal, false);    
    visitedOut.assign(cardinal, false);
    if (counterUnd == cardinal) {
        Depth_Fist_SearchOut(0);
        Depth_Fist_SearchIn(0);
        weakly_connected = true;        
        Is_Connected = "Graph is weakly connected.\n";
        if (counterOut == cardinal && counterIn == cardinal) {
            strongly_connected = true;
            Is_Connected = "Graph is connected.\n";
        }
    }
    else {
        Is_Connected = "Graph is not connected.\n";
    }
    return Is_Connected;
}