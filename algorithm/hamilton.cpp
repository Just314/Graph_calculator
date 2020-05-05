#include "hamilton.h"
using namespace std;

bool HamiltonAlgo::Hamilton(u_short current) {
    path.push_back(current);
    if (path.size() == cardinality)
        if (adjac[path[0]][path.back()] == 1) {
            path.push_back(path[0]);
            return true;
        }
        else {
            return false;
        }
    visited[current] = true;
    for (u_short nxt = 0; nxt < cardinality; ++nxt)
        if (adjac[current][nxt] == 1 && !visited[nxt]) 
            if (Hamilton(nxt))
                return true;
    visited[current] = false;
    path.pop_back();
    return false;
}   

void HamiltonAlgo::Initialize(Graph* g_in){
    g = g_in;
    cardinality = g->getVertCount();
    adjac = g->Matrix();
    visited.assign(cardinality+1, false);
    ispath = false;
}

std::string HamiltonAlgo::Calculate(){
    string ISHamiltonian;
    bool answer = false;
    if (Hamilton(0)) {
        ISHamiltonian = "Graph has Hamiltonian cycle.\n";
    }
    else {
        ISHamiltonian = "Graph is not Hamiltonian.\n";
    }
    return ISHamiltonian;
}