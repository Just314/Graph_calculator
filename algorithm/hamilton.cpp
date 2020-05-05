#include "hamilton.h"
using namespace std;

/*Recursive boolean function that searches for and builds Hamiltonian cycle
or return false which means no cycle exists*/
bool HamiltonAlgo::Hamilton(u_short current) {
    //Adding current vertex
    path.push_back(current);

    /*If length of path equals tne number of vertices algorithm checks 
    whether current vertex and initial are connected. 
    If yes, initial vertex is added to the path and cycle is found.
    Otherwise, no cycle exists and algorithm terminates.*/
    if (path.size() == cardinality)
        if (adjac[path[0]][path.back()] == 1) {
            path.push_back(path[0]);
            return true;
        }
        else {
            return false;
        }

    //Marking current vertex as visited;
    visited[current] = true;

    //Trying to build Hamiltonian cycle using next vertice. 
    //If it is impossible, algorithm returns to previous vertex and repeats
    for (u_short nxt = 0; nxt < cardinality; ++nxt)
        if (adjac[current][nxt] == 1 && !visited[nxt]) 
            if (Hamilton(nxt))
                return true;
    visited[current] = false;
    path.pop_back();
    return false;
}   

void HamiltonAlgo::Initialize(Graph* g_in){
    //Getting input graph, its number of vertices and adjacency matrix. Also, marking all vertices as not visited.
    g = g_in;
    cardinality = g->getVertCount();
    adjac = g->Matrix();
    visited.assign(cardinality, false);
}

std::string HamiltonAlgo::Calculate(){
    //String returned as an answer
    string ISHamiltonian;

    /*If Graph is Hamiltonian and has Hamiltonian cycle we can begin with any vertex, 
    since we should return to the initial vertex of the cycle*/
    if (Hamilton(0)) {
        ISHamiltonian = "Graph has Hamiltonian cycle.\n";
    }
    else {
        ISHamiltonian = "Graph is not Hamiltonian.\n";
    }
    return ISHamiltonian;
}