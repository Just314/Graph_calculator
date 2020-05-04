#include "hamilton.h"
using namespace std;

bool HamiltonAlgo::Hamilton(u_short current) {
    path.push_back(current);
    if (path.size() == cardinality)
        if (adjac[path[0]][path.back()] == 1)
            return true;
        else {
            path.pop_back();
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
}

std::string HamiltonAlgo::Calculate(){
    string ISHamiltonian;
    bool answer = false;
    for (u_short i = 0; i < cardinality; i++) {
        if (!Hamilton(i)) path.erase(path.begin(), path.end());
        else { 
            answer = true;
            break;
        }
    }
    if (answer) {
        ISHamiltonian = "Graph is hamiltonian. Cycle is: ";
         for (size_t i=0; i<path.size(); ++i) {
            ISHamiltonian += to_string(path[i]+1);
            ISHamiltonian += " ";
        }
        ISHamiltonian += "\n";
    }
    else {
        ISHamiltonian = "Graph is not Hamiltonian.\n";
    }
    return ISHamiltonian;
}