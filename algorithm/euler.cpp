#include "euler.h"
using namespace std;

bool EulerAlgo::HasEulerianCycle() {
    if (!ISConnected()) {
        return false;
    }
    for (u_short i = 1; i <= cardinality; i++) {
        if (adjacencylistout[i].size() != adjacencylistinto[i].size()) {
            return false;
        }
    }
    return true;
}

bool EulerAlgo::ISConnected() {
    bool visited[cardinality+1];
    memset(visited, false, sizeof(visited));
    u_short firstnonzero;
    for (firstnonzero = 1; firstnonzero <= cardinality; firstnonzero++) {
        if (!adjacencylistout[firstnonzero].empty()) {
            break;
        }
    }
    DFS(firstnonzero, visited);
    for (u_short i = 1; i <= cardinality; i++) {
        if (!adjacencylistout[firstnonzero].empty() && !visited[i]) {
            return false;
        }
    }
    transpose = true;    
    memset(visited, false, sizeof(visited));
    DFS(firstnonzero, visited);
    for (u_short i = 1; i <= cardinality; i++) {
        if (!adjacencylistout[firstnonzero].empty() && !visited[i]) {
            return false;
        }
    } 
    return true;
}

void EulerAlgo::DFS(u_short nonzero, bool *was) {
    was[nonzero] = true;
    if (!transpose) {
        vector<u_short> temp = adjacencylistout[nonzero];
        for (auto u : temp) {
            if (!was[u]) {
                DFS(u, was);
            }
        }
    }
    else {
        vector<u_short> temp = adjacencylistinto[nonzero];
        for (auto u : temp) {
            if (!was[u]) {
                DFS(u, was);
            }
        }
    }
}

void EulerAlgo::DFSTranspose(u_short nonzero, bool *was) {
    was[nonzero] = true;
    vector<u_short> temp = adjacencylistinto[nonzero];
    for (auto u : temp) {
        if (!was[u]) {
            DFSTranspose(u, was);
        }
    }
}



void EulerAlgo::Initialize(Graph* g_in){
    g = g_in;
    transpose = false;
    cardinality = g->getVertCount();
    adjacencylistout.resize(cardinality+1);
    adjacencylistinto.resize(cardinality+1);
    for (u_short i = 1; i <= cardinality; i++) {
        vector <u_short> outofvertexi = g->searchVertexConnectionsOut(i);
        adjacencylistout.insert(adjacencylistout.begin()+i,outofvertexi);
    }
    for (u_short i = 1; i <= cardinality; i++) {
        vector <u_short> intovertexi = g->searchVertexConnectionsIn(i);
        adjacencylistinto.insert(adjacencylistinto.begin()+i,intovertexi);
    }
}


std::string EulerAlgo::Calculate(){
    string Eulerian;
    if (HasEulerianCycle()) {
        Eulerian = "Graph is Eulerian.\n";
    }
    else {
        Eulerian = "Graph is not Eulerian.\n";
    }
    return Eulerian;
}